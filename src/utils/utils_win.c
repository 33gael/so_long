/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_win.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 12:04:34 by gaeducas          #+#    #+#             */
/*   Updated: 2026/01/06 13:56:00 by gaeducas         ###   ########.fr       */
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
	mlx_on_event(data->mlx, data->win, MLX_KEYDOWN, key_hook, data->mlx);
	mlx_on_event(data->mlx, data->win, MLX_WINDOW_EVENT, window_hook,
		data->mlx);
	mlx_loop(data->mlx);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_context(data->mlx);
}