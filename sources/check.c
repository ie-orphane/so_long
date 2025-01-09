/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:29:57 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/09 15:42:34 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/// @brief Checks the size of the line
/// @param data the game data
/// @note the line size should be the same as the first line
void	check_line_size(t_data *data)
{
	int	line_size;

	line_size = ft_strlen(data->map[data->height]);
	if (data->width == -1)
		data->width = line_size;
	else if (data->width < line_size)
		ft_error("Error\nExtra %d block(s) in %d:'%s'\n", line_size
			- data->width, data->height, data->map[data->height]);
	else if (data->width > line_size)
		ft_error("Missing %d block(s) in %d:'%s'\n", data->width - line_size,
			data->height, data->map[data->height]);
}

/// @brief Checks the blocks in the map
/// @param data the game data
void	check_blocks(t_data *data)
{
	size_t	i;

	i = 0;
	while (data->map[data->height][i])
	{
		if (data->map[data->height][i] == 'P')
		{
			data->px = i * TILE_SIZE;
			data->py = data->height * TILE_SIZE;
		}
		else if (data->map[data->height][i] == 'C')
			data->ccount += 1;
		else if (!ft_strchr("01EF\n", data->map[data->height][i]))
			ft_error("Invalid Block '%c' in %d, %d\n",
				data->map[data->height][i], data->height, i);
		i++;
	}
}

/// @brief Checks the map size
/// @param data the game data
void	check_map_size(t_data *data)
{
	if (data->width * TILE_SIZE > WIN_WIDTH || data->height
		* TILE_SIZE > WIN_HEIGHT)
		ft_error("Map (%dx%d) overflow from the window  (%dx%d)\n", data->width
			* TILE_SIZE, data->height * TILE_SIZE, WIN_WIDTH, WIN_HEIGHT);
	if (data->ccount == 0)
		ft_error("No collectibles found\n");
}

/// @brief Checks if the map is closed
/// @param data the game data
void	check_path(t_data *data)
{
	int			i;
	t_map_check	map;

	ft_bzero(&map, sizeof(t_map_check));
	map.content = malloc(sizeof(char *) * data->height);
	i = -1;
	while (++i < data->height)
		map.content[i] = ft_strdup(data->map[i]);
	flood_fill(data, &map, data->px / TILE_SIZE, data->py / TILE_SIZE);
	if (!map.player)
		ft_error("Player not found\n");
	if (!map.exit)
		ft_error("Exit not found\n");
	if (map.ccount != data->ccount)
		ft_error("Player cannot reach all collectibles\n");
	i = -1;
	while (++i < data->height)
		free(map.content[i]);
	free(map.content);
}

/// @brief Checks if the map is closed
/// @param data the game data
void	check_closed(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->height)
	{
		if (i == 0 || i == data->height - 1)
		{
			j = -1;
			while (++j < data->width)
			{
				if (data->map[i][j] != '1')
					ft_error("Map is not closed\n");
			}
		}
		if (data->map[i][0] != '1' || data->map[i][data->width - 1] != '1')
			ft_error("Map is not closed\n");
	}
}
