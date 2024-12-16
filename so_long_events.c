/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_events.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:09:56 by ielyatim          #+#    #+#             */
/*   Updated: 2024/12/16 12:11:30 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* This function needs to exist, but it is useless for the moment */
int	handle_no_event(void *data)
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
	ft_printf("%d\n", keycode);
	if (keycode == XK_Escape)
		return handle_close_event(data);
	return (0);
}
