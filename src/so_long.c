/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 15:24:42 by zaak              #+#    #+#             */
/*   Updated: 2026/01/05 14:55:59 by gaeducas         ###   ########.fr       */
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
	(void) argv;
	if (argc != 2)
	{
		ft_printf("Error\nUsage : ./so_long maps/(your map)");
		return (1);
	}
	ft_main_utils();
}
