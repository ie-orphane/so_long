/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:40:10 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/05 20:02:26 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_uint	t_ground_index(t_data *data, int x, int y)
{
	t_uint	top;
	t_uint	right;
	t_uint	bottom;
	t_uint	left;

	top = data->map->blocks[y - 1][x] == '1';
	right = data->map->blocks[y][x + 1] == '1';
	bottom = data->map->blocks[y + 1][x] == '1';
	left = data->map->blocks[y][x - 1] == '1';
	return ((top << 3) | (left << 2) | (right << 1) | bottom);
}

void	put_layers(t_data *data)
{
	int		x;
	int		y;
	t_img	*img;

	y = -1;
	while (++y < data->map->height)
	{
		x = -1;
		while (++x < data->map->width)
		{
			img = dict_find(&data->imgs, '0');
			if (img)
				put_img_to_img(data->img, img, TILE_SIZE * x, TILE_SIZE * y);
		}
	}
	y = -1;
	while (++y < data->map->height)
	{
		x = -1;
		while (++x < data->map->width)
		{
			img = NULL;
			if (data->map->blocks[y][x] != '1')
				img = frame_get(data->frames, 'f', data->f_foan.count);
			if (img)
				put_img_to_img(data->img, img, (TILE_SIZE * x) - ((82 - 64) / 2), (TILE_SIZE * y) - ((82 - 64) / 2));
		}
	}
	y = -1;
	while (++y < data->map->height)
	{
		x = -1;
		while (++x < data->map->width)
		{
			img = NULL;
			if (data->map->blocks[y][x] != '1')
				img = data->t_ground[t_ground_index(data, x, y)];
			if (img)
				put_img_to_img(data->img, img, TILE_SIZE * x, TILE_SIZE * y);
		}
	}
}

void	render(t_data *data)
{
	int		x;
	int		y;
	t_img	*img;

	y = -1;
	while (++y < data->map->height)
	{
		x = -1;
		while (++x < data->map->width)
		{
			img = NULL;
			if (data->map->blocks[y][x] == 'C')
				img = frame_get(data->frames, 'c', data->count_frame);
			else if (data->map->blocks[y][x] == 'E' && data->ccount != data->pcount)
				img = dict_find(&data->imgs, 'E');
			else if (data->map->blocks[y][x] == 'E')
				img = frame_get(data->frames, 'e', data->eframe);
			else if (data->map->blocks[y][x] == 'F')
				img = frame_get(data->frames, 'F', data->enemy_frame);
			if (img)
				put_img_to_img(data->img, img, TILE_SIZE * x, TILE_SIZE * y);
		}
	}
}

