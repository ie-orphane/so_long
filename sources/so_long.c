/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:40:10 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/09 18:37:00 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

int	update_frames(t_data *data)
{
	int	updated;

	updated = 0;
	update_frame(data, &updated, NULL,
		(t_frame_ref){.count = &data->f_enemy.count, .max = data->f_enemy.max,
		.delay = data->f_enemy.delay,
		.current_time = &data->f_enemy.current_time,
		.last_time = &data->f_enemy.last_time});
	update_frame(data, &updated, player_frame_callable,
		(t_frame_ref){.count = &data->f_player.count, .max = data->f_player.max,
		.delay = data->f_player.delay,
		.current_time = &data->f_player.current_time,
		.last_time = &data->f_player.last_time});
	update_frame(data, &updated, NULL,
		(t_frame_ref){.count = &data->f_foam.count, .max = data->f_foam.max,
		.delay = data->f_foam.delay, .current_time = &data->f_foam.current_time,
		.last_time = &data->f_foam.last_time});
	return (updated);
}

int	update_animation(t_data *data)
{
	if (!update_frames(data))
		return (0);
	if (data->img)
	{
		mlx_destroy_image(data->mlx, data->img->ptr);
		free(data->img);
	}
	data->img = img_new(data->mlx, data->width * TILE_SIZE, data->height
			* TILE_SIZE);
	put_ground_layers(data);

	put_entities_layers(data);
	mlx_clear_window(data->mlx, data->win);
	mlx_put_image_to_window(data->mlx, data->win, data->img->ptr, 0, 0);
	return (0);
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
	init_sprites(&data);
	mlx_loop_hook(data.mlx, update_animation, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, key_down, &data);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, key_up, &data);
	mlx_hook(data.win, DestroyNotify, NoEventMask, handle_close_event, &data);
	mlx_loop(data.mlx);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
	return (0);
}
