/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:40:10 by ielyatim          #+#    #+#             */
/*   Updated: 2024/12/17 15:34:03 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(void)
{
	t_data	data;

	data.mlx = mlx_init();
	if (data.mlx == NULL)
	{
		ft_printf("Error\n");
		return (MLX_ERROR);
	}
	data.win = mlx_new_window(data.mlx, WIN_WIDTH / 2, WIN_HEIGHT, WIN_TITLE);
	if (data.win == NULL)
	{
		ft_printf("Error\n");
		free(data.mlx);
		return (MLX_ERROR);
	}
	mlx_loop_hook(data.mlx, &handle_no_event, &data);
	mlx_key_hook(data.win, &handle_keypress_event, &data);
	mlx_hook(data.win, DestroyNotify, NoEventMask, handle_close_event, &data);
	mlx_loop(data.mlx);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
	return (0);
}
