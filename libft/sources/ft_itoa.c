/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 21:47:14 by ielyatim          #+#    #+#             */
/*   Updated: 2024/10/31 14:50:06 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(long nbr)
{
	int	size;

	if (nbr == 0)
		return (2);
	size = 0;
	if (nbr < 0)
	{
		size += 1;
		nbr *= -1;
	}
	while (nbr > 0)
	{
		size++;
		nbr /= 10;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	long	nbr;
	char	*str;
	int		size;

	nbr = (long)n;
	if (nbr == 0)
		return (ft_strdup("0"));
	size = ft_size(nbr);
	str = malloc(size + 1);
	if (str)
	{
		if (nbr < 0)
		{
			str[0] = '-';
			nbr *= -1;
		}
		str[size] = '\0';
		while (nbr > 0)
		{
			str[--size] = nbr % 10 + 48;
			nbr /= 10;
		}
	}
	return (str);
}
