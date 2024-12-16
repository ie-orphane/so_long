/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 18:00:38 by ielyatim          #+#    #+#             */
/*   Updated: 2024/11/14 09:53:50 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(int *count, const char c)
{
	write(1, &c, 1);
	(*count) += 1;
}

void	ft_putstr(int *count, const char *s)
{
	size_t	s_len;

	if (!s)
		return (ft_putstr(count, "(null)"));
	s_len = ft_strlen(s);
	write(1, s, s_len);
	(*count) += s_len;
}

void	ft_putnbr(int *count, long n)
{
	if (n < 0)
	{
		ft_putchar(count, '-');
		ft_putnbr(count, -n);
	}
	else
	{
		if (n >= 10)
			ft_putnbr(count, n / 10);
		ft_putchar(count, n % 10 + '0');
	}
}

void	ft_puthex(int *count, unsigned long n, const char x)
{
	char	c;

	if (n >= 16)
		ft_puthex(count, n / 16, x);
	c = "0123456789abcdef"[n % 16];
	if (97 <= c && c <= 122 && x == 'X')
		c -= 32;
	ft_putchar(count, c);
}

void	ft_putunbr(int *count, unsigned long n)
{
	if (n >= 10)
		ft_putunbr(count, n / 10);
	ft_putchar(count, n % 10 + '0');
}
