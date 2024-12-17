/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:40:06 by ielyatim          #+#    #+#             */
/*   Updated: 2024/12/17 18:09:30 by ielyatim         ###   ########.fr       */
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
# include "libft/libft.h"
# include "read_map.h"

# define MLX_ERROR 1

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define WIN_TITLE "my game"

typedef struct s_data
{
	void	*mlx;
	void	*win;
}	t_data;

typedef struct s_img
{
	void *self;
	int width;
	int height;
} t_img;

int	handle_no_event(void *data);
int	handle_close_event(t_data *data);
int	handle_keypress_event(int keycode, t_data *data);

#endif // SO_LONG_H
