/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frames.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 21:42:28 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/06 12:07:14 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	fill_frames(t_data *data, size_t max, const char *dir, char key)
{
	t_dict	*frames;
	size_t	i;
	char	*img_path;

	frames = NULL;
	i = 0;
	while (i < max)
	{
		img_path = filename_to_path(dir, i);
		dict_add(&frames, i, img_init(data->mlx, img_path));
		free(img_path);
		i++;
	}
	dict_add(&data->frames, key, frames);
}

static void	init_ground_imgs(t_data *data)
{
	int	i;
	char	*img_path;

	i = 0;
	while (i < TG_MAX)
	{
		img_path = filename_to_path(TG_PATH, i);
		data->t_ground[i] = img_init(data->mlx, img_path);
		free(img_path);
		i++;
	}
}

void	init_images(t_data *data)
{
	dict_add(&data->imgs, '0', img_init(data->mlx, "./textures/water.xpm"));
	init_ground_imgs(data);

	dict_add(&data->imgs, 'E', img_init(data->mlx, "./textures/gold-mine/destroyed.xpm"));

	fill_frames(data, IDLE_FRAMES, "./textures/pawn/idle/right/", 'i');
	fill_frames(data, IDLE_FRAMES, "./textures/pawn/idle/left/", 'I');
	fill_frames(data, RUN_FRAMES, "./textures/pawn/run/right/", 'r');
	fill_frames(data, RUN_FRAMES, "./textures/pawn/run/left/", 'R');

	fill_frames(data, COLLECTIVE_FRAMES, "./textures/sheep/", 'c');
	fill_frames(data, FOAM_FRAMES, "./textures/foam/", 'f');
	// fill_frames(data, EXIT_FRAMES, "./textures/trophy/", 'e');
	fill_frames(data, ENEMY_FRAMES, "./textures/goblins/torch/", 'F');
}

t_img	*frame_get(t_dict *framedict, char framekey, char frameindex)
{
	t_img	*img;
	t_dict	*frames;

	frames = dict_find(&framedict, framekey);
	img = dict_find(&frames, frameindex);
	return (img);
}
