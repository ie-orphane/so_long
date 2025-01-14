/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 10:49:27 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/14 12:30:23 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"

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
	{
		ft_printf("Error\nExtra %d block(s) in %d:'%s'\n", line_size
			- data->width, data->height, data->map[data->height]);
		ft_exit(data, 1);
	}
	else if (data->width > line_size)
	{
		ft_printf("Error\nMissing %d block(s) in %d:'%s'\n", data->width
			- line_size, data->height, data->map[data->height]);
		ft_exit(data, 1);
	}
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
		{
			ft_printf("Error\nInvalid Block '%c' in %d, %d\n",
				data->map[data->height][i], data->height, i);
			ft_exit(data, 1);
		}
		i++;
	}
}

/// @brief Checks the map size
/// @param data the game data
void	check_map_size(t_data *data)
{
	if (data->width * TILE_SIZE > WIN_WIDTH || data->height
		* TILE_SIZE > WIN_HEIGHT)
	{
		ft_printf("Error\nMap (%dx%d) overflow from the window (%dx%d)\n",
			data->width * TILE_SIZE, data->height * TILE_SIZE, WIN_WIDTH,
			WIN_HEIGHT);
		ft_exit(data, 1);
	}
	if (data->ccount == 0)
	{
		ft_printf("Error\nNo collectibles found\n");
		ft_exit(data, 1);
	}
}

/// @brief Checks if the map is closed
/// @param data the game data
void	check_path(t_data *data)
{
	int	i;

	data->check.content = malloc(sizeof(char *) * data->height);
	i = -1;
	while (++i < data->height)
		data->check.content[i] = ft_strdup(data->map[i]);
	flood_fill(data, data->px / TILE_SIZE, data->py / TILE_SIZE);
	if (!data->check.player)
	{
		ft_printf("Error\nPlayer not found\n");
		ft_exit(data, 1);
	}
	if (!data->check.exit)
	{
		ft_printf("Error\nExit not found\n");
		ft_exit(data, 1);
	}
	if (data->check.ccount != data->ccount)
	{
		ft_printf("Error\nPlayer cannot reach %d collectible(s)\n", data->ccount
			- data->check.ccount);
		ft_exit(data, 1);
	}
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
				{
					ft_printf("Error\nMap is not closed\n");
					ft_exit(data, 1);
				}
			}
		}
		if (data->map[i][0] != '1' || data->map[i][data->width - 1] != '1')
		{
			ft_printf("Error\nMap is not closed\n");
			ft_exit(data, 1);
		}
	}
}
