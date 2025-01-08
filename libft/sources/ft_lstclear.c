/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:13:48 by ielyatim          #+#    #+#             */
/*   Updated: 2024/11/01 14:46:39 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current_lst;
	t_list	*tmp;

	if (lst && del)
	{
		current_lst = (*lst);
		while (current_lst)
		{
			del(current_lst->content);
			tmp = current_lst->next;
			free(current_lst);
			current_lst = tmp;
		}
		*lst = NULL;
	}
}
