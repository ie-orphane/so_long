/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:40:06 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/06 17:28:33 by ielyatim         ###   ########.fr       */
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
# include "image.h"
# include "mlx.h"
# include "sprite.h"

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define WIN_TITLE "my game"

# define IDLE_FRAMES 6
# define RUN_FRAMES 6
# define COLLECTIVE_FRAMES 14
# define EXIT_FRAMES 8
# define ENEMY_FRAMES 7
# define FOAM_FRAMES 8

# define ANIMATION_DELAY 10000
# define SPEED 16

typedef struct s_map {
	char *content;
	int width;
	int height;
	char **blocks;
	int x;
	int y;
	size_t collective;
} t_map;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_map	*map;
	t_img	*img;

	void	*t_ground[TILESET_GROUND_MAX];

	t_frame f_foam;
	t_frame f_enemy;
	t_frame f_sheep;

	t_troop_frame f_player;

	char direction;

	t_img	*tiles[TILES_MAX];

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
void	init_sprites(t_data *data);


/* map */
t_map	*read_map(t_data *data, char *fpath);

int		handle_close_event();
int key_down(int keycode, t_data *data);
int key_up(int keycode, t_data *data);

#endif // SO_LONG_H
