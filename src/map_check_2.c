/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 15:33:18 by gaeducas          #+#    #+#             */
/*   Updated: 2026/01/09 15:39:17 by gaeducas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	ft_check_chars_validity(t_data *data)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			c = data->map.grid[y][x];
			if (c != '0' && c != '1' && c != 'P' && c != 'E' && c != 'C')
			{
				ft_putstr_fd("Error\nInvalid character found in map.\n", 2);
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}
