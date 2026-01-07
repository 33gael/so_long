/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 11:02:49 by gaeducas          #+#    #+#             */
/*   Updated: 2026/01/07 15:52:06 by gaeducas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	ft_remove_newline(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n' || line[i] == '\r')
		{
			line[i] = '\0';
			return ;
		}
		i++;
	}
}

static int	get_map_height(char *filename)
{
	int		fd;
	int		height;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	height = 0;
	while ((line = get_next_line(fd)))
	{
		height++;
		free(line);
	}
	close(fd);
	return (height);
}

int	ft_parse_map(char *filename, t_data *data)
{
	int		fd;
	int		i;
	char	*line;

	// 1. Compter les lignes
	data->map.height = get_map_height(filename);
	if (data->map.height == 0)
		return (0);
	// 2. Allouer le tableau
	data->map.grid = malloc(sizeof(char *) * (data->map.height + 1));
	if (!data->map.grid)
		return (0);
	// 3. Remplir le tableau
	fd = open(filename, O_RDONLY);
	i = 0;
	while ((line = get_next_line(fd)))
	{
		ft_remove_newline(line); // Important : on nettoie la ligne
		data->map.grid[i] = line;
		i++;
	}
	data->map.grid[i] = NULL;
	close(fd);
	// 4. Calculer la largeur (sur la 1ère ligne nettoyée)
	if (data->map.height > 0)
		data->map.width = gnl_strlen(data->map.grid[0]);
	return (1);
}

void	ft_count_items(t_data *data)
{
	int y;
	int x;

	y = 0;
	data->map.c_count = 0;
	data->map.p_count = 0;
	data->map.e_count = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (data->map.grid[y][x])
		{
			if (data->map.grid[y][x] == 'C')
				data->map.c_count++;
			else if (data->map.grid[y][x] == 'P')
				data->map.p_count++;
			else if (data->map.grid[y][x] == 'E')
			{
				data->map.e_count++;
				data->map.exit_x = x;
				data->map.exit_y = y;
			}
			x++;
		}
		y++;
	}
}