/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:30:35 by ielyatim          #+#    #+#             */
/*   Updated: 2024/12/18 11:31:13 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dict.h"

void	dict_add(t_dict **dict, const char *key, void *value)
{
	t_dict	*new;

	new = malloc(sizeof(t_dict));
	ft_strlcpy(new->key, key, DICT_KEY_SIZE);
	new->value = value;
	if (*dict != NULL)
		new->next = *dict;
	*dict = new;
}
