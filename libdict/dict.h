/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:26:09 by ielyatim          #+#    #+#             */
/*   Updated: 2024/12/18 12:01:29 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DICT_H
# define DICT_H

# include "libft.h"

# define DICT_KEY_SIZE 25

typedef struct s_dict
{
	char			key[DICT_KEY_SIZE];
	void			*value;
	struct s_dict	*next;
}	t_dict;

void	dict_add(t_dict **dict, const char *key, void *value);
void	*dict_find(t_dict **dict, const char *key);
void	dict_free(void *value);
void	dict_clear(t_dict **dict, void (*del)(void *));

#endif // DICT_H
