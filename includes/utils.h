/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 10:58:18 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/19 10:44:56 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libs.h"

typedef struct s_shape
{
	int	x;
	int	y;
	int	w;
	int	h;
}		t_shape;

char	*read_file(char *fpath);
char	**read_map(char *fpath);

void	ft_error(char *msg);

char	*filename_to_path(const char *dir, int index);
bool	shape_overlap(t_shape a, t_shape b);

double	dmin(double a, double b);

#endif // UTILS_H
