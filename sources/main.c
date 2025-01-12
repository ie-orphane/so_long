/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 11:06:04 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/12 21:46:38 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

unsigned int	get_pixel_img(t_img *img, int x, int y)
{
	return (*(unsigned int *)((img->addr + (y * img->line_length) + (x
					* img->bpp / 8))));
}

void	put_scaled_img_to_img(t_img *dst, t_img *src, t_point pixel,
		double brightness, int scale)
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
			while (++y < scale)
			{
				x = -1;
				while (++x < scale)
				{
					put_pixel_img(dst, (i * scale) + pixel.x + x, (j * scale)
						+ pixel.y + y, darken_color(get_pixel_img(src, i, j),
							brightness));
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

void	init_tiles(t_data *data)
{
	data->tiles[TILE_GROUND] = img_init(data->mlx, "./textures/ground.xpm");
	data->tiles[TILE_PLAYER] = img_init(data->mlx, "./textures/player.xpm");
	data->tiles[TILE_KEY] = img_init(data->mlx, "./textures/key.xpm");
	data->ts_wall = init_tileset(data->mlx, 9, "./textures/wall/");
}

t_img	*wall_tile(t_data *data, int x, int y)
{
	int			i;
	const int	walls[] = {3, 6, 18, 24, 56, 44, 41, 9, 12, -1};

	i = -1;
	while (walls[++i] != -1)
	{
		if (walls[i] == ((y == data->height - 1) << 5 | (x == data->width
					- 1) << 4 | (0 < y && y < data->height) << 3 | (0 < x
					&& x < data->width - 1) << 2 | (y == 0) << 1 | (x == 0)))
			return (data->ts_wall[i]);
	}
	return (NULL);
}

int	update_animation(t_data *data)
{
	int		x;
	int		y;
	t_img	*img;

	if (!data->updated)
		return (0);
	if (data->img)
	{
		mlx_destroy_image(data->mlx, data->img->ptr);
		free(data->img);
	}
	data->img = img_new(data->mlx, data->width * TILE_SIZE * TILE_SCALE,
			data->height * TILE_SIZE * TILE_SCALE);
	y = -1;
	while (++y < data->height)
	{
		x = -1;
		while (++x < data->width)
		{
			img = data->tiles[TILE_GROUND];
			put_scaled_img_to_img(data->img, img, (t_point){x * TILE_SIZE
				* TILE_SCALE, y * TILE_SIZE * TILE_SCALE}, data->brightness,
				TILE_SCALE);
			img = NULL;
			if (data->map[y][x] == '1')
				img = wall_tile(data, x, y);
			else if (data->map[y][x] == 'P')
				img = data->tiles[TILE_PLAYER];
			else if (data->map[y][x] == 'C')
				img = data->tiles[TILE_KEY];
			if (img)
				put_scaled_img_to_img(data->img, img, (t_point){x * TILE_SIZE
					* TILE_SCALE, y * TILE_SIZE * TILE_SCALE}, data->brightness,
					TILE_SCALE);
		}
	}
	mlx_clear_window(data->mlx, data->win);
	mlx_put_image_to_window(data->mlx, data->win, data->img->ptr, 0, 0);
	data->updated = false;
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc < 1)
		return (0);
	ft_bzero(&data, sizeof(t_data));
	parse_map(&data, argv[1]);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.width * TILE_SIZE * TILE_SCALE,
			data.height * TILE_SIZE * TILE_SCALE, WIN_TITLE);
	data.updated = true;
	init_tiles(&data);
	mlx_loop_hook(data.mlx, update_animation, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, key_down, &data);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, key_up, &data);
	mlx_hook(data.win, DestroyNotify, NoEventMask, handle_close_event, &data);
	mlx_loop(data.mlx);
}
