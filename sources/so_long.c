/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:40:10 by ielyatim          #+#    #+#             */
/*   Updated: 2024/12/21 18:15:38 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char *file_name_to_path(const char *dir, int index)
{
	char *path;
	char *num;
	size_t pathsize;

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
void fill_frames(t_data *data, size_t max_frames, const char *frames_dir, char frames_key)
{
	t_dict *frames;
	size_t i;

	frames = NULL;
	i = 0;
	while (i < max_frames)
	{
		char *img_path = file_name_to_path(frames_dir, i);
		dict_add(&frames, i, img_init(data->mlx, img_path));
		free(img_path);
		i++;
	}
	dict_add(&data->frames, frames_key, frames);
}

void init_images(t_data *data)
{
	dict_add(&data->imgs, '1', img_init(data->mlx, "./sprites/wall32x32.xpm"));
	fill_frames(data, IDLE_FRAMES, "./sprites/pink-man/idle/", 'i');
	fill_frames(data, RUN_FRAMES, "./sprites/pink-man/run/", 'r');
	fill_frames(data, COLLECTIVE_FRAMES, "./sprites/banana/", 'c');
}

void render(t_data *data)
{
	int x;
	int y;
	t_img *img;
	t_dict *frames;

	y = 0;
	while (y < data->map->height)
	{
		x = 0;
		while (x < data->map->width)
		{
			img = NULL;
			if (data->map->blocks[y][x] == '1')
				img = dict_find(&data->imgs, data->map->blocks[y][x]);
			else if (data->map->blocks[y][x] == 'C')
			{
				frames = dict_find(&data->frames, 'c');
				img = dict_find(&frames, data->count_frame);
				if (!frames || !img)
				{
					ft_printf("failed to get frames");
					exit(0);
				}
			}
			else if (data->map->blocks[y][x] == 'E')
			{
				if (data->ccount == data->pcount)
					img = dict_find(&data->imgs, 'e');
				else
					img = dict_find(&data->imgs, data->map->blocks[y][x]);
			}
			if (img)
				mlx_put_image_to_window(
					data->mlx,
					data->win,
					img->img_ptr,
					FRAME_SIZE * x,
					FRAME_SIZE * y);
			x++;
		}
		y++;
	}
}

int frames_overlap(int ax, int ay, int bx, int by)
{
	int a_right = ax + FRAME_SIZE;
	int a_bottom = ay + FRAME_SIZE;
	int b_right = bx + FRAME_SIZE;
	int b_bottom = by + FRAME_SIZE;

	if (ax >= b_right || bx >= a_right) // No horizontal overlap
		return (0);
	if (ay >= b_bottom || by >= a_bottom) // No vertical overlap
		return (0);
	return (1);
}

int next_ifwall(t_data *data, char direction, int next_x, int next_y)
{
	int distance = SPEED;
	int y = 0;

	while (y < data->map->height)
	{
		int x = 0;
		while (x < data->map->width)
		{
			if (data->map->blocks[y][x] == '1') // Wall block
			{
				if (frames_overlap(x * FRAME_SIZE, y * FRAME_SIZE, next_x, next_y))
				{
					if (direction == 'r') // Moving right
						distance = x * FRAME_SIZE - (data->px + FRAME_SIZE);
					else if (direction == 'l') // Moving left
						distance = data->px - (x * FRAME_SIZE + FRAME_SIZE);
					else if (direction == 'd') // Moving down
						distance = y * FRAME_SIZE - (data->py + FRAME_SIZE);
					else if (direction == 'u') // Moving up
						distance = data->py - (y * FRAME_SIZE + FRAME_SIZE);
					if (distance < 0)
						distance = 0;
				}
			}
			else if (data->map->blocks[y][x] == 'C')
			{
				if (frames_overlap(x * FRAME_SIZE, y * FRAME_SIZE, next_x, next_y))
				{
					if (direction == 'r') // Moving right
						distance = x * FRAME_SIZE - (data->px + FRAME_SIZE);
					else if (direction == 'l') // Moving left
						distance = data->px - (x * FRAME_SIZE + FRAME_SIZE);
					else if (direction == 'd') // Moving down
						distance = y * FRAME_SIZE - (data->py + FRAME_SIZE);
					else if (direction == 'u') // Moving up
						distance = data->py - (y * FRAME_SIZE + FRAME_SIZE);
					if (distance < 0)
						distance = 0;
					if (distance == 0)
					{
						distance = SPEED;
						data->map->blocks[y][x] = '0';
						data->pcount += 1;
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
		distance_x = next_ifwall(data, 'r', *next_x + SPEED, data->py);
	if (data->keys[XK_a]) // Move left
		distance_x = next_ifwall(data, 'l', *next_x - SPEED, data->py);
	if (data->keys[XK_s]) // Move down
		distance_y = next_ifwall(data, 'd', data->px, *next_y + SPEED);
	if (data->keys[XK_w]) // Move up
		distance_y = next_ifwall(data, 'u', data->px, *next_y - SPEED);
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

int update_animation(t_data *data)
{
	int next_x = data->px;
	int next_y = data->py;

	if (data->counter++ % ANIMATION_DELAY == 0)
	{
		mlx_clear_window(data->mlx, data->win);
		char keyframe = 'i';
		if (data->keys[XK_d] || data->keys[XK_a] || data->keys[XK_w] || data->keys[XK_s])
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
		mlx_put_image_to_window(data->mlx, data->win, frame->img_ptr, data->px, data->py);
		render(data);
	}
	return 0;
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
	// data.collective = 0;
	data.counter = 0;
	data.frames = NULL;
	data.steps = 0;
	data.pcount = 0;
	// data.ccount = data.map->collective;

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
