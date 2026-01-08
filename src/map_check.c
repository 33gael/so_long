/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:11:45 by gaeducas          #+#    #+#             */
/*   Updated: 2026/01/08 10:04:40 by gaeducas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	check_walls(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map.width)
	{
		if (data->map.grid[0][i] != '1' || data->map.grid[data->map.height
			- 1][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < data->map.height)
	{
		if (data->map.grid[i][0] != '1' || data->map.grid[i][data->map.width
			- 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

static int	check_counts(t_data *data)
{
	if (data->map.p_count != 1)
	{
		ft_printf("Error\nThe map must contain exactly 1 Player (P).\n");
		return (0);
	}
	if (data->map.e_count != 1)
	{
		ft_printf("Error\nThe map must contain exactly 1 Exit (E).\n");
		return (0);
	}
	if (data->map.c_count < 1)
	{
		ft_printf("Error\nThe map must contain at least 1 Collectible (C).\n");
		return (0);
	}
	return (1);
}

int	ft_check_map_validity(t_data *data)
{
	if (!check_walls(data))
	{
		ft_printf("Error\nThe map is not surrounded by walls (1).\n");
		return (0);
	}
	if (!check_counts(data))
		return (0);
	return (1);
}
