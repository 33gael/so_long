/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaak <zaak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 05:01:50 by gaeducas          #+#    #+#             */
/*   Updated: 2025/12/24 17:23:39 by zaak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// void	key_hook(int key, void *param)
// {
// 	if (key == 41)
// 		mlx_loop_end((mlx_context)param);
// }

// void	window_hook(int event, void *param)
// {
// 	if (event == 0)
// 		mlx_loop_end((mlx_context)param);
// }

// int	main(void)
// {
// 	mlx_context				mlx;
// 	mlx_window_create_info	info;
// 	mlx_window				win;

// 	mlx = mlx_init();
// 	info.title = "Hello World!";
// 	info.width = 1080;
// 	info.height = 860;
// 	win = mlx_new_window(mlx, &info);
// 	mlx_on_event(mlx, win, MLX_KEYDOWN, key_hook, mlx);
// 	mlx_on_event(mlx, win, MLX_WINDOW_EVENT, window_hook, mlx);
// 	mlx_loop(mlx);
// 	mlx_destroy_window(mlx, win);
// 	mlx_destroy_context(mlx);
// }

void    render_map(t_data *data)
{
    int x;
    int y;

    y = 0;
    while (data->map[y])
    {
        x = 0;
        while (data->map[y][x])
        {
            if (data->map[y][x] == '1')
                mlx_put_image_to_window(data->mlx, data->win, data->img_wall, x * 32, y * 32);
            // ... etc pour 'P', 'C', 'E', '0'
            x++;
        }
        y++;
    }
}
