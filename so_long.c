/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:40:10 by ielyatim          #+#    #+#             */
/*   Updated: 2024/12/17 18:09:38 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_img	*put_image(t_data *data, char *path, int x, int y)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (img == NULL)
		return (NULL);
	img->height = 0;
	img->width = 0;
	img->self = mlx_xpm_file_to_image(data->mlx, path, &img->width, &img->height);
	mlx_put_image_to_window(data->mlx, data->win, img->self, img->width * x, img->height * y);
	return (img);
}

int	main(void)
{
	t_data	data;
	t_map	*map;

	map = read_map("./map.ber");
	if (map->width * 96 > WIN_WIDTH || map->height * 96 > WIN_HEIGHT)
	{
		printf("map too big\n");
		return (MLX_ERROR);
	}
	data.mlx = mlx_init();
	if (data.mlx == NULL)
	{
		ft_printf("Error\n");
		return (MLX_ERROR);
	}
	data.win = mlx_new_window(data.mlx, map->width * 96, map->height * 96, WIN_TITLE);
	if (data.win == NULL)
	{
		ft_printf("Error\n");
		free(data.mlx);
		return (MLX_ERROR);
	}
	int y = 0;
	while (y < map->height)
	{
		int x = 0;
		while (x < map->width)
		{
			if (map->blocks[y][x] == '1')
				put_image(&data, "./w96x96.xpm", x, y);
			else if (map->blocks[y][x] == 'P')
				put_image(&data, "./p96x96.xpm", x, y);
			else if (map->blocks[y][x] == 'C')
				put_image(&data, "./c96x96.xpm", x, y);
			x++;
		}
		y++;
	}
	mlx_loop_hook(data.mlx, &handle_no_event, &data);
	mlx_key_hook(data.win, &handle_keypress_event, &data);
	mlx_hook(data.win, DestroyNotify, NoEventMask, handle_close_event, &data);
	mlx_loop(data.mlx);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
	return (0);
}
