/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_win.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 12:04:34 by gaeducas          #+#    #+#             */
/*   Updated: 2026/01/05 15:20:19 by gaeducas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

int	ft_main_utils(void)
{
	t_data					data;
	mlx_window_create_info	info;

	ft_memset(&info, 0, sizeof(mlx_window_create_info));
	ft_memset(&data, 0, sizeof(t_data));
	data.mlx = mlx_init();
	if (!data.mlx)
		return (1);
	info.title = "So Long";
	info.width = 400;
	info.height = 300;
	data.win = mlx_new_window(data.mlx, &info);
	if (!data.win)
	{
		mlx_destroy_context(data.mlx);
		return (1);
	}
	mlx_on_event(data.mlx, data.win, MLX_KEYDOWN, key_hook, data.mlx);
	mlx_on_event(data.mlx, data.win, MLX_WINDOW_EVENT, window_hook, data.mlx);
	mlx_loop(data.mlx);
	mlx_destroy_window(data.mlx, data.win);
	mlx_destroy_context(data.mlx);
	return (0);
}
