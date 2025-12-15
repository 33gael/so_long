/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazmat <hazmat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:57:35 by hazmat            #+#    #+#             */
/*   Updated: 2025/10/23 14:55:24 by hazmat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int searchchar)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i >= 0)
	{
		if (str[i] == (unsigned char)searchchar)
			return ((char *)str + i);
		i--;
	}
	if (searchchar == '\0' && !str[i])
		return ((char *)str + i);
	return (NULL);
}
