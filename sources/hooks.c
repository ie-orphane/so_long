/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:59:40 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/13 16:26:40 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	next_position(int keycode, t_point *next)
{
	if (keycode == XK_Right || keycode == XK_d)
		next->x += TILE_SIZE;
	if (keycode == XK_Left || keycode == XK_a)
		next->x -= TILE_SIZE;
	if (keycode == XK_Down || keycode == XK_s)
		next->y += TILE_SIZE;
	if (keycode == XK_Up || keycode == XK_w)
		next->y -= TILE_SIZE;
}

int	key_handler(int keycode, t_data *data)
{
	t_point	next;

	if (keycode == XK_Escape)
		destroy_handler(data);
	if (!(keycode == XK_d || keycode == XK_a || keycode == XK_s
			|| keycode == XK_w || keycode == XK_Right || keycode == XK_Left
			|| keycode == XK_Up || keycode == XK_Down) || data->brightness != 0)
		return (0);
	next = data->p;
	next_position(keycode, &next);
	if (data->map[next.y / TILE_SIZE][next.x / TILE_SIZE] == '1'
		|| (data->map[next.y / TILE_SIZE][next.x / TILE_SIZE] == 'E'
			&& data->ccount != data->pcount))
		return (0);
	data->steps += 1;
	if (data->map[next.y / TILE_SIZE][next.x / TILE_SIZE] == 'C')
	{
		data->map[next.y / TILE_SIZE][next.x / TILE_SIZE] = '0';
		data->pcount += 1;
	}
	else if (data->map[next.y / TILE_SIZE][next.x / TILE_SIZE] == 'E')
		data->brightness = 0.5;
	data->p = next;
	data->updated = true;
	return (0);
}

static void	put_tiles(t_data *data)
{
	int		x;
	int		y;
	t_img	*img;

	y = -1;
	while (++y < data->height)
	{
		x = -1;
		while (++x < data->width)
		{
			img = data->tiles[TILE_GROUND];
			put_scaled_img_to_img(data->img, img, (t_point){x * TILE_SIZE, y
				* TILE_SIZE}, data->brightness);
			img = NULL;
			if (data->map[y][x] == '1')
				img = wall_tile(data, x, y);
			else if (data->map[y][x] == 'C')
				img = data->tiles[TILE_KEY];
			else if (data->map[y][x] == 'E')
				img = data->ts_exit[data->pcount == data->ccount];
			if (img)
				put_scaled_img_to_img(data->img, img, (t_point){x * TILE_SIZE, y
					* TILE_SIZE}, data->brightness);
		}
	}
}

int	loop_handler(t_data *data)
{
	t_img	*img;

	if (data->game_over)
	{
		ft_printf("Game Over! you win.\n");
		ft_exit(data, 0);
	}
	if (!data->updated)
		return (0);
	ft_printf("Current Mouvements: %d\n", data->steps);
	if (data->brightness != 0)
		data->game_over = true;
	img_destroy(data->mlx, &data->img);
	data->img = img_new(data->mlx, data->width * TILE_SIZE * TILE_SCALE,
			data->height * TILE_SIZE * TILE_SCALE);
	put_tiles(data);
	img = data->tiles[TILE_PLAYER];
	put_scaled_img_to_img(data->img, img, data->p, data->brightness);
	mlx_clear_window(data->mlx, data->win);
	mlx_put_image_to_window(data->mlx, data->win, data->img->ptr, 0, 0);
	data->updated = false;
	return (0);
}

int	destroy_handler(t_data *data)
{
	ft_printf("Bye bye! see you later.\n");
	ft_exit(data, 0);
	return (0);
}
