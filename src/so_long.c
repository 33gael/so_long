/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 15:24:42 by zaak              #+#    #+#             */
/*   Updated: 2026/01/05 12:01:04 by gaeducas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	key_hook(int key, void *param)
{
	if (key == 41)
		mlx_loop_end((mlx_context)param);
}

void	window_hook(int event, void *param)
{
	if (event == 0)
		mlx_loop_end((mlx_context)param);
}

int	main(int argc, char **argv)
{
    t_data                  data;
    mlx_window_create_info  info;
	(void) argv;
	if (argc != 2)
	{
		ft_printf("Error\nUsage : ./so_long maps/(your map)");
		return (1);
	}
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
