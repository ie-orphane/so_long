/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:05:31 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/19 18:29:42 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/// @brief Checks the size of the line
/// @param data the game data
/// @note the line size should be the same as the first line
void	check_line_size(t_data *data)
{
	int	line_size;

	line_size = ft_strlen(data->map[data->height]);
	if (data->width == -1)
		data->width = line_size;
	else if (data->width != line_size)
		ft_ultimate_error(data, "Map is not rectangler.");
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
			data->p.x = i * TILE_SIZE;
			data->p.y = data->height * TILE_SIZE;
		}
		else if (data->map[data->height][i] == 'C')
			data->ccount += 1;
		else if (!ft_strchr("01E\n", data->map[data->height][i]))
		{
			ft_printf(ERROR_START "Invalid Block '%c'" ERROR_END,
				data->map[data->height][i]);
			ft_exit(data, 1);
		}
		i++;
	}
}

/// @brief Checks the map size
/// @param data the game data
void	check_map_size(t_data *data)
{
	if (data->width * TILE_SIZE * TILE_SCALE > WIN_WIDTH || data->height
		* TILE_SIZE * TILE_SCALE > WIN_HEIGHT)
	{
		ft_printf(ERROR_START "Map (%dx%d) overflow from the window (%dx%d)"
			ERROR_END, data->width * TILE_SIZE * TILE_SCALE, data->height
			* TILE_SIZE * TILE_SCALE, WIN_WIDTH, WIN_HEIGHT);
		ft_exit(data, 1);
	}
	if (data->ccount == 0)
		ft_ultimate_error(data, "No collectibles found");
}

/// @brief Checks if the map is closed
/// @param data the game data
void	check_path(t_data *data)
{
	int		i;
	char	*tmp;

	data->min = (t_point){.x = data->width, .y = data->height};
	data->check.content = malloc(sizeof(char *) * data->height);
	i = -1;
	while (++i < data->height)
		data->check.content[i] = ft_strdup(data->map[i]);
	flood_fill(data, (t_point){data->p.x / TILE_SIZE, data->p.y / TILE_SIZE});
	if (!data->check.player || !data->check.exit)
		ft_ultimate_error(data, "Player or Exit not found");
	if (data->check.ccount != data->ccount)
	{
		ft_printf(ERROR_START "Player cannot reach %d collectible(s)" ERROR_END,
			data->ccount - data->check.ccount);
		ft_exit(data, 1);
	}
	while (i-- > 0)
	{
		tmp = ft_strdup(data->map[i]);
		free(data->check.content[i]);
		data->check.content[i] = tmp;
	}
	flood_fill2(data, (t_point){data->p.x / TILE_SIZE, data->p.y / TILE_SIZE},
		' ', ' ');
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
					ft_ultimate_error(data, "Map is not closed");
			}
		}
		if (data->map[i][0] != '1' || data->map[i][data->width - 1] != '1')
			ft_ultimate_error(data, "Map is not closed");
	}
}
