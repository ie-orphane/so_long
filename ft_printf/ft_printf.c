/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:35:16 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/09 11:19:04 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_conversions(va_list args, char conv, int *count)
{
	void	*p;

	if (conv == '%')
		ft_putchar(count, '%');
	else if (conv == 'c')
		ft_putchar(count, va_arg(args, int));
	else if (conv == 's')
		ft_putstr(count, va_arg(args, char *));
	else if (conv == 'd' || conv == 'i')
		ft_putnbr(count, va_arg(args, int));
	else if (conv == 'u')
		ft_putunbr(count, va_arg(args, unsigned int));
	else if (conv == 'x' || conv == 'X')
		ft_puthex(count, va_arg(args, unsigned int), conv);
	else if (conv == 'p')
	{
		p = va_arg(args, void *);
		if (p == NULL)
			ft_putstr(count, "(nil)");
		else
		{
			ft_putstr(count, "0x");
			ft_puthex(count, (unsigned long)p, 'x');
		}
	}
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	if (write(1, 0, 0))
		return (-1);
	va_start(args, format);
	count = 0;
	while (*format)
	{
		if (*format == '%' && ft_strchr("%csdiuxXp", *(format + 1)))
		{
			ft_conversions(args, *(format + 1), &count);
			format++;
		}
		else
			ft_putchar(&count, *format);
		format++;
	}
	va_end(args);
	return (count);
}

void	ft_error(const char *msg, ...)
{
	va_list	args;
	int		count;

	if (write(1, 0, 0))
		exit(2);
	va_start(args, msg);
	count = 0;
	ft_printf("Error\n");
	while (*msg)
	{
		if (*msg == '%' && ft_strchr("%csdiuxXp", *(msg + 1)))
		{
			ft_conversions(args, *(msg + 1), &count);
			msg++;
		}
		else
			ft_putchar(&count, *msg);
		msg++;
	}
	va_end(args);
	exit(1);
}
