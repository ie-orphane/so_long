/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:40:06 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/07 12:17:43 by ielyatim         ###   ########.fr       */
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
# include "mlx.h"
# include "image.h"
# include "sprite.h"

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define WIN_TITLE "Tiny Swords"
# define SPEED 16

typedef struct s_shape
{
	int	x;
	int	y;
	int	w;
	int	h;
}	t_shape;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	char			**map;
	int				width;
	int				height;
	t_img			*img;
	t_img			*t_ground[TILESET_GROUND_MAX];
	t_img			*tiles[TILES_MAX];
	t_frame			f_foam;
	t_frame			f_enemy;
	t_frame			f_sheep;
	t_troop_frame	f_player;
	int				keys[256];
	int				steps;
	char			direction;
	int				px;
	int				py;
	int				pcount;
	int				ccount;
}	t_data;

/* utils */
char	*read_file(char *fpath);
int		ft_strset(const char *str, const char *set);
char	*filename_to_path(const char *dir, int index);
int		randint(int min, int max);

/* frames */
void	init_sprites(t_data *data);

/* map */
void	read_map(t_data *data, char *fpath);

/* events */
int		handle_close_event(void);
int		key_down(int keycode, t_data *data);
int		key_up(int keycode, t_data *data);

/* layers */
void	put_ground_layers(t_data *data);
int		frames_overlap(int ax, int ay, int bx, int by);
int		shape_overlap(t_shape a, t_shape b);
void	put_entities_layers(t_data *data);

#endif // SO_LONG_H
