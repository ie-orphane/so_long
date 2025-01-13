/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 10:50:08 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/13 18:05:45 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"

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
		if (data->f_player.state == DYING)
			return ;
		else if (data->direction == 'l')
			data->f_player.state = RUN_LEFT;
		else
			data->f_player.state = RUN_RIGHT;
	}
	else if (data->direction == 'l')
		data->f_player.state = IDLE_LEFT;
	data->px = next_x;
	data->py = next_y;
}

void	update_frames(t_data *data)
{
	data->f_updated = false;
	update_frame(data, NULL, (t_frame_ref){.count = &data->f_foam.count,
		.max = data->f_foam.max, .delay = data->f_foam.delay,
		.current_time = &data->f_foam.current_time,
		.last_time = &data->f_foam.last_time});
	update_frame(data, NULL, (t_frame_ref){.count = &data->f_enemy.count,
		.max = data->f_enemy.max, .delay = data->f_enemy.delay,
		.current_time = &data->f_enemy.current_time,
		.last_time = &data->f_enemy.last_time});
	if (data->f_player.state != DEAD && data->f_player.state != DYING)
		update_frame(data, player_frame_callable,
			(t_frame_ref){.count = &data->f_player.count,
			.max = data->f_player.max, .delay = data->f_player.delay,
			.current_time = &data->f_player.current_time,
			.last_time = &data->f_player.last_time});
	else if (data->f_player.state == DYING)
		update_frame(data, NULL, (t_frame_ref){.count = &data->f_dying.count,
			.max = data->f_dying.max, .delay = data->f_dying.delay,
			.current_time = &data->f_dying.current_time,
			.last_time = &data->f_dying.last_time});
	if (data->f_dying.count == data->f_dying.max - 1)
	{
		data->f_player.state = DEAD;
		data->brightness = 0.75;
	}
}

int	update_animation(t_data *data)
{
	update_frames(data);
	if (!data->f_updated)
		return (0);
	img_destroy(data->mlx, &data->img);
	data->img = img_new(data->mlx, data->width * TILE_SIZE, data->height
			* TILE_SIZE);
	put_ground_layers(data);
	put_entities_layers(data);
	mlx_clear_window(data->mlx, data->win);
	mlx_put_image_to_window(data->mlx, data->win, data->img->ptr, 0, 0);
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

	if (argc < 1)
		return (0);
	ft_bzero(&data, sizeof(t_data));
	parse_map(&data, argv[1]);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.width * TILE_SIZE, data.height
			* TILE_SIZE, WIN_TITLE);
	init_tiles(&data);
	init_frames(&data);
	mlx_loop_hook(data.mlx, update_animation, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, keypress_handler, &data);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, keyrelease_handler, &data);
	mlx_hook(data.win, DestroyNotify, NoEventMask, destroy_handler, &data);
	mlx_loop(data.mlx);
	return (0);
}
