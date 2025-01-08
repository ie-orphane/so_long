/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:06:49 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/08 22:03:46 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_uint	t_ground_index(t_data *data, int x, int y)
{
	t_uint	top;
	t_uint	right;
	t_uint	bottom;
	t_uint	left;

	top = data->map[y - 1][x] == '1';
	right = data->map[y][x + 1] == '1';
	bottom = data->map[y + 1][x] == '1';
	left = data->map[y][x - 1] == '1';
	return ((top << 3) | (left << 2) | (right << 1) | bottom);
}

static void	put_player_img(t_data *data)
{
	t_img	*player_img;
	int		player_x;
	int		player_y;

	player_x = data->px;
	player_y = data->py - 10;
	player_img = data->f_player.all[data->f_player.state][data->f_player.count];
	if (data->direction == 'l')
		put_img_to_img(data->img, player_img, player_x, player_y);
	else
		put_img_to_img(data->img, player_img, player_x, player_y);
}

void	put_ground_layers(t_data *data)
{
	int		x;
	int		y;
	t_img	*img;

	y = -1;
	while (++y < data->height)
	{
		x = -1;
		while (++x < data->width)
		{
			img = data->tiles[TILE_WATER];
			if (img)
				put_img_to_img(data->img, img, TILE_SIZE * x, TILE_SIZE * y);
		}
	}
	y = -1;
	while (++y < data->height)
	{
		x = -1;
		while (++x < data->width)
		{
			img = NULL;
			if (data->map[y][x] != '1')
				img = data->f_foam.all[data->f_foam.count];
			if (img)
				put_img_to_img(data->img, img, (TILE_SIZE * x) - ((82 - 64)
						/ 2), (TILE_SIZE * y) - ((82 - 64) / 2));
		}
	}
	y = -1;
	while (++y < data->height)
	{
		x = -1;
		while (++x < data->width)
		{
			img = NULL;
			if (data->map[y][x] != '1')
				img = data->t_ground[t_ground_index(data, x, y)];
			if (img)
				put_img_to_img(data->img, img, TILE_SIZE * x, TILE_SIZE * y);
		}
	}
}

static void	put_entities_img(t_data *data, t_img *img, t_point position, char **player_img)
{
	t_shape	entity;
	t_shape	player;

	player = (t_shape){data->px, data->py - 10, TILE_SIZE, TILE_SIZE};
	entity = (t_shape){TILE_SIZE * position.x - (img->width / 2) + (TILE_SIZE / 2),
		TILE_SIZE * position.y - (img->height / 2) + (TILE_SIZE / 2) - 10,
		img->width, img->height};
	if (shape_overlap(player, entity))
	{
		(*player_img) = "test";
		if (position.y * TILE_SIZE <= data->py)
		{
			put_img_to_img(data->img, img, entity.x, entity.y);
			put_player_img(data);
		}
		else
		{
			put_player_img(data);
			put_img_to_img(data->img, img, entity.x, entity.y);
		}
	}
	else
		put_img_to_img(data->img, img, entity.x, entity.y);
}

t_img	*get_entity_img(t_data *data, int x, int y)
{
	t_img	*img;

	img = NULL;
	if (data->map[y][x] == 'C')
		img = data->tiles[TILE_GOLD];
	else if (data->map[y][x] == 'E' && data->ccount != data->pcount)
		img = data->tiles[TILE_MINE_DESTROYED];
	else if (data->map[y][x] == 'E')
		img = data->tiles[TILE_MINE_ACTIVE];
	else if (data->map[y][x] == 'F')
		img = data->f_enemy.all[data->f_enemy.count];
	return (img);
}

void	put_entities_layers(t_data *data)
{
	int		x;
	int		y;
	t_img	*img;
	char	*player_img;

	player_img = NULL;
	y = -1;
	while (++y < data->height)
	{
		x = -1;
		while (++x < data->width)
		{
			img = get_entity_img(data, x, y);
			if (!img)
				continue ;
			put_entities_img(data, img, (t_point){x, y}, &player_img);
		}
	}
	if (!player_img)
		put_player_img(data);
}
