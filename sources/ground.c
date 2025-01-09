/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ground.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:10:25 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/09 15:10:28 by ielyatim         ###   ########.fr       */
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

static void	put_water(t_data *data)
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
}

static void	put_foam(t_data *data)
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
			img = NULL;
			if (data->map[y][x] != '1')
				img = data->f_foam.all[data->f_foam.count];
			if (img)
				put_img_to_img(data->img, img, (TILE_SIZE * x) - ((82 - 64)
						/ 2), (TILE_SIZE * y) - ((82 - 64) / 2));
		}
	}
}

void	put_ground_layers(t_data *data)
{
	int		x;
	int		y;
	t_img	*img;

	put_water(data);
	put_foam(data);
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
