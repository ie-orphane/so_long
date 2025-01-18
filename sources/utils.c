/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 10:55:29 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/18 21:40:11 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/// @brief Converts a filename to a path
/// @param dir the directory
/// @param index the index
/// @return the path
/// @note if the allocation fails, the function returns NULL
char	*filename_to_path(const char *dir, int index)
{
	char	*path;
	char	*num;
	size_t	pathsize;

	num = ft_itoa(index);
	if (!num)
		return (NULL);
	pathsize = ft_strlen(dir) + ft_strlen(num) + 5;
	path = malloc(pathsize * sizeof(char));
	if (path)
	{
		ft_strlcpy(path, dir, pathsize);
		ft_strlcat(path, num, pathsize);
		ft_strlcat(path, ".xpm", pathsize);
	}
	free(num);
	return (path);
}

/// @brief Checks if two shapes overlap
/// @param a the first shape
/// @param b the second shape
/// @return true if overlap, false otherwise
bool	shape_overlap(t_shape a, t_shape b)
{
	if (a.x >= b.x + b.w || b.x >= a.x + a.w || a.y >= b.y + b.h || b.y >= a.y
		+ a.h)
		return (false);
	return (true);
}

/// @brief compares two double values and returns the smaller one.
/// @param a The first double value to compare.
/// @param b The second double value to compare.
/// @return The smaller of the two double values.
double	dmin(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}
