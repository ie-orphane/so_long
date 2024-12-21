/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:09:56 by ielyatim          #+#    #+#             */
/*   Updated: 2024/12/20 10:16:41 by ielyatim         ###   ########.fr       */
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

int key_down(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		return (handle_close_event(data));
	if (keycode >= 0 && keycode < 256)
		data->keys[keycode] = 1;
	return 0;
}

int key_up(int keycode, t_data *data)
{
	if (keycode >= 0 && keycode < 256)
		data->keys[keycode] = 0;
	return 0;
}
