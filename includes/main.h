/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 11:02:24 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/12 17:28:56 by ielyatim         ###   ########.fr       */
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
	char	**content;
	int		ccount;
	bool	exit;
	bool	player;
}			t_map_check;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	char	**map;
	int		width;
	int		height;
	t_img	*img;
	double	brightness;
	t_img	**ts_wall;
	// t_img			**ts_numbers;
	// t_img			**ts_letters;
	// t_img			**ts_banner;
	t_img	*tiles[TILES_MAX];
	bool	updated;
	// int				steps;
	// char			direction;
	int		keys[256];
	int		px;
	int		py;
	int		pcount;
	int		ccount;
}			t_data;

void		check_line_size(t_data *data);
void		check_blocks(t_data *data);
void		check_map_size(t_data *data);
void		check_path(t_data *data);
void		check_closed(t_data *data);
void		flood_fill(t_data *data, t_map_check *map, int x, int y);
void		parse_map(t_data *data, char *fpath);

int			handle_close_event(void);
int			key_down(int keycode, t_data *data);
int			key_up(int keycode, t_data *data);
int			keyin(t_data *data, int arr[]);

#endif // MAIN_H
