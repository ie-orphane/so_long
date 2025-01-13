/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiles.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:55:51 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/13 11:44:29 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static unsigned int	get_pixel_img(t_img *img, int x, int y)
{
	return (*(unsigned int *)((img->addr + (y * img->line_length) + (x
				* img->bpp / 8))));
}

void	put_scaled_img_to_img(t_img *dst, t_img *src, t_point pixel,
		double brightness)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = -1;
	while (++i < src->width)
	{
		j = -1;
		while (++j < src->height)
		{
			y = -1;
			while (++y < TILE_SCALE)
			{
				x = -1;
				while (++x < TILE_SCALE)
				{
					put_pixel_img(dst, (i + pixel.x) * TILE_SCALE + x, (j
							+ pixel.y) * TILE_SCALE + y,
						darken_color(get_pixel_img(src, i, j), brightness));
				}
			}
		}
	}
}

t_img	**init_tileset(void *mlx_ptr, int max, char *dir)
{
	int		i;
	char	*img_path;
	t_img	**tileset;

	tileset = malloc(sizeof(t_img *) * max);
	i = 0;
	while (i < max)
	{
		img_path = filename_to_path(dir, i);
		tileset[i] = img_init(mlx_ptr, img_path);
		free(img_path);
		i++;
	}
	return (tileset);
}

void	img_destroy(void *mlx_ptr, t_img **img)
{
	if (mlx_ptr && img && (*img))
	{
		if ((*img)->ptr)
			mlx_destroy_image(mlx_ptr, (*img)->ptr);
		free(*img);
		(*img) = NULL;
	}
}

t_img	*wall_tile(t_data *data, int x, int y)
{
	int	index;

	index = 8;
	if (x == data->min.x && y == data->min.y)
		index = 0;
	else if (x == data->max.x && y == data->min.y)
		index = 2;
	else if (x == data->min.x && y == data->max.y)
		index = 6;
	else if (x == data->max.x && y == data->max.y)
		index = 4;
	else if (x == data->min.x && data->min.y < y && y < data->max.y)
		index = 7;
	else if (x == data->max.x && data->min.y < y && y < data->max.y)
		index = 3;
	else if (y == data->min.y && data->min.x < x && x < data->max.x)
		index = 1;
	else if (y == data->max.y && data->min.x < x && x < data->max.x)
		index = 5;
	return (data->ts_wall[index]);
}
