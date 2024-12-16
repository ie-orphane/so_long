/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:40:06 by ielyatim          #+#    #+#             */
/*   Updated: 2024/12/16 09:32:18 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <mlx.h>

// #ifndef WINDOW_WIDTH
# define WINDOW_WIDTH 1920
// #endif

// #ifndef WINDOW_HEIGHT
# define WINDOW_HEIGHT 1080
// #endif

// #ifndef WINDOW_TITLE
# define WINDOW_TITLE "my game"
// #endif


typedef	struct s_data
{
	void *mlx;
	void *win;
} t_data;

#endif // SO_LONG_H
