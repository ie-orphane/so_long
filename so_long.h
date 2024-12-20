/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:40:06 by ielyatim          #+#    #+#             */
/*   Updated: 2024/12/20 20:45:22 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <mlx.h>
# include <X11/keysym.h>
# include <X11/X.h>

# include "ft_printf.h"
# include "libft.h"
# include "dict.h"

# define MLX_ERROR 1

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define WIN_TITLE "my game"

// # define BLOCK_SIZE 96
# define FRAME_SIZE 32
# define IDLE_FRAMES 11
# define RUN_FRAMES 12
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

typedef struct s_img
{
	void *self;
	int width;
	int height;
	int x;
	int y;
}	t_img;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_map	*map;
	t_img	*pimg;
	t_dict *imgs;
	size_t collective;

	int frame_width;
	int frame_height;
	int current_frame;
	int x;
	int y;
	t_dict *frames;
	int counter;
	int keys[256];
} t_data;

/* utils */
char	*read_file(char *fpath);
int		ft_strset(const char *str, const char *set);

/* map */
t_map	*read_map(char *fpath);

int		handle_no_event(void *data);
int		handle_close_event(t_data *data);
int key_down(int keycode, t_data *data);
int key_up(int keycode, t_data *data);
// void	render(t_data *data);

#endif // SO_LONG_H
