/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:40:10 by ielyatim          #+#    #+#             */
/*   Updated: 2024/12/20 10:38:10 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*init_image(void *mlx_ptr, char *img_path)
{
	void	*img_ptr;
	int		img_width;
	int		img_height;

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

void init_images(t_data *data)
{
	// dict_add(&data->imgs, 'P', init_image(data->mlx, "./p96x96.xpm"));
	dict_add(&data->imgs, '1', init_image(data->mlx, "./sprites/wall32x32.xpm"));
	// dict_add(&data->imgs, 'C', init_image(data->mlx, "./c96x96.xpm"));
}

void	render(t_data *data)
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

int update_animation(t_data *data) {
	t_dict *frames;
	char framekey;
	t_dict *frame;

	if (data->counter++ % ANIMATION_DELAY == 0)
	{
		mlx_clear_window(data->mlx, data->win);
		if (data->keys[XK_d] || data->keys[XK_a] || data->keys[XK_w] || data->keys[XK_s])
		{
			if (data->keys[XK_d])
				data->x += SPEED;
			if (data->keys[XK_a])
				data->x -= SPEED;
			if (data->keys[XK_w])
				data->y -= SPEED;
			if (data->keys[XK_s])
				data->y += SPEED;
			data->current_frame = (data->current_frame + 1) % RUN_FRAMES;
			ft_printf("run : %d : %d, %d\n", data->current_frame, data->x, data->y);
			framekey = 'r';
		}
		else
		{
			data->current_frame = (data->current_frame + 1) % IDLE_FRAMES;
			ft_printf("idle: %d : %d, %d\n", data->current_frame, data->x, data->y);
			framekey = 'i';
		}
		frames = dict_find(&data->frames, framekey);
		frame = dict_find(&frames, data->current_frame);
		if (frames == NULL || frame == NULL)
		{
			ft_printf("failed to get frames");
			exit(0);
		}
		mlx_put_image_to_window(
			data->mlx,
			data->win,
			frame,
			data->x,
			data->y);
		render(data);
	}
	return 0;
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

int	main(void)
{
	t_data	data;

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

	init_images(&data);
	fill_frames(&data, IDLE_FRAMES, "./sprites/pink-man/idle/", 'i');
	fill_frames(&data, RUN_FRAMES, "./sprites/pink-man/run/", 'r');

	data.current_frame = 0;
	data.x = 0;
	data.y = 0;
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
