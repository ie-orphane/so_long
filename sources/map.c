/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 11:15:04 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/19 18:27:19 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/// @brief Compares two integer values and returns the larger one.
/// @param a The first integer value to compare.
/// @param b The second integer value to compare.
/// @return The larger of the two integer values.
static int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

/// @brief This function performs an operation on two integers.
/// @param a The first integer parameter.
/// @param b The second integer parameter.
/// @return The result of the operation as an integer.
static int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

/// @brief Flood fill algorithm to fill the map
/// @param data the game data
/// @param x the x position
/// @param y the y position
void	flood_fill(t_data *data, t_point pos)
{
	const char	key = data->check.content[pos.y][pos.x];

	if (ft_strchr(" 1", key))
		return ;
	if (data->map[pos.y][pos.x] == 'C')
		data->check.ccount += 1;
	if ((key == 'E' && data->check.exit) || (key == 'P' && data->check.player))
	{
		ft_printf(ERROR_START "Extra '%c' found" ERROR_END, key);
		ft_exit(data, 0);
	}
	if (key == 'E')
	{
		data->check.exit = true;
		data->check.content[pos.y][pos.x] = '1';
		flood_fill(data, pos);
		return ;
	}
	if (key == 'P')
		data->check.player = true;
	data->check.content[pos.y][pos.x] = ' ';
	flood_fill(data, (t_point){pos.x + 1, pos.y});
	flood_fill(data, (t_point){pos.x - 1, pos.y});
	flood_fill(data, (t_point){pos.x, pos.y + 1});
	flood_fill(data, (t_point){pos.x, pos.y - 1});
}

/// @brief Flood fill algorithm to fill the map
/// @param data the game data
/// @param x the x position
/// @param y the y position
void	flood_fill2(t_data *data, t_point pos, char f, char prev)
{
	char	key;

	if (pos.x < 0 || pos.y < 0 || pos.x >= data->width || pos.y >= data->height
		|| data->check.content[pos.y][pos.x] == ' ' || (prev == '1'
			&& data->check.content[pos.y][pos.x] == '1'))
		return ;
	key = data->check.content[pos.y][pos.x];
	if (f == 'x' && key == '1')
		data->min.x = min(data->min.x, pos.x);
	else if (f == 'X' && key == '1')
		data->max.x = max(data->max.x, pos.x);
	else if (f == 'y' && key == '1')
		data->min.y = min(data->min.y, pos.y);
	else if (f == 'Y' && key == '1')
		data->max.y = max(data->max.y, pos.y);
	data->check.content[pos.y][pos.x] = ' ';
	flood_fill2(data, (t_point){pos.x + 1, pos.y}, 'X', key);
	flood_fill2(data, (t_point){pos.x - 1, pos.y}, 'x', key);
	flood_fill2(data, (t_point){pos.x, pos.y + 1}, 'Y', key);
	flood_fill2(data, (t_point){pos.x, pos.y - 1}, 'y', key);
}

/// @brief Reads the map from the file
/// @param data the game data
/// @param fpath the file path
void	parse_map(t_data *data, char *fpath)
{
	data->map = read_map(fpath);
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
