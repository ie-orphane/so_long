/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 10:50:42 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/12 11:00:40 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_BONUS_H
# define MAIN_BONUS_H

# include "libs.h"
# include "image.h"
# include "utils.h"
# include "sprite_bonus.h"

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

typedef struct s_data
{
	void			*mlx;
	void			*win;
	char			**map;
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

#endif // MAIN_BONUS_H