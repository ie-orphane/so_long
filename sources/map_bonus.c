/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 10:50:14 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/13 17:31:40 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"

/// @brief Flood fill algorithm to fill the map
/// @param data the game data
/// @param x the x position
/// @param y the y position
void	flood_fill(t_data *data, int x, int y)
{
	const char	key = data->check.content[y][x];

	if (key == ' ' || key == '1')
		return ;
	if (data->map[y][x] == 'C')
		data->check.ccount += 1;
	if ((key == 'E' && data->check.exit) || (key == 'P' && data->check.player))
	{
		ft_printf("Error\nExtra '%c' found in %d, %d\n", key, x, y);
		ft_exit(data, 0);
	}
	if (data->map[y][x] == 'E')
	{
		data->check.exit = true;
		data->check.content[y][x] = '1';
		flood_fill(data, x, y);
		return ;
	}
	if (data->map[y][x] == 'P')
		data->check.player = true;
	data->check.content[y][x] = ' ';
	flood_fill(data, x + 1, y);
	flood_fill(data, x - 1, y);
	flood_fill(data, x, y + 1);
	flood_fill(data, x, y - 1);
}

/// @brief Reads the map from the file
/// @param data the game data
/// @param fpath the file path
void	parse_map(t_data *data, char *fpath)
{
	char	*content;

	content = read_file(fpath);
	if (!content)
	{
		ft_printf("Error\nFailed open to the map file\n");
		exit(1);
	}
	data->map = ft_split(content, '\n');
	free(content);
	if (!data->map)
	{
		ft_printf("Error\nFailed read to the map\n");
		exit(1);
	}
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
