/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:53:44 by gaeducas          #+#    #+#             */
/*   Updated: 2025/11/04 13:47:59 by gaeducas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	ft_put_ptr(void *ptr)
{
	unsigned long long int	nb;
	char					*hex;
	int						len;

	len = 0;
	hex = "0123456789abcdef";
	nb = (unsigned long long int)ptr;
	if (nb >= 16)
		len += ft_put_ptr((void *)(nb / 16));
	ft_putchar(hex[nb % 16]);
	len += 1;
	return (len);
}

int	ft_ptr_verif(void *ptr)
{
	int	len;

	len = 0;
	if (!ptr)
	{
		ft_putstr("(nil)");
		return (5);
	}
	len += ft_putstr("0x");
	len += ft_put_ptr(ptr);
	return (len);
}
