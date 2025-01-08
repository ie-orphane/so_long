/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:09:56 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/08 15:54:29 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_close_event()
{
	exit(0);
	return (0);
}

int	key_down(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		exit(1);
	if (keycode >= 0 && keycode < 256)
		data->keys[keycode] = 1;
	return (0);
}

int	key_up(int keycode, t_data *data)
{
	if (keycode >= 0 && keycode < 256)
		data->keys[keycode] = 0;
	return (0);
}

int keyin(t_data *data, int arr[])
{
	int i;

	i = 0;
	while (arr[i] != -1)
	{
		if (data->keys[arr[i]])
			return (1);
		i++;
	}
	return (0);
}
