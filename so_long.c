/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:40:10 by ielyatim          #+#    #+#             */
/*   Updated: 2024/12/20 15:49:52 by ielyatim         ###   ########.fr       */
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

void init_images(t_data *data)
{
	dict_add(&data->imgs, '1', init_image(data->mlx, "./sprites/wall32x32.xpm"));
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

typedef struct s_point
{
	int x;
	int y;
} t_point;

int squares_overlap(t_point a, t_point b, int size)
{
	int a_right = a.x + size;
	int a_bottom = a.y + size;
	int b_right = b.x + size;
	int b_bottom = b.y + size;

	if (a.x > b_right || b.x > a_right) // No horizontal overlap
		return (0);
	if (a.y > b_bottom || b.y > a_bottom) // No vertical overlap
		return (0);
	return (1);
}

int next_iswall(t_data *data, int next_x, int next_y)
{
	int y = 0;
	while (y < data->map->height)
	{
		int x = 0;
		while (x < data->map->width)
		{
			if (data->map->blocks[y][x] == '1')
			{
				t_point wall_position = {x * FRAME_SIZE, y * FRAME_SIZE};
				t_point player_position = {next_x + SPEED - 1, next_y + SPEED - 1};
				if (squares_overlap(wall_position, player_position, FRAME_SIZE))
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int update_animation(t_data *data)
{
	t_dict *frames;
	char framekey;
	t_dict *frame;
	int next_y;
	int next_x;

	if (data->counter++ % ANIMATION_DELAY == 0)
	{
		mlx_clear_window(data->mlx, data->win);
		next_x = data->x;
		next_y = data->y;
		if ((data->keys[XK_d] ||
			 data->keys[XK_a] ||
			 data->keys[XK_w] ||
			 data->keys[XK_s]) &&
			(next_iswall(data, next_x, next_y) == 0))
		{

			if (data->keys[XK_d])
				next_x += SPEED;
			if (data->keys[XK_a])
				next_x -= SPEED;
			if (data->keys[XK_w])
				next_y -= SPEED;
			if (data->keys[XK_s])
				next_y += SPEED;
			ft_printf("run : %d : %d, %d\n", data->current_frame, data->x, data->y);
			data->current_frame = (data->current_frame + 1) % RUN_FRAMES;
			framekey = 'r';
		}
		else
		{
			data->current_frame = (data->current_frame + 1) % IDLE_FRAMES;
			ft_printf("idle: %d : %d, %d\n", data->current_frame, data->x, data->y);
			framekey = 'i';
		}
		data->x = next_x;
		data->y = next_y;
		frames = dict_find(&data->frames, framekey);
		frame = dict_find(&frames, data->current_frame);
		if (frames == NULL || frame == NULL)
		{
			ft_printf("failed to get frames");
			exit(0);
		}
		render(data);
		mlx_put_image_to_window(
			data->mlx,
			data->win,
			frame,
			data->x,
			data->y);
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

	init_images(&data);
	fill_frames(&data, IDLE_FRAMES, "./sprites/pink-man/idle/", 'i');
	fill_frames(&data, RUN_FRAMES, "./sprites/pink-man/run/", 'r');
	int x;
	int y;

	y = 0;
	while (y < data.map->height - 1)
	{
		x = 0;
		while (x < data.map->width - 1)
		{
			if (data.map->blocks[y][x] == '1' && x != 0 && y != 0)
				ft_printf("(%d, %d) ", x, y);
			x++;
		}
		y++;
	}
	ft_printf("\n");
	data.current_frame = 0;
	data.x = 125;
	data.y = 125;
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
