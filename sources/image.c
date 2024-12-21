/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 12:13:18 by ielyatim          #+#    #+#             */
/*   Updated: 2024/12/21 15:18:27 by ielyatim         ###   ########.fr       */
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
