/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:06:49 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/12 10:37:12 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"

static void	put_player_img(t_data *data)
{
	t_img	*player_img;
	int		player_x;
	int		player_y;

	if (data->f_player.state == DEAD)
		return ;
	if (data->f_player.state == DYING)
		player_img = data->f_dying.all[(data->f_dying.count - 1)
			% data->f_dying.max];
	else
		player_img = data->f_player.all[data->f_player.state]
		[data->f_player.count];
	player_x = data->px - ((player_img->width - TILE_SIZE) / 2);
	player_y = data->py - 10 - ((player_img->height - TILE_SIZE) / 2);
	put_img_to_img(data->img, player_img, (t_point){player_x, player_y},
		data->brightness);
}

static void	put_entities_img(t_data *data, t_img *img, t_point player_position,
		bool *player_putted)
{
	t_shape	entity;
	t_shape	player;
	t_point	entity_position;

	player = (t_shape){data->px, data->py - 10, TILE_SIZE, TILE_SIZE};
	entity = (t_shape){TILE_SIZE * player_position.x - ((img->width - TILE_SIZE)
			/ 2), TILE_SIZE * player_position.y - ((img->height - TILE_SIZE)
			/ 2) - 15, img->width, img->height};
	entity_position = (t_point){entity.x, entity.y};
	if (!shape_overlap(player, entity))
	{
		put_img_to_img(data->img, img, entity_position, data->brightness);
		return ;
	}
	if (player_position.y * TILE_SIZE <= data->py)
	{
		put_img_to_img(data->img, img, entity_position, data->brightness);
		put_player_img(data);
	}
	else
	{
		put_player_img(data);
		put_img_to_img(data->img, img, entity_position, data->brightness);
	}
	(*player_putted) = true;
}

t_img	*get_entity_img(t_data *data, int x, int y)
{
	t_img	*img;

	img = NULL;
	if (data->map[y][x] == 'C')
		img = data->tiles[TILE_GOLD];
	else if (data->map[y][x] == 'E' && data->ccount != data->pcount)
		img = data->tiles[TILE_MINE_DESTROYED];
	else if (data->map[y][x] == 'E')
		img = data->tiles[TILE_MINE_ACTIVE];
	else if (data->map[y][x] == 'F')
		img = data->f_enemy.all[data->f_enemy.count];
	return (img);
}

void	put_entities_layers(t_data *data)
{
	int		x;
	int		y;
	t_img	*img;
	bool	player_putted;

	player_putted = false;
	y = -1;
	while (++y < data->height)
	{
		x = -1;
		while (++x < data->width)
		{
			img = get_entity_img(data, x, y);
			if (!img)
				continue ;
			put_entities_img(data, img, (t_point){x, y}, &player_putted);
		}
	}
	if (!player_putted)
		put_player_img(data);
}
