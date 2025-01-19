/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiles_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 10:50:22 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/19 18:19:04 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"

static t_img	**init_tileset(t_data *data, int max, char *dir)
{
	int		i;
	char	*img_path;
	t_img	**tileset;

	tileset = malloc(sizeof(t_img *) * max);
	i = 0;
	while (i < max)
	{
		img_path = filename_to_path(dir, i);
		tileset[i] = img_init(data->mlx, img_path);
		free(img_path);
		i++;
	}
	return (tileset);
}

void	init_tiles(t_data *data)
{
	data->tiles[TILE_GOLD] = img_init(data->mlx, "./textures/gold.xpm");
	data->tiles[TILE_COLON] = img_init(data->mlx, "./textures/colon.xpm");
	data->tiles[TILE_SEMI_COLON] = img_init(data->mlx,
			"./textures/semi-colon.xpm");
	data->tiles[TILE_PERIOD] = img_init(data->mlx, "./textures/period.xpm");
	data->tiles[TILE_WATER] = img_init(data->mlx, "./textures/water.xpm");
	data->tiles[TILE_MINE_DESTROYED] = img_init(data->mlx,
			"./textures/mine/destroyed.xpm");
	data->tiles[TILE_MINE_ACTIVE] = img_init(data->mlx,
			"./textures/mine/active.xpm");
	data->ts_ground = init_tileset(data, 16, "./textures/grass/green/");
	data->ts_numbers = init_tileset(data, 10, "./textures/numbers/");
	data->ts_letters = init_tileset(data, 26, "./textures/letters/");
	data->ts_banner = init_tileset(data, 3, "./textures/ribbon/white/");
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

void	destroy_tiles(t_data *data)
{
	int	i;

	i = -1;
	while (++i < TILES_MAX)
		img_destroy(data->mlx, &data->tiles[i]);
	i = -1;
	while (++i < 16)
		img_destroy(data->mlx, &data->ts_ground[i]);
	free(data->ts_ground);
	i = -1;
	while (++i < 10)
		img_destroy(data->mlx, &data->ts_numbers[i]);
	free(data->ts_numbers);
	i = -1;
	while (++i < 26)
		img_destroy(data->mlx, &data->ts_letters[i]);
	free(data->ts_letters);
	i = -1;
	while (++i < 3)
		img_destroy(data->mlx, &data->ts_banner[i]);
	free(data->ts_banner);
	img_destroy(data->mlx, &data->img);
}

void	ft_ultimate_error(t_data *data, char *msg)
{
	ft_printf(ERROR_START "%s" ERROR_END, msg);
	ft_exit(data, 1);
}
