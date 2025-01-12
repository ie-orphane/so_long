/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 10:49:33 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/12 11:11:10 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	handle_close_event(void)
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

int	keyin(t_data *data, int arr[])
{
	int	i;

	i = 0;
	while (arr[i] != -1)
	{
		if (data->keys[arr[i]])
			return (1);
		i++;
	}
	return (0);
}
