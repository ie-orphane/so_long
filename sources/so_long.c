/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:40:10 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/07 12:07:41 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	next_if(t_data *data, char direction, int next_x, int next_y)
{
	int	distance;
	int	y;
	int	x;

	y = 0;
	distance = SPEED;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (ft_strchr("1EC", data->map[y][x]))
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
						if (data->map[y][x] == 'C')
						{
							distance = SPEED;
							data->map[y][x] = '0';
							data->pcount += 1;
						}
						// else if ((data->map[y][x] == 'E' && data->ccount == data->pcount) 
						// 	|| data->map[y][x] == 'F')
						// {
						// 	ft_printf("\nGAME OVER\n");
						// 	exit(0);
						// }
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
	int next_x = data->px;
	int next_y = data->py;
	int updated = 0;

	gettimeofday(&data->f_player.current_time, NULL);
	if ((data->f_player.current_time.tv_sec - data->f_player.last_time.tv_sec) * 1000
		+ (data->f_player.current_time.tv_usec - data->f_player.last_time.tv_usec) / 1000 
		>= 75)
	{
		data->f_player.count = (data->f_player.count + 1) % data->f_player.max;
		data->f_player.state = IDLE_RIGHT;
		if (keyin(data, (int[]){XK_d, XK_a, XK_w, XK_s, -1}))
		{
			update_position(data, &next_x, &next_y);
			if (data->direction == 'l')
				data->f_player.state = RUN_LEFT;
			else
				data->f_player.state = RUN_RIGHT;
		}
		else if (data->direction == 'l')
			data->f_player.state = IDLE_LEFT;
		data->px = next_x;
		data->py = next_y;
		data->f_player.last_time = data->f_player.current_time;
		updated = 1;
	}

	gettimeofday(&data->f_foam.current_time, NULL);
	if ((data->f_foam.current_time.tv_sec - data->f_foam.last_time.tv_sec) * 1000
		+ (data->f_foam.current_time.tv_usec - data->f_foam.last_time.tv_usec) / 1000 
		>= 115)
	{
		data->f_foam.count = (data->f_foam.count + 1) % data->f_foam.max;
		data->f_foam.last_time = data->f_foam.current_time;
		updated = 1;
	}

	gettimeofday(&data->f_enemy.current_time, NULL);
	if ((data->f_enemy.current_time.tv_sec - data->f_enemy.last_time.tv_sec) * 1000
		+ (data->f_enemy.current_time.tv_usec - data->f_enemy.last_time.tv_usec) / 1000 
		>= 100)
	{
		data->f_enemy.count = (data->f_enemy.count + 1) % data->f_enemy.max;
		data->f_enemy.last_time = data->f_enemy.current_time;
		updated = 1;
	}

	if (updated)
	{
		if (data->img)
		{
			mlx_destroy_image(data->mlx, data->img->img_ptr);
			free(data->img);
		}
		data->img = img_new(data->mlx, data->width * TILE_SIZE, data->height * TILE_SIZE);
		put_ground_layers(data);
		put_entities_layers(data);
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
	read_map(&data, argv[1]);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.width * TILE_SIZE,
		data.height * TILE_SIZE, WIN_TITLE);

	data.steps = 0;
	data.pcount = 0;
	data.direction = 'r';

	for (int i = 0; i < 256; i++)
		data.keys[i] = 0;
	init_sprites(&data);

	mlx_loop_hook(data.mlx, update_animation, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, key_down, &data);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, key_up, &data);
	mlx_hook(data.win, DestroyNotify, NoEventMask, handle_close_event, &data);

	mlx_loop(data.mlx);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
	return (0);
}
