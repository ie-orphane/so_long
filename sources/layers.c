/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:06:49 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/07 12:10:56 by ielyatim         ###   ########.fr       */
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
				put_img_to_img(data->img, img, (TILE_SIZE * x) - ((82 - 64) / 2), (TILE_SIZE * y) - ((82 - 64) / 2));
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

int	frames_overlap(int ax, int ay, int bx, int by)
{
	if (ax >= bx + TILE_SIZE ||
		bx >= ax + TILE_SIZE ||
		ay >= by + TILE_SIZE ||
		by >= ay + TILE_SIZE)
		return (0);
	return (1);
}

int	shape_overlap(t_shape a, t_shape b)
{
	if (a.x >= b.x + b.w ||
		b.x >= a.x + a.w ||
		a.y >= b.y + b.h ||
		b.y >= a.y + a.h)
		return (0);
	return (1);
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
			img = NULL;
			if (data->map[y][x] == 'C')
				img = data->tiles[TILE_GOLD];
			else if (data->map[y][x] == 'E' && data->ccount != data->pcount)
				img = data->tiles[TILE_MINE_DESTROYED];
			else if (data->map[y][x] == 'E')
				img = data->tiles[TILE_MINE_ACTIVE];
			else if (data->map[y][x] == 'F')
				img = data->f_enemy.all[data->f_enemy.count];
			if (!img)
				continue ;
			if (shape_overlap(
				(t_shape){data->px, data->py - 10, TILE_SIZE, TILE_SIZE},
				(t_shape){TILE_SIZE * x - (img->width - TILE_SIZE), TILE_SIZE * y - (img->height - TILE_SIZE) - 10, img->width, img->height}))
			{
				player_img = "test";
				if (y * TILE_SIZE <= data->py)
				{
					put_img_to_img(data->img, img, TILE_SIZE * x - (img->width - TILE_SIZE), TILE_SIZE * y - (img->height - TILE_SIZE) - 10);
					put_player_img(data);
				}
				else
				{
					put_player_img(data);
					put_img_to_img(data->img, img, TILE_SIZE * x - (img->width - TILE_SIZE), TILE_SIZE * y - (img->height - TILE_SIZE) - 10);
				}
			}
			else
				put_img_to_img(data->img, img, TILE_SIZE * x - (img->width - TILE_SIZE), TILE_SIZE * y - (img->height - TILE_SIZE) - 10);
		}
	}
	if (!player_img)
		put_player_img(data);
}
