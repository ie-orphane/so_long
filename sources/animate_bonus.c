/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 10:49:21 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/26 22:03:29 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"

static void	init_entity_shape(t_data *data, int x, int y, t_shape *entity)
{
	if (data->map[y][x] == 'E')
		(*entity) = (t_shape){.x = (x * TILE_SIZE) - ((160 - 64) / 2) + 15,
			.y = (y * TILE_SIZE) - ((102 - 64) / 2) + 66, .w = 125, .h = 28};
	else if (data->map[y][x] == 'F')
		(*entity) = (t_shape){.x = (x * TILE_SIZE) - ((84 - 64) / 2) + 15,
			.y = (y * TILE_SIZE) - ((84 - 64) / 2) + 30, .w = (84 - 15 - 15),
			.h = (84 - 30 - 5)};
	else if (data->map[y][x] == '1')
		(*entity) = (t_shape){.x = x * TILE_SIZE, .y = y * TILE_SIZE,
			.w = TILE_SIZE, .h = TILE_SIZE};
	else if (data->map[y][x] == 'C')
		(*entity) = (t_shape){.x = x * TILE_SIZE + 10, .y = y * TILE_SIZE + 9
			- 10, .w = TILE_SIZE - 10 - 9, .h = TILE_SIZE};
}

static void	check_collision(t_data *data, int *distance, t_point pos,
		t_shape shapes[2])
{
	if (*distance == 0 && data->map[pos.y][pos.x] == 'C')
	{
		*distance = SPEED;
		data->map[pos.y][pos.x] = '0';
		data->pcount += 1;
		data->c = (t_point){pos.x, pos.y};
	}
	if (*distance == 0 && data->map[pos.y][pos.x] == 'F')
		data->f_player.state = DEAD;
	if (*distance == 0 && data->map[pos.y][pos.x] == 'E' && data->ccount == data->pcount)
	{
		shapes[1].x += 35;
		shapes[1].w -= 65;
		if (shape_overlap(shapes[0], shapes[1]))
			data->f_player.state = EXIT;
	}
}

static int	calculate_distance(t_data *data, t_shape shapes[2], char direction,
		t_point pos)
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
	distance = (distance + (-distance * (distance < 0)));
	check_collision(data, &distance, pos, shapes);
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
				direction, (t_point){x, y}));
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
