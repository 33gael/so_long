/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaak <zaak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 15:24:42 by zaak              #+#    #+#             */
/*   Updated: 2026/01/08 20:03:25 by zaak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	ft_load_map(t_data *data, char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".ber", 4) != 0)
	{
		ft_putstr_fd("Error\nInvalid file extension (.ber)\n", 2);
		return (0);
	}
	if (!ft_parse_map(path, data))
	{
		ft_putstr_fd("Error\nImpossible to read map\n", 2);
		return (0);
	}
	ft_count_items(data);
	if (!ft_check_map_validity(data))
	{
		ft_free_map(data);
		return (0);
	}
	if (!ft_check_path_validity(data))
	{
		ft_free_map(data);
		return (0);
	}
	return (1);
}

void	key_hook(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
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

	if (argc != 2)
	{
		ft_putstr_fd("Error\nUsage: ./so_long maps/(Your map.ber)\n", 2);
		return (1);
	}
	ft_memset(&data, 0, sizeof(t_data));
	if (!ft_load_map(&data, argv[1]))
		return (1);
	if (ft_init_window(&data) != 0)
	{
		ft_free_map(&data);
		return (1);
	}
	ft_init_images(&data);
	ft_render_map(&data);
	ft_start_game(&data);
	return (0);
}
