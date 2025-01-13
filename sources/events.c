/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 10:49:33 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/12 22:28:18 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	handle_close_event(void)
{
	exit(0);
	return (0);
}

int	keyin(int keycode, int arr[])
{
	int	i;

	i = 0;
	while (arr[i] != -1)
	{
		if (keycode == arr[i])
			return (1);
		i++;
	}
	return (0);
}
