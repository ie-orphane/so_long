/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:40:06 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/05 18:48:32 by ielyatim         ###   ########.fr       */
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
# include <sys/time.h>

# include "ft_printf.h"
# include "libft.h"
# include "dict.h"
# include "image.h"
# include "mlx.h"
# include "sprite.h"
# define MLX_ERROR 1

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define WIN_TITLE "my game"

// # define BLOCK_SIZE 96

# define IDLE_FRAMES 6
# define RUN_FRAMES 6
# define COLLECTIVE_FRAMES 17
# define EXIT_FRAMES 8
# define ENEMY_FRAMES 9
# define FOAM_FRAMES 8

# define ANIMATION_DELAY 10000
# define SPEED 16

typedef unsigned int t_uint;
typedef struct timeval t_timeval;

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

typedef struct s_frame
{
	t_uint		count;
	t_uint		max;
	t_timeval	current_time;
	t_timeval	last_time;
}	t_frame;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_map	*map;
	t_dict	*imgs;
	t_img	*img;

	void	*t_wall[TW_MAX];
	void	*t_ground[TG_MAX];

	int count_frame;
	int fframe;
	int eframe;
	int enemy_frame;

	t_frame f_foan;
	t_frame f_player;

	t_ply ply;
	char direction;
	t_dict *frames;
	t_dict *pframes;
	void	*_frames[F_MAX];

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
int		randint(int min, int max);


/* frames */
void	fill_frames(t_data *data, size_t max, const char *dir, char key);
void	init_images(t_data *data);
t_img	*frame_get(t_dict *framedict, char framekey, char frameindex);


/* map */
t_map	*read_map(t_data *data, char *fpath);

int		handle_no_event(void *data);
int		handle_close_event();
int key_down(int keycode, t_data *data);
int key_up(int keycode, t_data *data);

#endif // SO_LONG_H
