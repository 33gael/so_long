/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 15:24:42 by zaak              #+#    #+#             */
/*   Updated: 2026/01/06 13:52:47 by gaeducas         ###   ########.fr       */
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
	t_data	data;

	if (argc != 2)
	{
		ft_printf("Error\nUsage : ./so_long maps/map.ber");
		return (1);
	}
	ft_memset(&data, 0, sizeof(t_data));
	//Parsing (lire le fichier .ber pour remplir data.map.width/height)
	// if (!ft_parse_map(argv[1], &data))
	//     return (1);
	if (ft_init_window(&data) != 0)
	{
		ft_printf("Error\nImpossible to init the window\n");
		return (1);
	}
	ft_start_game(&data);
	return (0);
}
