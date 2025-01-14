/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 10:55:29 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/14 11:32:16 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/// @brief Reads the file
/// @param fpath the file path
/// @return the file content or NULL if read fails
char	*read_file(char *fpath)
{
	int		fd;
	char	*stock;
	char	*tmp;
	char	buffer[1024];
	ssize_t	bytes_read;

	fd = open(fpath, O_RDONLY);
	stock = NULL;
	while (fd != -1)
	{
		bytes_read = read(fd, buffer, 1023);
		if (bytes_read == 0)
			break ;
		if (bytes_read < 0)
		{
			free(stock);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		tmp = ft_strjoin(stock, buffer);
		free(stock);
		stock = tmp;
	}
	return (stock);
}

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

/// @brief Concatenates an array of strings into a single string.
/// @param strs A NULL-terminated array of strings to be concatenated.
/// @return A newly allocated string containing the concatenated
///			result of all strings in the array.
///			If the array is empty or allocation fails, returns NULL.
/// @note The caller is responsible for freeing the returned string.
char	*ft_ultimate_strjoin(char **strs)
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
