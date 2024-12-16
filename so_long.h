/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:40:06 by ielyatim          #+#    #+#             */
/*   Updated: 2024/12/16 12:16:47 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <mlx.h>
# include <stdlib.h>
# include <X11/keysym.h>
# include <X11/X.h>

# include "ft_printf/ft_printf.h"


#define MLX_ERROR 1

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define WINDOW_TITLE "my game"


typedef	struct s_data
{
	void *mlx;
	void *win;
} t_data;


int	handle_no_event(void *data);
int handle_close_event(t_data *data);
int handle_keypress_event(int keycode, t_data *data);

#endif // SO_LONG_H
