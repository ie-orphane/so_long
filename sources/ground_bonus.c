/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ground_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 10:49:53 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/27 11:28:05 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"

static int	ground_index(t_data *data, t_point pos)
{
	unsigned int	index;
	const bool		top = ft_strchr("1rR", data->map[pos.y - 1][pos.x]) != NULL;
	const bool		bottom = ft_strchr("1rR", data->map[pos.y
					+ 1][pos.x]) != NULL;
	const bool		right = ft_strchr("1rR", data->map[pos.y][pos.x
					+ 1]) != NULL;
	const bool		left = ft_strchr("1rR", data->map[pos.y][pos.x
					- 1]) != NULL;

	index = (top << 3) | (left << 2) | (right << 1) | bottom;
	return (index);
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
			if (!ft_strchr("1rR", data->map[y][x]))
				img = data->ts_ground[ground_index(data, (t_point){x, y})];
			if (img)
				put_img_to_img(data->img, img, (t_point){TILE_SIZE * x,
					TILE_SIZE * y}, data->brightness);
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
			if (!ft_strchr("1rR", data->map[y][x]))
				img = data->f_foam.all[data->f_foam.count];
			else if (data->map[y][x] == 'r')
				img = data->f_rocks[1].all[data->f_rocks[1].count];
			else if (data->map[y][x] == 'R')
				img = data->f_rocks[0].all[data->f_rocks[0].count];
			if (img)
				put_img_to_img(data->img, img, (t_point){(TILE_SIZE * x) - ((82
							- 64) / 2), (TILE_SIZE * y) - ((82 - 64) / 2)},
					data->brightness);
		}
	}
}

static void	put_ribbon(t_data *data, char *str)
{
	int	x;

	put_img_to_img(data->img, data->ts_banner[0], (t_point){TILE_SIZE / 3,
		TILE_SIZE / 3}, data->brightness);
	x = -1;
	while (++x < ((24 - 5) * ((int)ft_strlen(str) + 1)) / 64)
		put_img_to_img(data->img, data->ts_banner[1], (t_point){((x + 1)
				* TILE_SIZE) + TILE_SIZE / 3, TILE_SIZE / 3}, data->brightness);
	put_img_to_img(data->img, data->ts_banner[2], (t_point){((x + 1)
			* TILE_SIZE) + TILE_SIZE / 3, TILE_SIZE / 3}, data->brightness);
}

static void	put_text(t_data *data, char *str)
{
	int		i;
	t_img	*img;

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
		else if (str[i] == ';')
			img = data->tiles[TILE_SEMI_COLON];
		if (img)
			put_img_to_img(data->img, img, (t_point){(img->width - 5) * i
				+ TILE_SIZE, (TILE_SIZE + img->width) / 3}, data->brightness);
		i++;
	}
}

void	put_ground_layers(t_data *data)
{
	int		x;
	int		y;
	char	*str;
	char	*tmp;
	t_img	*img;

	y = -1;
	while (++y < data->height)
	{
		x = -1;
		while (++x < data->width)
			put_img_to_img(data->img, data->tiles[TILE_WATER],
				(t_point){TILE_SIZE * x, TILE_SIZE * y}, data->brightness);
	}
	put_foam(data);
	put_ground(data);
	if (data->c.x != -1 && data->c.y != -1)
	{
		img = data->f_gold.all[data->f_gold.count];
		put_img_to_img(data->img, img, (t_point){(data->c.x * TILE_SIZE)
			- ((img->width - TILE_SIZE) / 2), (data->c.y * TILE_SIZE)
			- ((img->height - TILE_SIZE) / 2) - 15}, data->brightness);
	}
	tmp = ft_itoa(data->steps / SPEED);
	str = ft_strsjoin((char *[]){"steps:", tmp, ";", NULL});
	free(tmp);
	put_ribbon(data, str);
	put_text(data, str);
	free(str);
}
