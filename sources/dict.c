/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:04:54 by ielyatim          #+#    #+#             */
/*   Updated: 2024/12/22 12:44:00 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dict.h"

void	dict_add(t_dict **dict, const char key, void *value)
{
	t_dict	*new;

	new = malloc(sizeof(t_dict));
	if (!new)
		return ;
	new->key = key;
	new->value = value;
	if (*dict != NULL)
		new->next = *dict;
	*dict = new;
}

void	*dict_find(t_dict **dict, const char key)
{
	t_dict	*current;

	if (!dict || !*dict)
		return (NULL);
	current = *dict;
	while (current)
	{
		if (current->key == key)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void	dict_clear(t_dict **dict, void (*del)(void *))
{
	t_dict	*current_dict;
	t_dict	*tmp;

	if (!dict || !*dict)
		return ;
	current_dict = *dict;
	while (current_dict)
	{
		if (del)
			del(current_dict->value);
		tmp = current_dict->next;
		free(current_dict);
		current_dict = tmp;
	}
	*dict = NULL;
}

void	dict_free(void *value)
{
	free(value);
}
