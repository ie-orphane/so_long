/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:06:56 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/09 14:31:28 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/// @brief Flood fill algorithm to fill the map
/// @param data the game data
/// @param x the x position
/// @param y the y position
void	flood_fill(t_data *data, t_map_check *map, int x, int y)
{
	if (x < 0 || y < 0 || x >= data->width || y >= data->height
		|| map->content[y][x] == ' ' || map->content[y][x] == '1')
		return ;
	if (data->map[y][x] == 'C')
		map->ccount += 1;
	if ((map->content[y][x] == 'E' && map->exit) || (map->content[y][x] == 'P'
			&& map->player))
		ft_error("Extra '%c' found in %d, %d\n", map->content[y][x], x, y);
	if (data->map[y][x] == 'E')
	{
		map->exit = true;
		map->content[y][x] = '1';
		flood_fill(data, map, x, y);
		return ;
	}
	if (data->map[y][x] == 'P')
		map->player = true;
	map->content[y][x] = ' ';
	flood_fill(data, map, x + 1, y);
	flood_fill(data, map, x - 1, y);
	flood_fill(data, map, x, y + 1);
	flood_fill(data, map, x, y - 1);
}

/// @brief Reads the map from the file
/// @param data the game data
/// @param fpath the file path
void	parse_map(t_data *data, char *fpath)
{
	char	*content;

	content = read_file(fpath);
	if (!content)
		ft_error("Cannot read the map file\n");
	data->map = ft_split(content, '\n');
	free(content);
	if (!data->map)
		ft_error("Cannot read the map\n");
	data->width = -1;
	data->height = -1;
	while (data->map[++data->height])
	{
		check_line_size(data);
		check_blocks(data);
	}
	check_closed(data);
	check_map_size(data);
	check_path(data);
}
