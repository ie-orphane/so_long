/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frames_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 10:49:39 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/27 11:36:08 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"

static void	init_frame_imgs(t_data *data, t_img ***imgs, unsigned int max,
		const char *dir)
{
	unsigned int	i;
	char			*img_path;

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

static void	init_frameset(t_data *data, t_frame *frame, t_frame_info info,
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
	unsigned int	i;

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

void	init_frames(t_data *data)
{
	init_troop_frames(data, &data->f_player, (t_frame_info){.delay = 87,
		.max = 6},
		(char *[TROOP_FRAMES_MAX]){"./textures/knights/pawn/idle/right/",
		"./textures/knights/pawn/idle/left/",
		"./textures/knights/pawn/run/right/",
		"./textures/knights/pawn/run/left/"});
	init_frameset(data, &data->f_enemy, (t_frame_info){.delay = 100, .max = 7},
		"./textures/goblins/torch/");
	init_frameset(data, &data->f_foam, (t_frame_info){.delay = 115, .max = 8},
		"./textures/foam/");
	init_frameset(data, &data->f_gold, (t_frame_info){.delay = 100, .max = 7},
		"./textures/gold/");
	init_frameset(data, &data->f_dying, (t_frame_info){.delay = 150, .max = 14},
		"./textures/knights/dead/");
	init_frameset(data, &data->f_rocks[0], (t_frame_info){.delay = 115, .max = 8},
		"./textures/rocks/0/");
	init_frameset(data, &data->f_rocks[1], (t_frame_info){.delay = 115, .max = 8},
		"./textures/rocks/1/");
}

void	destroy_frames(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < (int)data->f_foam.max)
		img_destroy(data->mlx, &data->f_foam.all[i]);
	free(data->f_foam.all);
	i = -1;
	while (++i < (int)data->f_enemy.max)
		img_destroy(data->mlx, &data->f_enemy.all[i]);
	free(data->f_enemy.all);
	i = -1;
	while (++i < (int)data->f_dying.max)
		img_destroy(data->mlx, &data->f_dying.all[i]);
	free(data->f_dying.all);
	i = -1;
	while (++i < (int)data->f_gold.max)
		img_destroy(data->mlx, &data->f_gold.all[i]);
	free(data->f_gold.all);
	i = -1;
	while (++i < TROOP_FRAMES_MAX)
	{
		j = -1;
		while (++j < 6)
			img_destroy(data->mlx, &(data->f_player.all[i][j]));
		free(data->f_player.all[i]);
	}
	i = -1;
	while (++i < 2)
	{
		j = -1;
		while (++j < (int)data->f_rocks[i].max)
			img_destroy(data->mlx, &(data->f_rocks[i].all[j]));
		free(data->f_rocks[i].all);
	}
	img_destroy(data->mlx, &data->img);
}
