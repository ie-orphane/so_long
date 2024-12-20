/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:40:10 by ielyatim          #+#    #+#             */
/*   Updated: 2024/12/20 21:16:50 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void *init_image(void *mlx_ptr, char *img_path)
{
	void *img_ptr;
	int img_width;
	int img_height;

	img_ptr = mlx_xpm_file_to_image(
		mlx_ptr,
		img_path,
		&img_width,
		&img_height);
	if (img_ptr == NULL)
	{
		ft_printf("img not found");
		exit(0);
	}
	if (img_height != FRAME_SIZE || img_width != FRAME_SIZE)
	{
		ft_printf("size error");
		free(mlx_ptr);
		free(img_ptr);
		exit(0);
	}
	return (img_ptr);
}

char *file_name_to_path(const char *dir, int index)
{
	char *path;
	char *num;
	size_t pathsize;

	num = ft_itoa(index);
	pathsize = ft_strlen(dir) + ft_strlen(num) + 5;
	path = malloc(pathsize * sizeof(char));
	if (path)
	{
		ft_strlcpy(path, dir, pathsize);
		ft_strlcat(path, num, pathsize);
		ft_strlcat(path, ".xpm", pathsize);
	}
	free(num);
	return (path);
}
void fill_frames(t_data *data, size_t max_frames, const char *frames_dir, char frames_key)
{
	t_dict *frames;
	size_t i;

	frames = NULL;
	i = 0;
	while (i < max_frames)
	{
		char *path = file_name_to_path(frames_dir, i);
		char *img_ptr = mlx_xpm_file_to_image(data->mlx, path, &data->frame_width, &data->frame_height);
		if (img_ptr == NULL || data->frame_height != FRAME_SIZE || data->frame_width != FRAME_SIZE)
		{
			ft_printf("%s: failed to load frame", path);
			dict_clear(&frames, dict_free);
			free(path);
			exit(0);
		}
		dict_add(&frames, i, img_ptr);
		free(path);
		i++;
	}
	dict_add(&data->frames, frames_key, frames);
}

void init_images(t_data *data)
{
	dict_add(&data->imgs, '1', init_image(data->mlx, "./sprites/wall32x32.xpm"));
	fill_frames(data, IDLE_FRAMES, "./sprites/pink-man/idle/", 'i');
	fill_frames(data, RUN_FRAMES, "./sprites/pink-man/run/", 'r');
}

void render(t_data *data)
{
	int x;
	int y;

	y = 0;
	while (y < data->map->height)
	{
		x = 0;
		while (x < data->map->width)
		{
			if (data->map->blocks[y][x] == '1')
				mlx_put_image_to_window(
					data->mlx,
					data->win,
					dict_find(&data->imgs, data->map->blocks[y][x]),
					FRAME_SIZE * x,
					FRAME_SIZE * y);
			x++;
		}
		y++;
	}
}

int frames_overlap(int ax, int ay, int bx, int by)
{
	int a_right = ax + FRAME_SIZE;
	int a_bottom = ay + FRAME_SIZE;
	int b_right = bx + FRAME_SIZE;
	int b_bottom = by + FRAME_SIZE;

	if (ax >= b_right || bx >= a_right) // No horizontal overlap
		return (0);
	if (ay >= b_bottom || by >= a_bottom) // No vertical overlap
		return (0);
	return (1);
}

int next_ifwall(t_data *data, char direction, int next_x, int next_y)
{
	int distance = SPEED;
	int y = 0;

	while (y < data->map->height)
	{
		int x = 0;
		while (x < data->map->width)
		{
			if (data->map->blocks[y][x] == '1') // Wall block
			{
				if (frames_overlap(x * FRAME_SIZE, y * FRAME_SIZE, next_x, next_y))
				{

					if (direction == 'r') // Moving right
						distance = x * FRAME_SIZE - (data->x + FRAME_SIZE);
					else if (direction == 'l') // Moving left
						distance = data->x - (x * FRAME_SIZE + FRAME_SIZE);
					else if (direction == 'd') // Moving down
						distance = y * FRAME_SIZE - (data->y + FRAME_SIZE);
					else if (direction == 'u') // Moving up
						distance = data->y - (y * FRAME_SIZE + FRAME_SIZE);


					// Clamp distance to positive values
					if (distance < 0)
						distance = 0;
				}
			}
			x++;
		}
		y++;
	}

	// Return the smaller of SPEED or the clamped distance
	if (distance < SPEED)
		return (distance);
	return (SPEED);
}

void update_position(t_data *data, int *next_x, int *next_y)
{
	int distance_x = SPEED;
	int distance_y = SPEED;

	// Calculate distances for both axes independently
	if (data->keys[XK_d]) // Move right
		distance_x = next_ifwall(data, 'r', *next_x + SPEED, data->y);
	if (data->keys[XK_a]) // Move left
		distance_x = next_ifwall(data, 'l', *next_x - SPEED, data->y);

	if (data->keys[XK_s]) // Move down
		distance_y = next_ifwall(data, 'd', data->x, *next_y + SPEED);
	if (data->keys[XK_w]) // Move up
		distance_y = next_ifwall(data, 'u', data->x, *next_y - SPEED);

	// Apply movement only if the respective direction is not blocked
	if (data->keys[XK_d] && distance_x > 0)
		*next_x += distance_x;
	if (data->keys[XK_a] && distance_x > 0)
		*next_x -= distance_x;
	if (data->keys[XK_s] && distance_y > 0)
		*next_y += distance_y;
	if (data->keys[XK_w] && distance_y > 0)
		*next_y -= distance_y;
}

int update_animation(t_data *data)
{
	int next_x = data->x;
	int next_y = data->y;

	if (data->counter++ % ANIMATION_DELAY == 0)
	{
		mlx_clear_window(data->mlx, data->win);

		// Update position with collision checks
		if (data->keys[XK_d] || data->keys[XK_a] || data->keys[XK_w] || data->keys[XK_s])
		{
			update_position(data, &next_x, &next_y);

			if (next_x != data->x || next_y != data->y)
				data->current_frame = (data->current_frame + 1) % RUN_FRAMES;
			else
				data->current_frame = (data->current_frame + 1) % IDLE_FRAMES;
		}
		else
			data->current_frame = (data->current_frame + 1) % IDLE_FRAMES;

		data->x = next_x;
		data->y = next_y;

		// Render current frame
		t_dict *frames = dict_find(&data->frames, data->keys[XK_d] || data->keys[XK_a] || data->keys[XK_w] || data->keys[XK_s] ? 'r' : 'i');
		t_dict *frame = dict_find(&frames, data->current_frame);
		if (!frames || !frame)
		{
			ft_printf("failed to get frames");
			exit(0);
		}

		mlx_put_image_to_window(data->mlx, data->win, frame, data->x, data->y);
		render(data);
	}
	return 0;
}

int main(void)
{
	t_data data;

	data.map = read_map("./map.ber");
	data.mlx = mlx_init();
	if (data.mlx == NULL)
	{
		ft_printf("Error\n");
		return (MLX_ERROR);
	}
	data.win = mlx_new_window(
		data.mlx,
		data.map->width * FRAME_SIZE,
		data.map->height * FRAME_SIZE,
		WIN_TITLE);
	if (data.win == NULL)
	{
		ft_printf("Error\n");
		free(data.mlx);
		return (MLX_ERROR);
	}

	data.imgs = NULL;
	data.collective = 0;
	data.counter = 0;
	data.frames = NULL;
	data.steps = 0;

	init_images(&data);

	data.current_frame = 0;
	data.x = data.map->x * FRAME_SIZE;
	data.y = data.map->y * FRAME_SIZE;
	data.counter = 0;
	for (int i = 0; i < 256; i++)
		data.keys[i] = 0;

	mlx_loop_hook(data.mlx, update_animation, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, key_down, &data);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, key_up, &data);
	mlx_hook(data.win, DestroyNotify, NoEventMask, handle_close_event, &data);

	mlx_loop(data.mlx);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
	return (0);
}
