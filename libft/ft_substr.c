/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:04:57 by ielyatim          #+#    #+#             */
/*   Updated: 2024/11/05 10:37:51 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	str_len;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (start > str_len)
		return (ft_strdup(""));
	i = 0;
	while (i < len && s[start + i])
		i++;
	str = malloc(i + 1);
	if (str)
	{
		i = 0;
		while (i < len && s[start])
			str[i++] = s[start++];
		str[i] = '\0';
	}
	return (str);
}
