/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:11:45 by gaeducas          #+#    #+#             */
/*   Updated: 2026/01/09 16:22:07 by gaeducas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	check_screen_size(t_data *data)
{
	if (data->map.width > MAX_WIDTH)
	{
		ft_putstr_fd("Error\nMap is too wide for the screen.\n", 2);
		return (0);
	}
	if (data->map.height > MAX_HEIGHT)
	{
		ft_putstr_fd("Error\nMap is too high for the screen.\n", 2);
		return (0);
	}
	return (1);
}

static int	check_rectangular(t_data *data)
{
	int	i;

	i = 0;
	while (data->map.grid[i])
	{
		if (ft_strlen(data->map.grid[i]) != (size_t)data->map.width)
			return (0);
		i++;
	}
	return (1);
}

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
		ft_putstr_fd("Error\nThe map must contain exactly 1 Player (P).\n", 2);
		return (0);
	}
	if (data->map.e_count != 1)
	{
		ft_putstr_fd("Error\nThe map must contain exactly 1 Exit (E).\n", 2);
		return (0);
	}
	if (data->map.c_count < 1)
	{
		ft_putstr_fd("Error\nThe map must contain at least 1 Collectible (C)."
			"\n", 2);
		return (0);
	}
	return (1);
}

int	ft_check_map_validity(t_data *data)
{
	if (!check_rectangular(data))
	{
		ft_putstr_fd("Error\nThe map is not rectangular\n", 2);
		return (0);
	}
	if (!check_walls(data))
	{
		ft_putstr_fd("Error\nThe map is not surrounded by walls (1).\n", 2);
		return (0);
	}
	if (!check_counts(data))
		return (0);
	if (!check_screen_size(data))
		return (0);
	if (!ft_check_chars_validity(data))
		return (0);
	return (1);
}
