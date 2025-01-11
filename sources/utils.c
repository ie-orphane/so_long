/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:53:27 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/11 18:48:08 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
		return (0);
	return (1);
}

/// @brief Generates a random integer between min and max
/// @param min the minimum value
/// @param max the maximum value
/// @return the random integer
int	randint(int min, int max)
{
	return (rand() % (max - min + 1) + min);
}

char	*ft_ultimate_strjoin(size_t count, ...)
{
	char	*str;
	size_t	str_size;
	va_list	strs;
	size_t	i;

	va_start(strs, count);
	str_size = 1;
	i = -1;
	while (++i < count)
		str_size += ft_strlen(va_arg(strs, char *));
	va_end(strs);
	if (str_size == 1)
		return ((char *)ft_calloc(1, 1));
	str = malloc(str_size);
	if (!str)
		return (NULL);
	va_start(strs, count);
	str[0] = '\0';
	i = -1;
	while (++i < count)
		ft_strlcat(str, (const char *)va_arg(strs, char *), str_size);
	va_end(strs);
	return (str);
}
