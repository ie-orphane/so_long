/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 12:13:18 by ielyatim          #+#    #+#             */
/*   Updated: 2024/12/22 11:14:35 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void flip_horizontal(t_img *img)
{
	int y, x;
	int pixel_size = img->bpp / 8;
	char *temp_row;

	temp_row = malloc(img->width * pixel_size);
	if (!temp_row)
		return;
	for (y = 0; y < img->height; y++)
	{
		char *row = img->addr + (y * img->line_length);
		for (x = 0; x < img->width / 2; x++)
		{
			int opposite = img->width - x - 1;
			char *pixel = row + (x * pixel_size);
			char *opposite_pixel = row + (opposite * pixel_size);

			ft_memcpy(temp_row, pixel, pixel_size);
			ft_memcpy(pixel, opposite_pixel, pixel_size);
			ft_memcpy(opposite_pixel, temp_row, pixel_size);
		}
	}
	free(temp_row);
}

void flip_vertical(t_img *img)
{
	int y;
	char *temp_row;

	temp_row = malloc(img->line_length);
	if (!temp_row)
		return;
	for (y = 0; y < img->height / 2; y++)
	{
		int opposite = img->height - y - 1;
		char *row = img->addr + (y * img->line_length);
		char *opposite_row = img->addr + (opposite * img->line_length);

		ft_memcpy(temp_row, row, img->line_length);
		ft_memcpy(row, opposite_row, img->line_length);
		ft_memcpy(opposite_row, temp_row, img->line_length);
	}
	free(temp_row);
}

void	put_pixel_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (color == (int)TRANSPARENT_COLOR)
		return;
	if (x >= 0 && y >= 0 && x < img->width && y < img->height) {
		dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
		*(unsigned int *) dst = color;
	}
}

unsigned int	get_pixel_img(t_img *img, int x, int y) {
	return (*(unsigned int *)((img->addr + (y * img->line_length) + (x * img->bpp / 8))));
}

void	put_img_to_img(t_img *dst, t_img *src, int x, int y) {
	int i;
	int j;

	i = 0;
	while(i < src->width) {
		j = 0;
		while (j < src->height) {
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
	img->img_ptr = mlx_new_image(mlx_ptr, width, height);
	img->addr = mlx_get_data_addr(img->img_ptr, &(img->bpp),
			&(img->line_length), &(img->endian));
	img->width = width;
	img->height = height;
	return (img);
}

// t_img	*img_to_img(void *mlx_ptr, char *img_path)
// {
// 	t_img img_org;
// 	t_img *img_cpy;

// 	img_org.img_ptr = mlx_xpm_file_to_image(
// 		mlx_ptr,
// 		img_path,
// 		&img_org.width,
// 		&img_org.height);
// 	if (img_org.img_ptr == NULL)
// 	{
// 		ft_printf("Image not found: %s\n", img_path);
// 		exit(EXIT_FAILURE);
// 	}
// 	if (img_org.height != FRAME_SIZE || img_org.width != FRAME_SIZE)
// 	{
// 		ft_printf("Size error: Image dimensions must be %dx%d\n", FRAME_SIZE, FRAME_SIZE);
// 		mlx_destroy_image(mlx_ptr, img_org.img_ptr);
// 		exit(EXIT_FAILURE);
// 	}
// 	img_org.addr = mlx_get_data_addr(img_org.img_ptr, &img_org.bpp, &img_org.line_length, &img_org.endian);
// 	img_cpy = img_new(mlx_ptr);
// 	put_img_to_img(img_cpy, &img_org, 0,0);
// 	mlx_destroy_image(mlx_ptr, img_org.img_ptr);
// 	return (img_cpy);
// }

t_img	*img_init(void *mlx_ptr, char *img_path)
{
	t_img *img;

	img = malloc(sizeof(t_img));
	if (img == NULL)
	{
		ft_printf("Allocation error: %s\n", img_path);
		exit(EXIT_FAILURE);
	}
	img->img_ptr = mlx_xpm_file_to_image(
		mlx_ptr,
		img_path,
		&img->width,
		&img->height);
	if (img->img_ptr == NULL)
	{
		ft_printf("Image not found: %s\n", img_path);
		exit(EXIT_FAILURE);
	}
	if (img->height != FRAME_SIZE || img->width != FRAME_SIZE)
	{
		ft_printf("Size error: Image dimensions must be %dx%d\n", FRAME_SIZE, FRAME_SIZE);
		mlx_destroy_image(mlx_ptr, img->img_ptr);
		exit(EXIT_FAILURE);
	}
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line_length, &img->endian);
	return (img);
}
