/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaak <zaak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 14:12:01 by gaeducas          #+#    #+#             */
/*   Updated: 2026/01/08 21:03:38 by zaak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static char	**copy_grid(t_data *data)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (data->map.height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < data->map.height)
	{
		copy[i] = ft_strdup(data->map.grid[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static void	free_temp_grid(char **grid, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

static void	flood_fill(char **map, int x, int y, t_map *map_info)
{
	if (x < 0 || y < 0 || x >= map_info->width || y >= map_info->height)
		return ;
	if (map[y][x] == '1' || map[y][x] == 'V')
		return ;
	map[y][x] = 'V';
	flood_fill(map, x + 1, y, map_info);
	flood_fill(map, x - 1, y, map_info);
	flood_fill(map, x, y + 1, map_info);
	flood_fill(map, x, y - 1, map_info);
}

static int	check_accessibility(char **temp, t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if (temp[y][x] == 'C' || temp[y][x] == 'E')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	ft_check_path_validity(t_data *data)
{
	char	**temp;
	int		x;
	int		y;
	int		valid;

	y = 0;
	x = 0;
	while (data->map.grid[y][x] != 'P')
	{
		x++;
		if (data->map.grid[y][x] == '\0')
		{
			x = 0;
			y++;
		}
	}
	temp = copy_grid(data);
	if (!temp)
		return (0);
	flood_fill(temp, x, y, &data->map);
	valid = check_accessibility(temp, data);
	free_temp_grid(temp, data->map.height);
	if (!valid)
		ft_putstr_fd("Error\nCollectibles or Exit unreachable.\n", 2);
	return (valid);
}
