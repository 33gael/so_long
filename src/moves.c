/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 14:39:36 by gaeducas          #+#    #+#             */
/*   Updated: 2026/01/08 10:04:39 by gaeducas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	get_player_pos(t_data *data, int *x, int *y)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (j < data->map.width)
		{
			if (data->map.grid[i][j] == 'P')
			{
				*y = i;
				*x = j;
				return ;
			}
			j++;
		}
		i++;
	}
}

static int	check_move(t_data *data, int new_x, int new_y)
{
	char	next_case;

	next_case = data->map.grid[new_y][new_x];
	if (next_case == '1')
		return (0);
	if (next_case == 'E')
	{
		if (data->map.c_count == 0)
		{
			ft_printf("Congratulation ! You won in %d moves !\n", data->moves
				+ 1);
			mlx_loop_end(data->mlx);
			return (1);
		}
		return (1);
	}
	if (next_case == 'C')
	{
		data->map.c_count--;
	}
	return (1);
}

void	ft_move_player(t_data *data, int dx, int dy)
{
	int	x;
	int	y;
	int	new_x;
	int	new_y;

	get_player_pos(data, &x, &y);
	new_x = x + dx;
	new_y = y + dy;
	if (check_move(data, new_x, new_y))
	{
		if (x == data->map.exit_x && y == data->map.exit_y)
			data->map.grid[y][x] = 'E';
		else
			data->map.grid[y][x] = '0';
		data->map.grid[new_y][new_x] = 'P';
		data->moves++;
		ft_printf("Move : %d\n", data->moves);
		ft_render_map(data);
	}
}
