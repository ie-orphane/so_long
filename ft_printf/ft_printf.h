/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:37:50 by ielyatim          #+#    #+#             */
/*   Updated: 2025/01/13 16:13:38 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>

char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);

void	ft_putchar(int *count, const char c);
void	ft_putstr(int *count, const char *s);
void	ft_putnbr(int *count, long n);
void	ft_puthex(int *count, unsigned long n, const char x);
void	ft_putunbr(int *count, unsigned long n);

int		ft_printf(const char *format, ...);

#endif
