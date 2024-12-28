/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 12:13:15 by ielyatim          #+#    #+#             */
/*   Updated: 2024/12/24 11:42:13 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

#define TRANSPARENT_COLOR 0xFF000000

typedef struct s_img {
    void    *img_ptr;
    char    *addr;
    int     bpp;
    int     line_length;
    int     endian;
    int     width;
    int     height;
} t_img;

t_img *img_init(void *mlx_ptr, char *img_path);
void	put_img_to_img(t_img *dst, t_img *src, int x, int y);
t_img	*img_new(void *mlx_ptr, int width, int height);

#endif // IMAGE_H
