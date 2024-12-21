/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 12:13:15 by ielyatim          #+#    #+#             */
/*   Updated: 2024/12/21 15:18:52 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

typedef struct s_img {
    void    *img_ptr;
    char    *addr;
    int     bpp;
    int     line_length;
    int     endian;
    int     width;
    int     height;
} t_img;

void flip_horizontal(t_img *img);
void flip_vertical(t_img *img);
t_img *img_init(void *mlx_ptr, char *img_path);

#endif // IMAGE_H
