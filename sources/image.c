/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 12:13:18 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/08 15:51:57 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_pixel_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (color == (int)TRANSPARENT_COLOR || color == 0x0)
		return ;
	if (x >= 0 && y >= 0 && x < img->width && y < img->height)
	{
		dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

unsigned int	get_pixel_img(t_img *img, int x, int y)
{
	return (*(unsigned int *)(
		(img->addr + (y * img->line_length) + (x * img->bpp / 8))));
}

void	put_img_to_img(t_img *dst, t_img *src, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < src->width)
	{
		j = 0;
		while (j < src->height)
		{
			put_pixel_img(dst, x + i, y + j, get_pixel_img(src, i, j));
			j++;
		}
		i++;
	}
}

t_img	*img_new(void *mlx_ptr, int width, int height)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (img == NULL)
	{
		ft_printf("Allocation error: %s\n", "empty");
		exit(EXIT_FAILURE);
	}
	img->ptr = mlx_new_image(mlx_ptr, width, height);
	img->addr = mlx_get_data_addr(img->ptr, &(img->bpp),
			&(img->line_length), &(img->endian));
	img->width = width;
	img->height = height;
	return (img);
}

t_img	*img_init(void *mlx_ptr, char *img_path)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (img == NULL)
	{
		ft_printf("Allocation error: %s\n", img_path);
		exit(EXIT_FAILURE);
	}
	img->ptr = mlx_xpm_file_to_image(mlx_ptr, img_path,
			&img->width, &img->height);
	if (img->ptr == NULL)
	{
		ft_printf("Image not found: %s\n", img_path);
		exit(EXIT_FAILURE);
	}
	// if (img->height != TILE_SIZE || img->width != TILE_SIZE)
	// {
	// 	ft_printf("Size error: Image dimensions must be %dx%d\n",
	// 		TILE_SIZE, TILE_SIZE);
	// 	mlx_destroy_image(mlx_ptr, img->ptr);
	// 	exit(EXIT_FAILURE);
	// }
	img->addr = mlx_get_data_addr(img->ptr, &img->bpp,
			&img->line_length, &img->endian);
	return (img);
}
