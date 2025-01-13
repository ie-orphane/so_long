/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 10:49:33 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/13 18:01:56 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"

int	destroy_handler(t_data *data)
{
	ft_printf("Bye bye! See you later.\n");
	ft_exit(data, 0);
	return (0);
}

int	keypress_handler(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		return (destroy_handler(data));
	if (keycode >= 0 && keycode < 256)
		data->keys[keycode] = 1;
	return (0);
}

int	keyrelease_handler(int keycode, t_data *data)
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
