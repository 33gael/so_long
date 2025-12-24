/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaak <zaak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 15:24:42 by zaak              #+#    #+#             */
/*   Updated: 2025/12/24 17:37:50 by zaak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// Fonction ajoutée pour éviter l'erreur "undefined reference"
void	parse_map(t_data *data, char *map_path)
{
	(void)map_path;
	// Pour l'instant on met des valeurs manuelles pour tester la fenêtre
	data->width = 15;
	data->height = 10;
	data->map = NULL;
	// Tu devras coder le vrai parsing ici plus tard !
}

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
	t_data					data;
	mlx_window_create_info	info;

	if (argc != 2)
	{
		ft_printf("Error\nUsage: ./so_long maps/map.ber\n");
		return (1);
	}
	ft_memset(&data, 0, sizeof(t_data));
	// Maintenant cette fonction existe (voir plus haut)
	parse_map(&data, argv[1]);
	data.mlx = mlx_init();
	info.title = "so_long";
	info.width = data.width * 32;
	info.height = data.height * 32;
	data.win = mlx_new_window(data.mlx, &info);
	mlx_on_event(data.mlx, data.win, MLX_KEYDOWN, key_hook, data.mlx);
	mlx_on_event(data.mlx, data.win, MLX_WINDOW_EVENT, window_hook, data.mlx);
	mlx_loop(data.mlx);
	mlx_destroy_window(data.mlx, data.win);
	mlx_destroy_context(data.mlx);
}
