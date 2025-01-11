/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiles.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:56:25 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/11 18:08:55 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
