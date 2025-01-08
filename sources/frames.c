/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frames.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 21:42:28 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/08 18:38:05 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	init_frame_imgs(t_data *data, t_img ***imgs, t_uint max,
		const char *dir)
{
	t_uint	i;
	char	*img_path;

	(*imgs) = malloc(sizeof(t_img) * max);
	i = 0;
	while (i < max)
	{
		img_path = filename_to_path(dir, i);
		(*imgs)[i] = img_init(data->mlx, img_path);
		free(img_path);
		i++;
	}
}

static void	init_frames(t_data *data, t_frame *frame, t_frame_info info,
		const char *dir)
{
	frame->count = 0;
	frame->max = info.max;
	frame->delay = info.delay;
	gettimeofday(&frame->last_time, NULL);
	init_frame_imgs(data, &frame->all, frame->max, dir);
}

static void	init_troop_frames(t_data *data, t_troop_frame *frame,
		t_frame_info info, char *dirs[TROOP_FRAMES_MAX])
{
	t_uint	i;

	frame->count = 0;
	frame->max = info.max;
	frame->delay = info.delay;
	gettimeofday(&frame->last_time, NULL);
	i = 0;
	while (i < TROOP_FRAMES_MAX)
	{
		init_frame_imgs(data, &frame->all[i], frame->max, dirs[i]);
		i++;
	}
}

static void	init_ground_imgs(t_data *data)
{
	int		i;
	char	*img_path;

	i = 0;
	while (i < TILESET_GROUND_MAX)
	{
		img_path = filename_to_path(TILESET_GROUND_PATH, i);
		data->t_ground[i] = img_init(data->mlx, img_path);
		free(img_path);
		i++;
	}
}

void	init_sprites(t_data *data)
{
	data->img = NULL;
	data->tiles[TILE_GOLD] = img_init(data->mlx, "./textures/gold.xpm");
	data->tiles[TILE_WATER] = img_init(data->mlx, "./textures/water.xpm");
	data->tiles[TILE_MINE_DESTROYED] = img_init(data->mlx,
			"./textures/mine/destroyed.xpm");
	data->tiles[TILE_MINE_ACTIVE] = img_init(data->mlx,
			"./textures/mine/active.xpm");
	init_ground_imgs(data);
	data->f_player.state = IDLE_RIGHT;
	init_troop_frames(data, &data->f_player, (t_frame_info){.delay = 87,
		.max = 6}, (char *[TROOP_FRAMES_MAX]){"./textures/pawn/idle/right/",
		"./textures/pawn/idle/left/", "./textures/pawn/run/right/",
		"./textures/pawn/run/left/"});
	init_frames(data, &data->f_enemy, (t_frame_info){.delay = 100, .max = 7},
		"./textures/goblins/torch/");
	init_frames(data, &data->f_foam, (t_frame_info){.delay = 115, .max = 8},
		"./textures/foam/");
}
