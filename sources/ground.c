/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ground.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:10:25 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/09 21:34:15 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_uint	ts_ground_index(t_data *data, int x, int y)
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

static void	put_ground(t_data *data)
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
				img = data->ts_ground[ts_ground_index(data, x, y)];
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

static void	put_text(t_data *data, char *str)
{
	int		i;
	t_img	*img;

	str = ft_strjoin(str, ft_itoa(data->steps / TILE_SIZE));
	i = 0;
	while (str[i])
	{
		img = NULL;
		if ('a' <= str[i] && str[i] <= 'z')
			img = data->ts_letters[str[i] - 'a'];
		else if (str[i] == ':')
			img = data->tiles[TILE_COLON];
		else if ('0' <= str[i] && str[i] <= '9')
			img = data->ts_numbers[str[i] - '0'];
		if (img)
			put_img_to_img(data->img, img, (img->width - 5) * i + (TILE_SIZE
					/ 4), (TILE_SIZE - img->height) / 2);
		i++;
	}
	img = data->tiles[TILE_SEMI_COLON];
	put_img_to_img(data->img, img, (img->width - 5) * i + (TILE_SIZE
			/ 4), (TILE_SIZE - img->height) / 2);
	free(str);
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
	put_foam(data);
	put_ground(data);
	put_img_to_img(data->img, data->ts_banner[0], 0 * TILE_SIZE, 0);
	put_img_to_img(data->img, data->ts_banner[1], 1 * TILE_SIZE, 0);
	put_img_to_img(data->img, data->ts_banner[1], 2 * TILE_SIZE, 0);
	put_img_to_img(data->img, data->ts_banner[1], 3 * TILE_SIZE, 0);
	put_img_to_img(data->img, data->ts_banner[2], 4 * TILE_SIZE, 0);
	put_text(data, "mouvments:");
}
