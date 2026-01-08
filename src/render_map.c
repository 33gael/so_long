/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:12:08 by gaeducas          #+#    #+#             */
/*   Updated: 2026/01/08 10:04:37 by gaeducas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	put_img_to_window(t_data *data, int x, int y)
{
	void	*img;

	mlx_put_image_to_window(data->mlx, data->win, data->img_floor, x * 64, y
		* 64);
	img = NULL;
	if (data->map.grid[y][x] == '1')
		img = data->img_wall;
	else if (data->map.grid[y][x] == 'C')
		img = data->img_collectible;
	else if (data->map.grid[y][x] == 'E')
		img = data->img_exit;
	else if (data->map.grid[y][x] == 'P')
		img = data->img_player;
	if (img)
		mlx_put_image_to_window(data->mlx, data->win, img, x * 64, y * 64);
}

void	ft_render_map(t_data *data)
{
	int	x;
	int	y;

	mlx_clear_window(data->mlx, data->win, (mlx_color){0});
	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			put_img_to_window(data, x, y);
			x++;
		}
		y++;
	}
}
