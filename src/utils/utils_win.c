/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_win.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 12:04:34 by gaeducas          #+#    #+#             */
/*   Updated: 2026/01/08 10:04:42 by gaeducas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

int	ft_init_window(t_data *data)
{
	mlx_window_create_info	info;
	int						img_size;

	img_size = 64;
	ft_memset(&info, 0, sizeof(mlx_window_create_info));
	data->mlx = mlx_init();
	if (!data->mlx)
		return (1);
	info.title = "So Long";
	info.width = data->map.width * img_size;
	info.height = data->map.height * img_size;
	data->win = mlx_new_window(data->mlx, &info);
	if (!data->win)
	{
		mlx_destroy_context(data->mlx);
		return (1);
	}
	return (0);
}

void	ft_start_game(t_data *data)
{
	mlx_on_event(data->mlx, data->win, MLX_KEYDOWN, key_hook, data);
	mlx_on_event(data->mlx, data->win, MLX_WINDOW_EVENT, window_hook, data);
	mlx_loop(data->mlx);
	ft_destroy_images(data);
	ft_free_map(data);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_context(data->mlx);
}

void	ft_destroy_images(t_data *data)
{
	if (data->img_wall)
		mlx_destroy_image(data->mlx, data->img_wall);
	if (data->img_floor)
		mlx_destroy_image(data->mlx, data->img_floor);
	if (data->img_player)
		mlx_destroy_image(data->mlx, data->img_player);
	if (data->img_collectible)
		mlx_destroy_image(data->mlx, data->img_collectible);
	if (data->img_exit)
		mlx_destroy_image(data->mlx, data->img_exit);
}

void	ft_free_map(t_data *data)
{
	int	i;

	if (!data->map.grid)
		return ;
	i = 0;
	while (i < data->map.height)
	{
		free(data->map.grid[i]);
		i++;
	}
	free(data->map.grid);
}
