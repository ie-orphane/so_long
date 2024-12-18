/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:30:53 by ielyatim          #+#    #+#             */
/*   Updated: 2024/12/18 11:59:30 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dict.h"

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
