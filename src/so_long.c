/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 15:24:42 by zaak              #+#    #+#             */
/*   Updated: 2026/01/07 11:11:11 by gaeducas         ###   ########.fr       */
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
		return (1);
	ft_memset(&data, 0, sizeof(t_data));
	if (!ft_parse_map(argv[1], &data))
		return (1);
	if (ft_init_window(&data) != 0)
		return (1);
	ft_init_images(&data);
	ft_render_map(&data);
	ft_start_game(&data);
	return (0);
}

