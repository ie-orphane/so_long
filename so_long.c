/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:40:10 by ielyatim          #+#    #+#             */
/*   Updated: 2024/12/16 11:12:23 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_no_event(void *data)
{
	(void)data;
	/* This function needs to exist, but it is useless for the moment */
	return (0);
}

int keypress_hook(int keycode, t_data *data)
{
	if (keycode == 65307)
		mlx_destroy_window(data->mlx, data->win);
	ft_printf("%d\n", keycode);
	return (0);
}

int main() {
	t_data	data;

	data.mlx = mlx_init();

	data.win = mlx_new_window(data.mlx, WINDOW_WIDTH / 2, WINDOW_HEIGHT, WINDOW_TITLE);

	mlx_key_hook(data.win, keypress_hook, &data);
	mlx_loop_hook(data.mlx, &handle_no_event, &data);

	mlx_loop(data.mlx);

	mlx_destroy_display(data.mlx);
	free(data.mlx);
	return (0);
}
