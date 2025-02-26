/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 11:58:41 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/19 18:30:03 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

void	put_pixel_img(t_img *img, int x, int y, unsigned int color)
{
	char	*dst;

	if (color == (unsigned int)TRANSPARENT_COLOR)
		return ;
	if (x >= 0 && y >= 0 && x < img->width && y < img->height)
	{
		dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

unsigned int	darken_color(unsigned int color, double factor)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	if (factor < 0.0)
		factor = 0.0;
	if (factor >= 1.0)
		return (color);
	r = ((color >> 16) & 0xFF) * (1.0 - factor);
	g = ((color >> 8) & 0xFF) * (1.0 - factor);
	b = (color & 0xFF) * (1.0 - factor);
	return ((color & 0xFF000000) | (r << 16) | (g << 8) | b);
}

void	put_img_to_img(t_img *dst, t_img *src, t_point pixel, double brightness)
{
	int				i;
	int				j;
	unsigned int	color;

	i = 0;
	while (i < src->width)
	{
		j = 0;
		while (j < src->height)
		{
			color = (*(unsigned int *)((src->addr + (j * src->line_length) + (i
								* src->bpp / 8))));
			color = darken_color(color, brightness);
			put_pixel_img(dst, pixel.x + i, pixel.y + j, color);
			j++;
		}
		i++;
	}
}

t_img	*img_new(void *mlx_ptr, int width, int height)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	img->ptr = mlx_new_image(mlx_ptr, width, height);
	img->addr = mlx_get_data_addr(img->ptr, &(img->bpp), &(img->line_length),
			&(img->endian));
	img->width = width;
	img->height = height;
	return (img);
}

t_img	*img_init(void *mlx_ptr, char *img_path)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	img->ptr = mlx_xpm_file_to_image(mlx_ptr, img_path, &img->width,
			&img->height);
	if (!img->ptr)
	{
		ft_printf(ERROR_START "Image not found: %s" ERROR_END, img_path);
		return (NULL);
	}
	img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->line_length,
			&img->endian);
	if (!img->addr)
	{
		ft_printf(ERROR_START "Getting image data failed: %s" ERROR_END,
			img_path);
		return (NULL);
	}
	return (img);
}
