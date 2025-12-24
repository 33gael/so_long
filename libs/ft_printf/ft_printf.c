/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:34:26 by gaeducas          #+#    #+#             */
/*   Updated: 2025/11/04 17:15:16 by gaeducas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_percent(va_list ap, char c)
{
	int	count;

	count = 0;
	if (c == 's')
		count += ft_putstr(va_arg(ap, char *));
	else if (c == '%')
		count += ft_putchar('%');
	else if (c == 'd' || c == 'i')
		count += ft_putnbr(va_arg(ap, int));
	else if (c == 'u')
		count += ft_putnbr_unsigned(va_arg(ap, unsigned int));
	else if (c == 'X' || c == 'x')
		count += ft_putnbr_hex(va_arg(ap, unsigned int), c == 'X');
	else if (c == 'c')
		count += ft_putchar(va_arg(ap, int));
	else if (c == 'p')
		count += ft_ptr_verif(va_arg(ap, void *));
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	size_t	i;
	int		count;

	if (format == NULL)
		return (-1);
	count = 0;
	va_start(ap, format);
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			count += ft_percent(ap, format[i + 1]);
			i++;
		}
		else
			count += ft_putchar(format[i]);
		if (format[i])
			i++;
	}
	va_end(ap);
	return (count);
}
