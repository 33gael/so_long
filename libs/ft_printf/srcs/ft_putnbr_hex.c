/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:00:44 by gaeducas          #+#    #+#             */
/*   Updated: 2025/11/04 10:54:52 by gaeducas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_putnbr_hex(unsigned int nb, int uppercase)
{
	char	*hex;
	int		len;

	len = 0;
	if (uppercase)
		hex = "0123456789ABCDEF";
	else
		hex = "0123456789abcdef";
	if (nb >= 16)
		len += ft_putnbr_hex(nb / 16, uppercase);
	ft_putchar(hex[nb % 16]);
	len += 1;
	return (len);
}
