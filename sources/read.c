/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 21:33:22 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/20 11:55:10 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_error(char *msg)
{
	ft_printf(ERROR_START "%s" ERROR_END, msg);
	exit(1);
}

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

/// @brief Reads the map file and splits its content into an array of strings
/// @param fpath the file path
/// @return an array of strings representing the map or exits if read fails
char	**read_map(char *fpath)
{
	char	*content;
	char	*tmp;
	char	**arr;

	if (ft_strncmp(fpath + (ft_strlen(fpath) - 4), ".ber", 4))
		ft_error("Invalid map file");
	content = read_file(fpath);
	if (!content)
		ft_error("Failed to read the map");
	tmp = ft_strtrim(content, "\n");
	free(content);
	if (!tmp)
		ft_error("Failed to read the map");
	arr = ft_split(tmp, '\n');
	free(tmp);
	if (!tmp)
		ft_error("Failed to read the map");
	return (arr);
}
