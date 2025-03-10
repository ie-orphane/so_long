/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 20:20:13 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/18 21:17:25 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(const char *str, char c)
{
	int	i;
	int	count;

	i = -1;
	count = 1;
	while (str[++i] != '\0')
	{
		if (str[i] != c)
			continue ;
		count++;
	}
	return (count);
}

static char	*ft_walloc(const char *str, char c, size_t *i)
{
	size_t	j;
	char	*dest;

	j = 0;
	while (str[*i + j] != '\0' && str[*i + j] != c)
		j++;
	dest = malloc((j + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	j = 0;
	while (str[*i] != '\0' && str[*i] != c)
	{
		dest[j] = str[*i];
		(*i)++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

char	**ft_free(char **arr, size_t count)
{
	while (count > 0)
	{
		free(arr[count - 1]);
		count--;
	}
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	k;
	char	**arr;

	if (!s)
		return (NULL);
	arr = malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (arr)
	{
		i = 0;
		k = 0;
		while (i < ft_strlen(s))
		{
			arr[k] = ft_walloc(s, c, &i);
			if (!arr[k])
				return (ft_free(arr, k));
			k++;
			i++;
		}
		arr[k] = NULL;
	}
	return (arr);
}
