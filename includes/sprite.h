/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 18:36:32 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/09 14:38:26 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_H
# define SPRITE_H

typedef unsigned int	t_uint;
typedef struct timeval	t_timeval;

# define TILE_SIZE 64

// TILES
# define TILE_WATER 0
# define TILE_GOLD 1
# define TILE_MINE_ACTIVE 2
# define TILE_MINE_INACTIVE 3
# define TILE_MINE_DESTROYED 4
# define TILES_MAX 5

// TILE SETS
# define TILESET_GROUND_MAX 16
# define TILESET_GROUND_PATH "./textures/grass/green/"

// FRAMES
typedef struct s_frame
{
	t_img				**all;
	t_uint				count;
	t_uint				max;
	t_uint				delay;
	t_timeval			current_time;
	t_timeval			last_time;
}						t_frame;

typedef struct s_frame_ref
{
	t_uint				*count;
	t_uint				max;
	t_uint				delay;
	t_timeval			*current_time;
	t_timeval			*last_time;
}						t_frame_ref;

typedef struct s_frame_info
{
	t_uint				delay;
	t_uint				max;
}						t_frame_info;

// TROOP FRAMES
# define TROOP_FRAMES_MAX 4

typedef enum e_troop_state
{
	IDLE_RIGHT = 0,
	IDLE_LEFT = 1,
	RUN_RIGHT = 2,
	RUN_LEFT = 3,
}						t_troop_state;

typedef struct s_troop_frame
{
	t_img				**all[TROOP_FRAMES_MAX];
	t_troop_state		state;
	t_uint				count;
	t_uint				max;
	t_uint				delay;
	t_timeval			current_time;
	t_timeval			last_time;
}						t_troop_frame;

#endif // SPRITE_H
