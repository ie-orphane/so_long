/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 10:51:07 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/26 21:11:38 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_BONUS_H
# define SPRITE_BONUS_H

typedef struct timeval	t_timeval;

# define TILE_SIZE 64

// TILES
# define TILE_WATER 0
# define TILE_GOLD 1
# define TILE_MINE_ACTIVE 2
# define TILE_MINE_INACTIVE 3
# define TILE_MINE_DESTROYED 4
# define TILE_COLON 5
# define TILE_SEMI_COLON 6
# define TILE_PERIOD 7
# define TILES_MAX 8

// FRAMES
typedef struct s_frame
{
	t_img				**all;
	unsigned int		count;
	unsigned int		max;
	unsigned int		delay;
	t_timeval			current_time;
	t_timeval			last_time;
}						t_frame;

typedef struct s_frame_ref
{
	unsigned int		*count;
	unsigned int		max;
	unsigned int		delay;
	t_timeval			*current_time;
	t_timeval			*last_time;
}						t_frame_ref;

typedef struct s_frame_info
{
	unsigned int		delay;
	unsigned int		max;
}						t_frame_info;

// TROOP FRAMES
# define TROOP_FRAMES_MAX 4

typedef enum e_troop_state
{
	IDLE_RIGHT = 0,
	IDLE_LEFT = 1,
	RUN_RIGHT = 2,
	RUN_LEFT = 3,
	DEAD = 5,
	EXITING = 6,
	EXIT = 7,
}						t_troop_state;

typedef struct s_troop_frame
{
	t_img				**all[TROOP_FRAMES_MAX];
	t_troop_state		state;
	unsigned int		count;
	unsigned int		max;
	unsigned int		delay;
	t_timeval			current_time;
	t_timeval			last_time;
}						t_troop_frame;

#endif // SPRITE_BONUS_H
