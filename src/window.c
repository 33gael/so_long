/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 05:01:50 by gaeducas          #+#    #+#             */
/*   Updated: 2025/12/15 12:48:46 by gaeducas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	main(void)
{
	mlx_context mlx = mlx_init();

	mlx_window_create_info info = {0};
	info.title = "Hello World!";
	info.width = 400;
	info.height = 400;
	mlx_window win = mlx_new_window(mlx, &info);
	mlx_loop(mlx);
	sleep(100);
	mlx_destroy_window(mlx, win);
    mlx_destroy_context(mlx);
}