/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:58:54 by ielyatim          #+#    #+#             */
/*   Updated: 2024/10/31 12:43:54 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_instr(const char c, const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	s1_len;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (s1[i] && ft_instr(s1[i], set) == 1)
		i++;
	j = ft_strlen(s1);
	while (s1[j - 1] && ft_instr(s1[j - 1], set) == 1)
		j--;
	if (j < i)
		return (ft_strdup(""));
	s1_len = j - i;
	str = malloc(s1_len + 1);
	if (str)
	{
		j = 0;
		while (j < s1_len)
			str[j++] = s1[i++];
		str[j] = '\0';
	}
	return (str);
}
