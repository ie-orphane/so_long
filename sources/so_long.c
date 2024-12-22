/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:40:10 by ielyatim          #+#    #+#             */
/*   Updated: 2024/12/22 21:09:16 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*file_name_to_path(const char *dir, int index)
{
	char	*path;
	char	*num;
	size_t	pathsize;

	num = ft_itoa(index);
	pathsize = ft_strlen(dir) + ft_strlen(num) + 5;
	path = malloc(pathsize * sizeof(char));
	if (path)
	{
		ft_strlcpy(path, dir, pathsize);
		ft_strlcat(path, num, pathsize);
		ft_strlcat(path, ".xpm", pathsize);
	}
	free(num);
	return (path);
}

void	fill_frames(t_data *data, size_t max, const char *dir, char key)
{
	t_dict	*frames;
	size_t	i;
	char	*img_path;

	frames = NULL;
	i = 0;
	while (i < max)
	{
		img_path = file_name_to_path(dir, i);
		dict_add(&frames, i, img_init(data->mlx, img_path));
		free(img_path);
		i++;
	}
	dict_add(&data->frames, key, frames);
}

void	init_images(t_data *data)
{
	dict_add(&data->imgs, '1', img_init(data->mlx, "./sprites/wall.xpm"));
	// dict_add(&data->imgs, '2', img_init(data->mlx, "./sprites/000.xpm"));
	dict_add(&data->imgs, 'E', img_init(data->mlx, "./sprites/exit32x32.xpm"));
	dict_add(&data->imgs, '0', img_init(data->mlx, "./sprites/ground.xpm"));
	fill_frames(data, IDLE_FRAMES, "./sprites/pink-man/idle/", 'i');
	fill_frames(data, RUN_FRAMES, "./sprites/pink-man/run/", 'r');
	fill_frames(data, COLLECTIVE_FRAMES, "./sprites/banana/", 'c');
	fill_frames(data, EXIT_FRAMES, "./sprites/trophy/", 'e');
	fill_frames(data, ENEMY_FRAMES, "./sprites/mashroom/", 'F');
}

t_img	*frame_get(t_dict *framedict, char framekey, char frameindex)
{
	t_img	*img;
	t_dict	*frames;

	frames = dict_find(&framedict, framekey);
	img = dict_find(&frames, frameindex);
	return (img);
}

void	render(t_data *data)
{
	int		x;
	int		y;
	t_img	*img;

	y = 0;
	while (y < data->map->height)
	{
		x = 0;
		while (x < data->map->width)
		{
			img = dict_find(&data->imgs, '0');
			put_img_to_img(data->img, img, FRAME_SIZE * x, FRAME_SIZE * y);
			img = NULL;
			if (data->map->blocks[y][x] == '1')
				img = dict_find(&data->imgs, data->map->blocks[y][x]);
			else if (data->map->blocks[y][x] == 'C')
				img = frame_get(data->frames, 'c', data->count_frame);
			else if (data->map->blocks[y][x] == 'E' && data->ccount != data->pcount)
				img = dict_find(&data->imgs, 'E');
			else if (data->map->blocks[y][x] == 'E')
				img = frame_get(data->frames, 'e', data->eframe);
			else if (data->map->blocks[y][x] == 'F')
				img = frame_get(data->frames, 'F', data->enemy_frame);
			if (img)
				put_img_to_img(data->img, img, FRAME_SIZE * x, FRAME_SIZE * y);
			x++;
		}
		y++;
	}
}

int	frames_overlap(int ax, int ay, int bx, int by)
{
	int	a_right;
	int	a_bottom;
	int	b_right;
	int	b_bottom;

	a_right = ax + FRAME_SIZE;
	a_bottom = ay + FRAME_SIZE;
	b_right = bx + FRAME_SIZE;
	b_bottom = by + FRAME_SIZE;
	if (ax >= b_right || bx >= a_right)
		return (0);
	if (ay >= b_bottom || by >= a_bottom)
		return (0);
	return (1);
}

int	next_if(t_data *data, char direction, int next_x, int next_y)
{
	int	distance;
	int	y;
	int	x;

	y = 0;
	distance = SPEED;
	while (y < data->map->height)
	{
		x = 0;
		while (x < data->map->width)
		{
			if (ft_strchr("1ECF", data->map->blocks[y][x]))
			{
				if (frames_overlap(x * FRAME_SIZE, y * FRAME_SIZE, next_x, next_y))
				{
					if (direction == 'r')
						distance = x * FRAME_SIZE - (data->px + FRAME_SIZE);
					else if (direction == 'l')
						distance = data->px - (x * FRAME_SIZE + FRAME_SIZE);
					else if (direction == 'd')
						distance = y * FRAME_SIZE - (data->py + FRAME_SIZE);
					else if (direction == 'u')
						distance = data->py - (y * FRAME_SIZE + FRAME_SIZE);
					if (distance < 0)
						distance = 0;
					if (distance == 0)
					{
						if (data->map->blocks[y][x] == 'C')
						{
							distance = SPEED;
							data->map->blocks[y][x] = '0';
							data->pcount += 1;
						}
						else if ((data->map->blocks[y][x] == 'E' && data->ccount == data->pcount) 
							|| data->map->blocks[y][x] == 'F')
						{
							ft_printf("\nGAME OVER\n");
							exit(0);
						}
					}
				}
			}
			x++;
		}
		y++;
	}
	if (distance < SPEED)
		return (distance);
	return (SPEED);
}

void update_position(t_data *data, int *next_x, int *next_y)
{
	int distance_x;
	int distance_y;

	distance_x = SPEED;
	distance_y = SPEED;
	if (data->keys[XK_d]) // Move right
		distance_x = next_if(data, 'r', *next_x + SPEED, data->py);
	if (data->keys[XK_a]) // Move left
		distance_x = next_if(data, 'l', *next_x - SPEED, data->py);
	if (data->keys[XK_s]) // Move down
		distance_y = next_if(data, 'd', data->px, *next_y + SPEED);
	if (data->keys[XK_w]) // Move up
		distance_y = next_if(data, 'u', data->px, *next_y - SPEED);
	if (data->keys[XK_d] && distance_x > 0)
		*next_x += distance_x;
	if (data->keys[XK_a] && distance_x > 0)
		*next_x -= distance_x;
	if (data->keys[XK_s] && distance_y > 0)
		*next_y += distance_y;
	if (data->keys[XK_w] && distance_y > 0)
		*next_y -= distance_y;
	data->steps += abs(data->px - *next_x) + abs(data->py - *next_y);
	// if (data->steps != 0 && data->steps % FRAME_SIZE == 0)
	// 	ft_printf("%d\n", data->steps / FRAME_SIZE);
}

int keyin(t_data *data, int arr[])
{
	int i;

	i = 0;
	while (arr[i] != -1)
	{
		if (data->keys[arr[i]])
			return (1);
		i++;
	}
	return (0);
}

int update_animation(t_data *data)
{
	int next_x = data->px;
	int next_y = data->py;

	if (data->counter++ % ANIMATION_DELAY == 0)
	{
		char keyframe = 'i';
		
		if (keyin(data, (int[]){XK_d, XK_a, XK_w, XK_s, -1}))
		{
			update_position(data, &next_x, &next_y);
			data->current_frame = (data->current_frame + 1) % RUN_FRAMES;
			keyframe = 'r';
		}
		else
			data->current_frame = (data->current_frame + 1) % IDLE_FRAMES;
		data->px = next_x;
		data->py = next_y;
		t_dict *frames = dict_find(&data->frames, keyframe);
		t_img *frame = dict_find(&frames, data->current_frame);
		if (!frames || !frame)
		{
			ft_printf("failed to get frames");
			exit(0);
		}
		data->count_frame = (data->count_frame + 1) % COLLECTIVE_FRAMES;
		data->enemy_frame = (data->enemy_frame + 1) % ENEMY_FRAMES;
		if (data->ccount == data->pcount)
			data->eframe = (data->eframe + 1) % EXIT_FRAMES;
		if (data->img)
		{
			mlx_destroy_image(data->mlx, data->img->img_ptr);
			free(data->img);
		}
		data->img = img_new(data->mlx, data->map->width * FRAME_SIZE, data->map->height * FRAME_SIZE);
		render(data);
		put_img_to_img(data->img, frame, data->px, data->py);
		mlx_clear_window(data->mlx, data->win);
		mlx_put_image_to_window(data->mlx, data->win, data->img->img_ptr, 0, 0);
	}
	return (0);
}

int main(void)
{
	t_data data;

	data.map = read_map(&data, "./map.ber");
	data.mlx = mlx_init();
	if (data.mlx == NULL)
	{
		ft_printf("Error\n");
		return (MLX_ERROR);
	}
	data.win = mlx_new_window(
		data.mlx,
		data.map->width * FRAME_SIZE,
		data.map->height * FRAME_SIZE,
		WIN_TITLE);
	if (data.win == NULL)
	{
		ft_printf("Error\n");
		free(data.mlx);
		return (MLX_ERROR);
	}

	data.imgs = NULL;
	data.img = NULL;
	data.counter = 0;
	data.frames = NULL;
	data.steps = 0;
	data.pcount = 0;
	data.eframe = 0;
	data.enemy_frame = 0;

	init_images(&data);

	data.current_frame = 0;
	data.count_frame = 0;

	data.counter = 0;
	for (int i = 0; i < 256; i++)
		data.keys[i] = 0;

	mlx_loop_hook(data.mlx, update_animation, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, key_down, &data);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, key_up, &data);
	mlx_hook(data.win, DestroyNotify, NoEventMask, handle_close_event, &data);

	mlx_loop(data.mlx);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
	return (0);
}
