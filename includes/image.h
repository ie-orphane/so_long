/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 12:13:15 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/12 22:52:37 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include "libs.h"

# define TRANSPARENT_COLOR 0xFF000000

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct s_img
{
	void		*ptr;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_img;

t_img			*img_init(void *mlx_ptr, char *img_path);
void			put_img_to_img(t_img *dst, t_img *src, t_point pixel,
					double brightness);
t_img			*img_new(void *mlx_ptr, int width, int height);
void			put_pixel_img(t_img *img, int x, int y, unsigned int color);
unsigned int	darken_color(unsigned int color, double factor);

#endif // IMAGE_H
