/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 15:24:42 by zaak              #+#    #+#             */
/*   Updated: 2026/01/07 15:11:12 by gaeducas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	key_hook(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	ft_printf("Pressed Key : %d\n", key);
	if (key == 41)
		mlx_loop_end(data->mlx);
	else if (key == 26)
		ft_move_player(data, 0, -1);
	else if (key == 4)
		ft_move_player(data, -1, 0);
	else if (key == 22)
		ft_move_player(data, 0, 1);
	else if (key == 7)
		ft_move_player(data, 1, 0);
}

void	window_hook(int event, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (event == 0)
		mlx_loop_end(data->mlx);
}

int	main(int argc, char **argv)
{
	t_data	data;

	data.moves = 0;
	if (argc != 2)
		return (1);
	ft_memset(&data, 0, sizeof(t_data));
	if (!ft_parse_map(argv[1], &data))
		return (1);
	if (ft_init_window(&data) != 0)
		return (1);
	ft_count_items(&data);
	ft_init_images(&data);
	ft_render_map(&data);
	ft_start_game(&data);
	return (0);
}