int	frames_overlap(int ax, int ay, int bx, int by)
{
	if (ax >= bx + TILE_SIZE ||
		bx >= ax + TILE_SIZE ||
		ay >= by + TILE_SIZE ||
		by >= ay + TILE_SIZE)
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
				if (frames_overlap(x * TILE_SIZE, y * TILE_SIZE, next_x, next_y))
				{
					if (direction == 'r')
						distance = x * TILE_SIZE - (data->px + TILE_SIZE);
					else if (direction == 'l')
						distance = data->px - (x * TILE_SIZE + TILE_SIZE);
					else if (direction == 'd')
						distance = y * TILE_SIZE - (data->py + TILE_SIZE);
					else if (direction == 'u')
						distance = data->py - (y * TILE_SIZE + TILE_SIZE);
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
	if (data->keys[XK_d] == 1) // Move right
	{
		data->direction = 'r';
		*next_x += next_if(data, 'r', *next_x + SPEED, data->py);
	}
	if (data->keys[XK_a]) // Move left
	{
		data->direction = 'l';
		*next_x -= next_if(data, 'l', *next_x - SPEED, data->py);
	}
	if (data->keys[XK_s]) // Move down
		*next_y += next_if(data, 'd', data->px, *next_y + SPEED);
	if (data->keys[XK_w]) // Move up
		*next_y -= next_if(data, 'u', data->px, *next_y - SPEED);
	data->steps += abs(data->px - *next_x) + abs(data->py - *next_y);
	// if (data->steps != 0 && data->steps % TILE_SIZE == 0)
	// 	ft_printf("%d\n", data->steps / TILE_SIZE);
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
	static char keyframe = 'i';
	int next_x = data->px;
	int next_y = data->py;
	int updated = 0;

	gettimeofday(&data->f_player.current_time, NULL);
	if ((data->f_player.current_time.tv_sec - data->f_player.last_time.tv_sec) * 1000
		+ (data->f_player.current_time.tv_usec - data->f_player.last_time.tv_usec) / 1000 
		>= 75)
	{
		keyframe = 'i';
		if (keyin(data, (int[]){XK_d, XK_a, XK_w, XK_s, -1}))
		{
			update_position(data, &next_x, &next_y);
			data->f_player.count = (data->f_player.count + 1) % RUN_FRAMES;
			if (data->direction == 'l')
				keyframe = 'R';
			else
				keyframe = 'r';
		}
		else
		{
			data->f_player.count = (data->f_player.count + 1) % IDLE_FRAMES;
			if (data->direction == 'l')
				keyframe = 'I';
		}
		data->px = next_x;
		data->py = next_y;
		// data->count_frame = (data->count_frame + 1) % COLLECTIVE_FRAMES;
		// data->enemy_frame = (data->enemy_frame + 1) % ENEMY_FRAMES;
		// if (data->ccount == data->pcount)
		// 	data->eframe = (data->eframe + 1) % EXIT_FRAMES;
		data->f_player.last_time = data->f_player.current_time;
		updated = 1;
	}

	gettimeofday(&data->f_foan.current_time, NULL);
	if ((data->f_foan.current_time.tv_sec - data->f_foan.last_time.tv_sec) * 1000
		+ (data->f_foan.current_time.tv_usec - data->f_foan.last_time.tv_usec) / 1000 
		>= 115)
	{
		data->f_foan.count = (data->f_foan.count + 1) % FOAM_FRAMES;
		data->f_foan.last_time = data->f_foan.current_time;
		updated = 1;
	}

	if (updated)
	{
		t_dict *frames = dict_find(&data->frames, keyframe);
		t_img *frame = dict_find(&frames, data->f_player.count);

		if (data->img)
		{
			mlx_destroy_image(data->mlx, data->img->img_ptr);
			free(data->img);
		}
		data->img = img_new(data->mlx, data->map->width * TILE_SIZE, data->map->height * TILE_SIZE);
		put_layers(data);
		// render(data);
		put_img_to_img(data->img, frame, data->px, data->py);
		mlx_clear_window(data->mlx, data->win);
		mlx_put_image_to_window(data->mlx, data->win, data->img->img_ptr, 0, 0);
	}
	return (0);
}

int main(int argc, char *argv[])
{
	t_data data;

	if (argc < 1)
		return (0);
	data.map = read_map(&data, argv[1]);
	data.mlx = mlx_init();
	if (data.mlx == NULL)
	{
		ft_printf("Error\n");
		return (MLX_ERROR);
	}
	data.win = mlx_new_window(
		data.mlx,
		data.map->width * TILE_SIZE,
		data.map->height * TILE_SIZE,
		WIN_TITLE);
	if (data.win == NULL)
	{
		ft_printf("Error\n");
		free(data.mlx);
		return (MLX_ERROR);
	}

	data.imgs = NULL;
	data.img = NULL;

	data.frames = NULL;
	data.steps = 0;
	data.pcount = 0;
	data.eframe = 0;
	data.fframe = 0;
	data.enemy_frame = 0;
	data.direction = 'r';

	data.f_foan.count = 0;
	gettimeofday(&data.f_foan.last_time, NULL);

	data.f_player.count = 0;
	gettimeofday(&data.f_player.last_time, NULL);

	init_images(&data);

	data.count_frame = 0;

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
