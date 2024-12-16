/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:05:25 by ielyatim          #+#    #+#             */
/*   Updated: 2024/11/01 10:04:45 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	index;
	size_t	substr_len;
	size_t	count;
	char	*str;
	char	*substr;

	str = (char *)big;
	substr = (char *)little;
	substr_len = ft_strlen(little);
	if (substr_len == 0)
		return (str);
	if (len <= 0)
		return (0);
	index = 0;
	while (str[index] && index < len)
	{
		count = 0;
		while (str[index + count] && substr[count] && str[index
				+ count] == substr[count] && index + count < len)
			count++;
		if (count == substr_len)
			return (str + index);
		index++;
	}
	return (0);
}
