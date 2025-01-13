/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 11:15:04 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/13 17:18:02 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

static int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

static void	update_minmax(t_data *data, t_point *pos, char f)
{
	if (data->check.content[pos->y][pos->x] != '1')
		return ;
	if (f == 'x')
		data->min.x = min(data->min.x, pos->x);
	else if (f == 'X')
		data->max.x = max(data->max.x, pos->x);
	else if (f == 'y')
		data->min.y = min(data->min.y, pos->y);
	else if (f == 'Y')
		data->max.y = max(data->max.y, pos->y);
}

/// @brief Flood fill algorithm to fill the map
/// @param data the game data
/// @param x the x position
/// @param y the y position
void	flood_fill(t_data *data, t_point pos, char f)
{
	const char	key = data->check.content[pos.y][pos.x];

	if (ft_strchr(" 1", key))
		return (update_minmax(data, &pos, f));
	if (data->map[pos.y][pos.x] == 'C')
		data->check.ccount += 1;
	if ((key == 'E' && data->check.exit) || (key == 'P' && data->check.player))
	{
		ft_printf("Error\nExtra '%c' found in %d, %d\n", key, pos.x, pos.y);
		ft_exit(data, 0);
	}
	if (key == 'E')
	{
		data->check.exit = true;
		data->check.content[pos.y][pos.x] = '1';
		flood_fill(data, pos, ' ');
		return ;
	}
	if (key == 'P')
		data->check.player = true;
	data->check.content[pos.y][pos.x] = ' ';
	flood_fill(data, (t_point){pos.x + 1, pos.y}, 'X');
	flood_fill(data, (t_point){pos.x - 1, pos.y}, 'x');
	flood_fill(data, (t_point){pos.x, pos.y + 1}, 'Y');
	flood_fill(data, (t_point){pos.x, pos.y - 1}, 'y');
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
		ft_printf("Cannot open the map file\n");
		exit(1);
	}
	data->map = ft_split(content, '\n');
	free(content);
	if (!data->map)
	{
		ft_printf("Cannot read the map\n");
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
