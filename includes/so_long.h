/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:40:06 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/02 21:46:16 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <math.h>
# include <time.h>

# include "ft_printf.h"
# include "libft.h"
# include "dict.h"
# include "image.h"
# include "mlx.h"

# define MLX_ERROR 1

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define WIN_TITLE "my game"

// # define BLOCK_SIZE 96
# define FRAME_SIZE 32
# define IDLE_FRAMES 11
# define RUN_FRAMES 12
# define COLLECTIVE_FRAMES 17
# define EXIT_FRAMES 8
# define ENEMY_FRAMES 9
# define ANIMATION_DELAY 10000
# define SPEED 8

typedef struct s_map {
	char *content;
	int width;
	int height;
	char **blocks;
	int x;
	int y;
	size_t collective;
} t_map;

// typedef struct s_img
// {
// 	void *self;
// 	int width;
// 	int height;
// 	int x;
// 	int y;
// }	t_img;

typedef struct s_ply
{
	int x;
	int y;
	int current_bag;
	int max_bag;
} t_ply;


typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_map	*map;
	t_dict	*imgs;
	t_img	*img;
	t_img	*static_img;

	int current_frame;
	int count_frame;
	int eframe;
	int enemy_frame;

	t_ply ply;
	char direction;
	t_dict *frames;
	t_dict *pframes;
	int counter;
	int keys[256];
	int steps;

	int px;
	int py;
	int pcount;
	int ccount;
} t_data;

/* utils */
char	*read_file(char *fpath);
int		ft_strset(const char *str, const char *set);
char	*filename_to_path(const char *dir, int index);


/* frames */
void	fill_frames(t_data *data, size_t max, const char *dir, char key);
void	init_images(t_data *data);
t_img	*frame_get(t_dict *framedict, char framekey, char frameindex);


/* map */
t_map	*read_map(t_data *data, char *fpath);

int		handle_no_event(void *data);
int		handle_close_event(t_data *data);
int key_down(int keycode, t_data *data);
int key_up(int keycode, t_data *data);
// void	render(t_data *data);

#endif // SO_LONG_H
