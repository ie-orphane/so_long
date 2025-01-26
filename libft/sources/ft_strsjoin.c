/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_strjoin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:28:59 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/23 21:56:42 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief Concatenates an array of strings into a single string.
/// @param strs A NULL-terminated array of strings to be concatenated.
/// @return A newly allocated string containing the concatenated
///			result of all strings in the array.
///			If the array is empty or allocation fails, returns NULL.
/// @note The caller is responsible for freeing the returned string.
char	*ft_strsjoin(char **strs)
{
	char	*str;
	size_t	str_size;
	size_t	i;

	str_size = 1;
	i = -1;
	while (strs[++i])
		str_size += ft_strlen(strs[i]);
	if (str_size == 1)
		return ((char *)ft_calloc(1, 1));
	str = malloc(str_size);
	if (!str)
		return (NULL);
	str[0] = '\0';
	i = -1;
	while (strs[++i])
		ft_strlcat(str, strs[i], str_size);
	return (str);
}
