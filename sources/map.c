/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:06:56 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/08 21:13:51 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * checks the size of the line in the map
 *
 * @param data the game data
 * @note the line size should be the same as the first line
 */
static void	check_line_size(t_data *data)
{
	int	line_size;

	line_size = ft_strlen(data->map[data->height]);
	if (data->width == -1)
		data->width = line_size;
	else if (data->width < line_size)
	{
		ft_printf("Error\nExtra %d block(s) in %d:'%s'\n", line_size
			- data->width, data->height, data->map[data->height]);
		exit(1);
	}
	else if (data->width > line_size)
	{
		ft_printf("Error\nMissing %d block(s) in %d:'%s'\n", data->width
			- line_size, data->height, data->map[data->height]);
		exit(1);
	}
}

/*
 * checks the blocks in the map
 *
 * @note the blocks should be 'P', 'C', 'E', 'F', '1', '0' or '\\n'
 * @param data the game data
 */
static void	check_blocks(t_data *data)
{
	size_t	i;

	i = 0;
	while (data->map[data->height][i] != 0)
	{
		if (data->map[data->height][i] == 'P')
		{
			data->px = i * TILE_SIZE;
			data->py = data->height * TILE_SIZE;
		}
		else if (data->map[data->height][i] == 'C')
			data->ccount += 1;
		else if (ft_strchr("01EF\n", data->map[data->height][i]) == NULL)
		{
			ft_printf("Error\nUnknown block '%c' found in %d:%d:'%s'\n",
				data->map[data->height][i], data->height, i,
				data->map[data->height]);
			exit(1);
		}
		i++;
	}
}

/*
 * checks the size of the map
 *
 * @param data the game data
 * @note the map size should not overflow the window size
 */
void	check_map_size(t_data *data)
{
	if (data->width * TILE_SIZE > WIN_WIDTH || data->height
		* TILE_SIZE > WIN_HEIGHT)
	{
		printf("Error\nMap (%dx%d) overflow from the window  (%dx%d)\n",
			data->width * TILE_SIZE, data->height * TILE_SIZE, WIN_WIDTH,
			WIN_HEIGHT);
		exit(1);
	}
}

/*
 * reads the map from the file
 *
 * @param data the game data
 * @param fpath the file path
 */
void	read_map(t_data *data, char *fpath)
{
	char	*content;

	content = read_file(fpath);
	data->map = ft_split(content, '\n');
	free(content);
	data->width = -1;
	data->height = -1;
	data->px = -1;
	data->py = -1;
	while (data->map[++data->height])
	{
		check_line_size(data);
		check_blocks(data);
	}
	check_map_size(data);
}
