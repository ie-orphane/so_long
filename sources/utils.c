/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 09:53:27 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/03 11:20:36 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* 
 * read all bytes of a file
 * 
 * @return content of file or NULL if read fails
 */
char	*read_file(char *fpath)
{
	int			fd;
	char		*stock;
	char		*tmp;
	char		buffer[1024];
	ssize_t		bytes_read;

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

/* 
 * check that all characters in str are included in the set
 * 
 * @return index of non charachter or -1 if not found
 */
int	ft_strset(const char *str, const char *set)
{
	size_t	i;

	i = 0;
	while (str[i] != 0)
	{
		if (ft_strchr(set, str[i]) == NULL)
			return (i);
		i++;
	}
	return (-1);
}

char	*filename_to_path(const char *dir, int index)
{
	char	*path;
	char	*num;
	size_t	pathsize;

	num = ft_itoa(index);
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

int	randint(int min, int max)
{
	return rand() % (max - min + 1) + min;
}
