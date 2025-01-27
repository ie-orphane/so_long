/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:01:26 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/27 11:01:59 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "random.h"

int	randint(int min, int max)
{
	return (rand() % (max - min + 1) + min);
}

bool	randbool(int prob)
{
	return (rand() % prob == 0);
}
