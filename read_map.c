/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:06:56 by ielyatim          #+#    #+#             */
/*   Updated: 2024/12/16 21:58:39 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*read_file(int fd)
{
	char		*stock;
	char		*tmp;
	char		buffer[1024];
	ssize_t		bytes_read;

	stock = ft_strdup("");
	while (1)
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
 * @return index of non charachter or -1 if none found
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

void	check_line_size(t_map **map)
{
	t_map	*map_cpy;
	int		line_size;

	map_cpy = *map;
	line_size = ft_strlen(map_cpy->blocks[map_cpy->height]);
	if (map_cpy->width == -1)
		map_cpy->width = line_size;
	else if (map_cpy->width < line_size)
	{
		ft_printf("Error\nExtra %d block(s) in %d:'%s'\n",
			line_size - map_cpy->width, map_cpy->height, map_cpy->blocks[map_cpy->height]);
		exit(1);
	}
	else if (map_cpy->width > line_size)
	{
		ft_printf("Error\nMissing %d block(s) in %d:'%s'\n",
			map_cpy->width - line_size, map_cpy->height, map_cpy->blocks[map_cpy->height]);
		exit(1);
	}
}

void	check_blocks(t_map **map)
{
	t_map	*map_cpy;
	int		position;

	map_cpy = *map;
	position = ft_strset(map_cpy->blocks[map_cpy->height], "01CEP\n");
	if (position != -1)
	{
		ft_printf("Error\nUnknown block '%c' found in %d:%d:'%s'\n", map_cpy->blocks[map_cpy->height][position],
			map_cpy->height, position, map_cpy->blocks[map_cpy->height]);
		exit(1);
	}
}

t_map	*read_map(char *fpath)
{
	t_map	*map;
	int		fd;

	map = malloc(sizeof(t_map));
	if (!fpath)
		return (NULL);
	fd = open(fpath, O_RDONLY);
	if (fd == -1)
		return (NULL);
	map->content = read_file(fd);
	if (map->content == NULL)
		return (NULL);
	map->blocks = ft_split(map->content, '\n');
	if (map->blocks == NULL)
		return (NULL);
	map->width = -1;
	map->height = -1;
	while (map->blocks[++map->height])
	{
		check_line_size(&map);
		check_blocks(&map);
	}
	ft_printf("width = %d\nheight = %d", map->width, map->height);
	return (map);
}
