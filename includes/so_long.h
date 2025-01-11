/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:40:06 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/11 18:48:33 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "ft_printf.h"
# include "image.h"
# include "libft.h"
# include "sprite.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define WIN_TITLE "Tiny Swords"
# define SPEED 16

typedef struct s_map_check
{
	char			**content;
	int				ccount;
	bool			exit;
	bool			player;
}					t_map_check;

typedef struct s_shape
{
	int				x;
	int				y;
	int				w;
	int				h;
}					t_shape;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	char			**map;
	char			**map_cpy;
	int				width;
	int				height;
	t_img			*img;
	double			brightness;
	t_img			**ts_ground;
	t_img			**ts_numbers;
	t_img			**ts_letters;
	t_img			**ts_banner;
	t_img			*tiles[TILES_MAX];
	t_frame			f_foam;
	t_frame			f_enemy;
	t_frame			f_dying;
	t_troop_frame	f_player;
	bool			f_updated;
	int				keys[256];
	int				steps;
	char			direction;
	int				px;
	int				py;
	int				pcount;
	int				ccount;
}					t_data;

/* utils */
char				*read_file(char *fpath);
char				*filename_to_path(const char *dir, int index);
int					randint(int min, int max);
bool				shape_overlap(t_shape a, t_shape b);
char				*ft_ultimate_strjoin(size_t count, ...);

/* frames & tiles */
void				init_frames(t_data *data);
void				init_tiles(t_data *data);

/* animate */
void				update_position(t_data *data, int *next_x, int *next_y);
void				update_frame(t_data *data, void (*callable)(t_data *),
						t_frame_ref frame);

/* check & map */
void				check_line_size(t_data *data);
void				check_blocks(t_data *data);
void				check_map_size(t_data *data);
void				check_path(t_data *data);
void				check_closed(t_data *data);
void				flood_fill(t_data *data, t_map_check *map, int x, int y);
void				parse_map(t_data *data, char *fpath);

/* events */
int					handle_close_event(void);
int					key_down(int keycode, t_data *data);
int					key_up(int keycode, t_data *data);
int					keyin(t_data *data, int arr[]);

/* layers & ground */
void				put_ground_layers(t_data *data);
void				put_entities_layers(t_data *data);

#endif // SO_LONG_H
