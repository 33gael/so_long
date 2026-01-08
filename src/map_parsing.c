/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaak <zaak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 11:02:49 by gaeducas          #+#    #+#             */
/*   Updated: 2026/01/08 19:56:53 by zaak             ###   ########.fr       */
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
	line = get_next_line(fd);
	while (line)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

int	ft_parse_map(char *filename, t_data *data)
{
	int		fd;
	int		i;
	char	*line;

	data->map.height = get_map_height(filename);
	if (data->map.height == 0)
		return (0);
	data->map.grid = malloc(sizeof(char *) * (data->map.height + 1));
	if (!data->map.grid)
		return (0);
	fd = open(filename, O_RDONLY);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		ft_remove_newline(line);
		data->map.grid[i++] = line;
		line = get_next_line(fd);
	}
	data->map.grid[i] = NULL;
	close(fd);
	data->map.width = gnl_strlen(data->map.grid[0]);
	return (1);
}

static void	check_cell(t_data *data, int y, int x)
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
}

void	ft_count_items(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	data->map.c_count = 0;
	data->map.p_count = 0;
	data->map.e_count = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (data->map.grid[y][x])
		{
			check_cell(data, y, x);
			x++;
		}
		y++;
	}
}
