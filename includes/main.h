/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 11:02:24 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/19 14:44:03 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "image.h"
# include "libs.h"
# include "sprite.h"
# include "utils.h"

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define WIN_TITLE "Pixel Dungeon"
# define SPEED 16

typedef struct s_map_check
{
	char		**content;
	int			ccount;
	bool		exit;
	bool		player;
	t_point		max;
	t_point		min;
}				t_map_check;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	char		**map;
	int			width;
	int			height;
	t_img		*img;
	t_map_check	check;
	double		brightness;
	t_img		**ts_wall;
	t_img		**ts_exit;
	t_img		*tiles[TILES_MAX];
	bool		updated;
	bool		game_over;
	t_point		min;
	t_point		max;
	int			steps;
	t_point		p;
	int			pcount;
	int			ccount;
}				t_data;

void			flood_fill(t_data *data, t_point pos);
void			flood_fill2(t_data *data, t_point pos, char f, char prev);

void			check_line_size(t_data *data);
void			check_blocks(t_data *data);
void			check_map_size(t_data *data);
void			check_path(t_data *data);
void			check_closed(t_data *data);
void			parse_map(t_data *data, char *fpath);

void			put_scaled_img_to_img(t_img *dst, t_img *src, t_point pixel,
					double brightness);
void			img_destroy(void *mlx_ptr, t_img **img);
t_img			*wall_tile(t_data *data, int x, int y);
t_img			**init_tileset(void *mlx_ptr, int max, char *dir);

void			ft_exit(t_data *data, int status);
void			ft_ultimate_error(t_data *data, char *msg);

int				destroy_handler(t_data *data);
int				key_handler(int keycode, t_data *data);
int				loop_handler(t_data *data);

#endif // MAIN_H
