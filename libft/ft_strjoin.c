/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:35:25 by ielyatim          #+#    #+#             */
/*   Updated: 2024/12/18 10:26:07 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*str;
	size_t	str_size;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str_size = s1_len + s2_len + 1;
	if (s1_len + s2_len == 0)
		return ((char *)ft_calloc(1, 1));
	str = malloc(str_size);
	if (str)
	{
		str[0] = '\0';
		ft_strlcat(str, s1, str_size);
		ft_strlcat(str, s2, str_size);
	}
	return (str);
}
