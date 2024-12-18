/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_find.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:30:57 by ielyatim          #+#    #+#             */
/*   Updated: 2024/12/18 12:00:51 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dict.h"

void	*dict_find(t_dict **dict, const char *key)
{
	t_dict	*current;

	if (!dict || !*dict)
		return (NULL);
	current = *dict;
	while (current)
	{
		if (ft_strncmp(current->key, key, DICT_KEY_SIZE) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}
