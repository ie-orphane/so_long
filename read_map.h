/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:10:45 by ielyatim          #+#    #+#             */
/*   Updated: 2024/12/16 21:43:12 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_MAP_H
# define READ_MAP_H

# include <fcntl.h>
// # include <unistd.h>
# include <stdio.h>
// # include <stdlib.h>

typedef struct s_map {
	char *content;
	int width;
	int height;
	char **blocks;
} t_map;

char	*read_file(int fd);
t_map	*read_map(char *fpath);

#endif // READ_MAP_H