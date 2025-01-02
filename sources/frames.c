/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frames.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 21:42:28 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/02 21:48:06 by ielyatim         ###   ########.fr       */
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

typedef struct s_frame {
	int		length;
	t_dict	*self;
} t_frame;

void	fill_player_frames(t_data *data, size_t max, const char *dir, char key)
{
	t_frame *frames;
	size_t	i;
	char	*img_path;

	frames = malloc(sizeof(t_frame));
	frames->length = max;
	frames->self = NULL;

	i = 0;
	while (i < max)
	{
		img_path = filename_to_path(dir, i);
		dict_add(&frames->self, i, img_init(data->mlx, img_path));
		free(img_path);
		i++;
	}
	dict_add(&data->pframes, key, frames);
}

void	init_images(t_data *data)
{
	dict_add(&data->imgs, '1', img_init(data->mlx, "./sprites/min-wall.xpm"));
	dict_add(&data->imgs, '4', img_init(data->mlx, "./sprites/left_wall.xpm"));
	dict_add(&data->imgs, '2', img_init(data->mlx, "./sprites/right_wall.xpm"));
	dict_add(&data->imgs, '3', img_init(data->mlx, "./sprites/twall.xpm"));
	dict_add(&data->imgs, '5', img_init(data->mlx, "./sprites/tlcorner.xpm"));
	dict_add(&data->imgs, '6', img_init(data->mlx, "./sprites/trcorner.xpm"));
	dict_add(&data->imgs, '7', img_init(data->mlx, "./sprites/br-corner.xpm"));
	dict_add(&data->imgs, '8', img_init(data->mlx, "./sprites/bl-corner.xpm"));
	dict_add(&data->imgs, '9', img_init(data->mlx, "./sprites/wall.xpm"));
	dict_add(&data->imgs, 'E', img_init(data->mlx, "./sprites/exit32x32.xpm"));
	dict_add(&data->imgs, '0', img_init(data->mlx, "./sprites/ground.xpm"));
	fill_frames(data, IDLE_FRAMES, "./sprites/pink-man/idle/", 'i');
	fill_frames(data, IDLE_FRAMES, "./sprites/pink-man/idle/left/", 'I');
	fill_frames(data, RUN_FRAMES, "./sprites/pink-man/run/", 'r');
	fill_frames(data, RUN_FRAMES, "./sprites/pink-man/run/left/", 'R');
	fill_frames(data, COLLECTIVE_FRAMES, "./sprites/banana/", 'c');
	fill_frames(data, EXIT_FRAMES, "./sprites/trophy/", 'e');
	fill_frames(data, ENEMY_FRAMES, "./sprites/mashroom/", 'F');
	fill_frames(data, 32, "./sprites/grass/", 'g');
}

t_img	*frame_get(t_dict *framedict, char framekey, char frameindex)
{
	t_img	*img;
	t_dict	*frames;

	frames = dict_find(&framedict, framekey);
	img = dict_find(&frames, frameindex);
	return (img);
}
