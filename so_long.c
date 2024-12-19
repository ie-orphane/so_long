/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:40:10 by ielyatim          #+#    #+#             */
/*   Updated: 2024/12/19 11:38:13 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*init_image(void *mlx_ptr, char *img_path)
{
	void	*img_ptr;
	int		img_width;
	int		img_height;

	img_ptr = mlx_xpm_file_to_image(
		mlx_ptr,
		img_path,
		&img_width,
		&img_height);
	if (img_height != BLOCK_SIZE || img_width != BLOCK_SIZE)
	{
		free(mlx_ptr);
		free(img_ptr);
		return (NULL);
	}
	return (img_ptr);
}

void init_images(t_data *data)
{
	dict_add(&data->imgs, 'P', init_image(data->mlx, "./p96x96.xpm"));
	dict_add(&data->imgs, '1', init_image(data->mlx, "./w96x96.xpm"));
	dict_add(&data->imgs, 'C', init_image(data->mlx, "./c96x96.xpm"));
}

int render(t_data *data)
{
	int x;
	int y;

	y = 0;
	while (y < data->map->height)
	{
		x = 0;
		while (x < data->map->width)
		{
			if (ft_strchr("1PC", data->map->blocks[y][x]))
				mlx_put_image_to_window(
					data->mlx,
					data->win,
					dict_find(&data->imgs, data->map->blocks[y][x]),
					BLOCK_SIZE * x,
					BLOCK_SIZE * y);
			x++;
		}
		y++;
	}
	return (0);
}

int	main(void)
{
	t_data	data;

	data.map = read_map("./map.ber");
	data.mlx = mlx_init();
	data.imgs = NULL;
	if (data.mlx == NULL)
	{
		ft_printf("Error\n");
		return (MLX_ERROR);
	}
	data.win = mlx_new_window(
		data.mlx,
		data.map->width * BLOCK_SIZE,
		data.map->height * BLOCK_SIZE,
		WIN_TITLE);
	if (data.win == NULL)
	{
		ft_printf("Error\n");
		free(data.mlx);
		return (MLX_ERROR);
	}
	init_images(&data);
	mlx_loop_hook(data.mlx, &handle_no_event, &data);
	mlx_loop_hook(data.mlx, &render, &data);
	mlx_key_hook(data.win, &handle_keypress_event, &data);
	mlx_hook(data.win, DestroyNotify, NoEventMask, handle_close_event, &data);
	mlx_loop(data.mlx);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
	return (0);
}
