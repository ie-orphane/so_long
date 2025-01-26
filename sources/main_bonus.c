/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 10:50:08 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/26 22:05:03 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"

static void	update_frames_enhanced(t_data *data)
{
	t_frame	*frames[2];
	int		i;

	frames[0] = &data->f_foam;
	frames[1] = &data->f_enemy;
	i = -1;
	while (++i < 2)
	{
		if (timediff(&frames[i]->current_time,
				frames[i]->last_time) >= frames[i]->delay)
		{
			frames[i]->count = (frames[i]->count + 1) % frames[i]->max;
			frames[i]->last_time = frames[i]->current_time;
			data->f_updated = true;
		}
	}
	if (timediff(&data->f_gold.current_time,
			data->f_gold.last_time) >= data->f_gold.delay && data->c.x != -1
		&& data->c.y != -1)
	{
		data->f_gold.count = (data->f_gold.count + 1) % data->f_gold.max;
		if (data->f_gold.count == 0)
		{
			data->c = (t_point){-1, -1};
			return ;
		}
		data->f_gold.last_time = data->f_gold.current_time;
		data->f_updated = true;
	}
}

static void	update_troop_frames(t_data *data)
{
	if (data->f_player.state == DEAD || data->f_player.state == EXIT)
	{
		if (!(timediff(&data->f_dying.current_time,
					data->f_dying.last_time) >= (data->f_dying.delay
					- ((data->f_dying.delay * 0.25)
						* (data->f_player.state == EXIT)))))
			return ;
		data->f_dying.count = (data->f_dying.count + 1) % data->f_dying.max;
		data->brightness += (0.9 / (data->f_dying.max - ((data->f_dying.max
							* 0.625) * (data->f_player.state == EXIT))));
		data->brightness = dmin(0.9, data->brightness);
		data->f_dying.last_time = data->f_dying.current_time;
		data->f_updated = true;
	}
	else if (timediff(&data->f_player.current_time,
			data->f_player.last_time) >= data->f_player.delay)
	{
		data->f_player.count = (data->f_player.count + 1) % data->f_player.max;
		player_frame_callable(data);
		data->f_player.last_time = data->f_player.current_time;
		data->f_updated = true;
	}
}

static int	loop_handler(t_data *data)
{
	update_frames_enhanced(data);
	update_troop_frames(data);
	if (data->brightness == 0.9)
	{
		if (data->f_player.state == EXIT)
			ft_printf(B_GREEN "Game Over! " R_GREEN "you won.\n\n" RESET);
		if (data->f_player.state == DEAD)
			ft_printf(B_RED "Game Over! " R_RED "you lost.\n\n" RESET);
		ft_exit(data, 0);
	}
	if (!data->f_updated)
		return (0);
	img_destroy(data->mlx, &data->img);
	data->img = img_new(data->mlx, data->width * TILE_SIZE, data->height
			* TILE_SIZE);
	put_ground_layers(data);
	put_entities_layers(data);
	mlx_clear_window(data->mlx, data->win);
	mlx_put_image_to_window(data->mlx, data->win, data->img->ptr, 0, 0);
	data->f_updated = false;
	return (0);
}

void	ft_exit(t_data *data, int status)
{
	int	i;

	if (data->map)
	{
		i = -1;
		while (data->map[++i])
			free(data->map[i]);
		free(data->map);
	}
	if (data->check.content)
	{
		i = -1;
		while (++i < data->height)
			free(data->check.content[i]);
		free(data->check.content);
	}
	if (!data->mlx)
		exit(status);
	destroy_tiles(data);
	destroy_frames(data);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(status);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc < 2)
		ft_error("missing map argument");
	ft_bzero(&data, sizeof(t_data));
	parse_map(&data, argv[1]);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.width * TILE_SIZE, data.height
			* TILE_SIZE, WIN_TITLE);
	init_tiles(&data);
	init_frames(&data);
	data.c = (t_point){-1, -1};
	mlx_loop_hook(data.mlx, loop_handler, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, keypress_handler, &data);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, keyrelease_handler, &data);
	mlx_hook(data.win, DestroyNotify, NoEventMask, destroy_handler, &data);
	mlx_loop(data.mlx);
	return (0);
}
