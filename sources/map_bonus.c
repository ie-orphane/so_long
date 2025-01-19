/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 10:50:14 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/19 18:52:08 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"

void	flood_exit(t_data *data, int x, int y)
{
	data->check.exit = true;
	data->check.exit_coor = (t_point){x, y};
	data->check.content[y][x] = '1';
	data->check.content[y][x + 1] = '1';
	data->check.content[y][x - 1] = '1';
}

/// @brief Flood fill algorithm to fill the map
/// @param data the game data
/// @param x the x position
/// @param y the y position
void	flood_fill(t_data *data, int x, int y)
{
	const char	key = data->check.content[y][x];

	if (key == ' ' || key == '1' || key == 'F')
		return ;
	if (data->map[y][x] == 'C')
		data->check.ccount += 1;
	if ((key == 'E' && data->check.exit) || (key == 'P' && data->check.player))
	{
		ft_printf(ERROR_START "Extra '%c' found" ERROR_END, key);
		ft_exit(data, 0);
	}
	if (data->map[y][x] == 'E')
	{
		flood_exit(data, x, y);
		return (flood_fill(data, x, y));
	}
	if (data->map[y][x] == 'P')
		data->check.player = true;
	data->check.content[y][x] = ' ';
	flood_fill(data, x + 1, y);
	flood_fill(data, x - 1, y);
	flood_fill(data, x, y + 1);
	flood_fill(data, x, y - 1);
}

static void	check_exit(t_data *data)
{
	const int	x = data->check.exit_coor.x;
	const int	y = data->check.exit_coor.y;

	if (data->map[y][x - 1] != '0' || data->map[y][x + 1] != '0')
		ft_ultimate_error(data,
			"Exit should be horizontally surrounded by '0'");
}

/// @brief Reads the map from the file
/// @param data the game data
/// @param fpath the file path
void	parse_map(t_data *data, char *fpath)
{
	char	**tmp;
	int		i;

	data->map = read_map(fpath);
	data->width = -1;
	data->height = -1;
	while (data->map[++data->height])
	{
		check_line_size(data);
		check_blocks(data);
	}
	check_closed(data);
	data->height++;
	data->py += TILE_SIZE;
	tmp = malloc((data->height + 1) * sizeof(char *));
	i = 0;
	tmp[i] = ft_strdup(data->map[i]);
	while (++i < data->height)
		tmp[i] = data->map[i - 1];
	tmp[i] = NULL;
	free(data->map);
	data->map = tmp;
	check_map_size(data);
	check_path(data);
	check_exit(data);
}

void	player_frame_callable(t_data *data)
{
	int	next_x;
	int	next_y;

	next_x = data->px;
	next_y = data->py;
	data->f_player.state = IDLE_RIGHT;
	if (keyin(data, (int []){XK_d, XK_a, XK_w, XK_s, -1}))
	{
		update_position(data, &next_x, &next_y);
		if (data->f_player.state == DEAD || data->f_player.state == EXIT)
			return ;
		if (data->direction == 'l')
			data->f_player.state = RUN_LEFT;
		else
			data->f_player.state = RUN_RIGHT;
	}
	else if (data->direction == 'l')
		data->f_player.state = IDLE_LEFT;
	data->px = next_x;
	data->py = next_y;
}
