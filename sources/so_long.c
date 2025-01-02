/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:40:10 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/02 21:48:24 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	get_wall_tile(t_data *data, int x, int y)
{
	if (x == 0 && 0 < y && y < data->map->height - 1)
		return ('4');
	if (x == data->map->width - 1 && 0 < y && y < data->map->height - 1)
		return ('2');
	if (y == 0 && 0 < x && x < data->map->width - 1)
		return ('3');
	if (x == data->map->width - 1 && y == 0)
		return ('6');
	if (x == 0 && y == 0)
		return ('5');
	if (x == data->map->width - 1 && y == data->map->height - 1)
		return ('7');
	if (x == 0 && y == data->map->height - 1)
		return ('8');
	if (0 < x && x < data->map->width - 1 && y == data->map->height - 1)
		return ('9');
	return ('1');
}

void	init_static_img(t_data *data)
{
	int		x;
	int		y;
	t_img	*img;
	char	tile_key;

	data->static_img = img_new(data->mlx, data->map->width * FRAME_SIZE, data->map->height * FRAME_SIZE);
	y = -1;
	while (++y < data->map->height)
	{
		x = -1;
		while (++x < data->map->width)
		{
			img = NULL;
			tile_key = '0';
			if (data->map->blocks[y][x] == '1')
			{
				img = frame_get(data->frames, 'g', (x + y) % 32);
				put_img_to_img(data->static_img, img, FRAME_SIZE * x, FRAME_SIZE * y);
				tile_key = get_wall_tile(data, x, y);
			}
			img = dict_find(&data->imgs, tile_key);
			if (img)
				put_img_to_img(data->static_img, img, FRAME_SIZE * x, FRAME_SIZE * y);
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
				put_img_to_img(data->img, img, FRAME_SIZE * x, FRAME_SIZE * y);
		}
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
	if (data->keys[XK_d]) // Move right
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
			if (data->direction == 'l')
				keyframe = 'R';
			else
				keyframe = 'r';
		}
		else
		{
			data->current_frame = (data->current_frame + 1) % IDLE_FRAMES;
			if (data->direction == 'l')
				keyframe = 'I';
		}
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
		put_img_to_img(data->img, data->static_img, 0, 0);
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

	srand(time(NULL));
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
	data.direction = 'r';

	init_images(&data);
	init_static_img(&data);

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
