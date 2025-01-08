/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 08:26:06 by ielyatim          #+#    #+#             */
/*   Updated: 2024/11/05 11:04:33 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dst_tmp;
	char	*src_tmp;

	if (!dst && !src)
		return (NULL);
	dst_tmp = (char *)dst;
	src_tmp = (char *)src;
	while (n-- > 0)
		*(dst_tmp++) = *(src_tmp++);
	return (dst);
}
