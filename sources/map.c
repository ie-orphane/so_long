/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:06:56 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/05 12:18:11 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* 
 * checks the length of a line in the map
 * 
 * all lines should have the same length
 */
static void	check_line_size(t_map **map)
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
			line_size - map_cpy->width,
			map_cpy->height,
			map_cpy->blocks[map_cpy->height]);
		exit(1);
	}
	else if (map_cpy->width > line_size)
	{
		ft_printf("Error\nMissing %d block(s) in %d:'%s'\n",
			map_cpy->width - line_size,
			map_cpy->height,
			map_cpy->blocks[map_cpy->height]);
		exit(1);
	}
}

/* 
 * checks the blocks of a line in the map
 * 
 * the map should contains only '0', '1', 'C', 'E', 'P'
 */
static void	check_blocks(t_data *data, t_map **map)
{
	t_map	*map_cpy;
	size_t	i;

	map_cpy = *map;
	i = 0;
	while (map_cpy->blocks[map_cpy->height][i] != 0)
	{
		if (map_cpy->blocks[map_cpy->height][i] == 'P')
		{
			data->px = i * TILE_SIZE;
			data->py = map_cpy->height * TILE_SIZE;
		}
		else if (map_cpy->blocks[map_cpy->height][i] == 'C')
			data->ccount += 1;
			// map_cpy->collective += 1;
		else if (ft_strchr("01EF\n", map_cpy->blocks[map_cpy->height][i]) == NULL)
		{
			ft_printf("Error\nUnknown block '%c' found in %d:%d:'%s'\n",
			map_cpy->blocks[map_cpy->height][i],
			map_cpy->height,
			i, map_cpy->blocks[map_cpy->height]);
			exit(1);
		}
		i++;
	}
}

/* 
 * checks the height and width of the map
 * 
 * the max size of the map should be the screen size
 */
void	check_map_size(t_map *map)
{
	if (map->width * TILE_SIZE > WIN_WIDTH
		|| map->height * TILE_SIZE > WIN_HEIGHT)
	{
		printf("Error\nMap (%dx%d) overflow from the window  (%dx%d)\n",
			map->width * TILE_SIZE,
			map->height * TILE_SIZE,
			WIN_WIDTH,
			WIN_HEIGHT);
		exit(1);
	}
}

t_map	*read_map(t_data *data, char *fpath)
{
	t_map	*map;
	char	*content;
	char	**blocks;

	map = malloc(sizeof(t_map));
	content = read_file(fpath);
	blocks = ft_split(content, '\n');
	free(content);

	map->width = -1;
	map->height = -1;
	map->blocks = blocks;
	// map->collective = 0;
	data->ccount = 0;
	data->px = -1;
	data->py = -1;
	while (blocks[++map->height])
	{
		check_line_size(&map);
		check_blocks(data, &map);
	}
	check_map_size(map);
	return (map);
}
