/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:56:31 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/09 14:39:19 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	init_entity_shape(t_data *data, int x, int y, t_shape *entity)
{
	if (data->map[y][x] == 'E')
		(*entity) = (t_shape){.x = (x * TILE_SIZE) - (160 - 64) + 15, .y = (y
				* TILE_SIZE) - (102 - 64) + 66, .w = 125, .h = 1};
	else if (data->map[y][x] == 'F')
		(*entity) = (t_shape){.x = (x * TILE_SIZE) - (84 - 64) + 15, .y = (y
				* TILE_SIZE) - (84 - 64) + 30, .w = (84 - 15 - 15), .h = (84
				- 30 - 5)};
	else if (data->map[y][x] == '1')
		(*entity) = (t_shape){.x = x * TILE_SIZE, .y = y * TILE_SIZE,
			.w = TILE_SIZE, .h = TILE_SIZE};
	else if (data->map[y][x] == 'C')
		(*entity) = (t_shape){.x = x * TILE_SIZE + 10, .y = y * TILE_SIZE + 9,
			.w = TILE_SIZE - 10 - 9, .h = TILE_SIZE - 9 - 8};
}

static int	calculate_distance(t_data *data, t_shape shapes[2], char direction,
		char *entity)
{
	int	distance;

	distance = SPEED;
	if (direction == 'r')
		distance = shapes[1].x - shapes[0].x + SPEED - shapes[0].w;
	else if (direction == 'l')
		distance = shapes[0].x - SPEED - shapes[1].x - shapes[1].w;
	else if (direction == 'd')
		distance = shapes[1].y - shapes[0].y + SPEED - shapes[0].h;
	else if (direction == 'u')
		distance = shapes[0].y - SPEED - shapes[1].y - shapes[1].h;
	if (distance < 0)
		distance = 0;
	if (distance == 0 && (*entity) == 'C')
	{
		distance = SPEED;
		(*entity) = '0';
		data->pcount += 1;
	}
	if (distance < SPEED)
		return (distance);
	return (SPEED);
}

static int	get_distance(t_data *data, char direction, int next_x, int next_y)
{
	int		y;
	int		x;
	t_shape	player;
	t_shape	entity;

	y = -1;
	player = (t_shape){next_x + 6, next_y + 46, TILE_SIZE - 6 - 6, TILE_SIZE
		- 46};
	while (++y < data->height)
	{
		x = -1;
		while (++x < data->width)
		{
			if (!ft_strchr("1CEF", data->map[y][x]))
				continue ;
			init_entity_shape(data, x, y, &entity);
			if (!shape_overlap(player, entity))
				continue ;
			return (calculate_distance(data, (t_shape[]){player, entity},
				direction, &data->map[y][x]));
		}
	}
	return (SPEED);
}

void	update_position(t_data *data, int *next_x, int *next_y)
{
	if (data->keys[XK_d])
	{
		data->direction = 'r';
		*next_x += get_distance(data, 'r', *next_x + SPEED, data->py);
	}
	if (data->keys[XK_a])
	{
		data->direction = 'l';
		*next_x -= get_distance(data, 'l', *next_x - SPEED, data->py);
	}
	if (data->keys[XK_s])
		*next_y += get_distance(data, 'd', data->px, *next_y + SPEED);
	if (data->keys[XK_w])
		*next_y -= get_distance(data, 'u', data->px, *next_y - SPEED);
	data->steps += abs(data->px - *next_x) + abs(data->py - *next_y);
}

void	update_frame(t_data *data, int *updated, void (*callable)(t_data *),
		t_frame_ref frame)
{
	gettimeofday(frame.current_time, NULL);
	if (((*frame.current_time).tv_sec - (*frame.last_time).tv_sec) * 1000
		+ ((*frame.current_time).tv_usec - (*frame.last_time).tv_usec)
		/ 1000 >= frame.delay)
	{
		(*frame.count) = ((*frame.count) + 1) % frame.max;
		if (callable)
			callable(data);
		(*frame.last_time) = (*frame.current_time);
		(*updated) = 1;
	}
}
