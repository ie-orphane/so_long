/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 11:06:04 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/21 18:37:36 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	destroy_tiles(t_data *data)
{
	int	i;

	i = -1;
	while (++i < TILES_MAX)
		img_destroy(data->mlx, &data->tiles[i]);
	i = -1;
	while (++i < 9)
		img_destroy(data->mlx, &data->ts_wall[i]);
	free(data->ts_wall);
	i = -1;
	while (++i < 2)
		img_destroy(data->mlx, &data->ts_exit[i]);
	free(data->ts_exit);
	img_destroy(data->mlx, &data->img);
}

void	ft_exit(t_data *data, int status)
{
	int	i;

	if (data->map)
	{
		i = -1;
		while (data->map[++i])
			free(data->map[i]);
		free(data->map);
	}
	if (data->check.content)
	{
		i = -1;
		while (++i < data->height)
			free(data->check.content[i]);
		free(data->check.content);
	}
	if (!data->mlx)
		exit(status);
	destroy_tiles(data);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(status);
}

void	ft_ultimate_error(t_data *data, char *msg)
{
	ft_printf(ERROR_START "%s" ERROR_END, msg);
	ft_exit(data, 1);
}

static void	init_tiles(t_data *data)
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

	if (argc < 2)
		ft_error("missing map argument");
	ft_bzero(&data, sizeof(t_data));
	parse_map(&data, argv[1]);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.width * TILE_SIZE * TILE_SCALE,
			data.height * TILE_SIZE * TILE_SCALE, WIN_TITLE);
	data.updated = true;
	init_tiles(&data);
	mlx_loop_hook(data.mlx, loop_handler, &data);
	mlx_hook(data.win, DestroyNotify, NoEventMask, destroy_handler, &data);
	mlx_key_hook(data.win, key_handler, &data);
	mlx_loop(data.mlx);
}
