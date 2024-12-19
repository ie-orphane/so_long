/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_events.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:09:56 by ielyatim          #+#    #+#             */
/*   Updated: 2024/12/19 11:55:19 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* This function needs to exist, but it is useless for the moment */
int handle_no_event(void *data)
{
	(void)data;
	return (0);
}

int handle_close_event(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	return (0);
}

int handle_keypress_event(int keycode, t_data *data)
{
	int next_x;
	int next_y;

	ft_printf("%d\n", keycode);
	if (keycode == XK_Escape)
		return (handle_close_event(data));
	next_x = data->map->x;
	next_y = data->map->y;
	if (keycode == XK_d)
		next_x += 1;
	else if (keycode == XK_w)
		next_y -= 1;
	else if (keycode == XK_a)
		next_x -= 1;
	else if (keycode == XK_s)
		next_y += 1;
	if (ft_strchr("C0", data->map->blocks[next_y][next_x]) != NULL)
	{
		if (data->map->blocks[next_y][next_x] == 'C')
			data->collective += 1;
		mlx_clear_window(data->mlx, data->win);
		data->map->blocks[data->map->y][data->map->x] = '0';
		data->map->x = next_x;
		data->map->y = next_y;
		data->map->blocks[data->map->y][data->map->x] = 'P';
	}
	return (0);
}
