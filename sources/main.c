/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 11:06:04 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/13 11:00:07 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_tiles(t_data *data)
{
	data->tiles[TILE_GROUND] = img_init(data->mlx, "./textures/ground.xpm");
	data->tiles[TILE_PLAYER] = img_init(data->mlx, "./textures/player.xpm");
	data->tiles[TILE_KEY] = img_init(data->mlx, "./textures/key.xpm");
	data->ts_wall = init_tileset(data->mlx, 9, "./textures/wall/");
	data->ts_exit = init_tileset(data->mlx, 2, "./textures/exit/");
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
	mlx_loop_hook(data.mlx, loop_handler, &data);
	mlx_hook(data.win, DestroyNotify, NoEventMask, handle_close_event, &data);
	mlx_key_hook(data.win, key_handler, &data);
	mlx_loop(data.mlx);
}
