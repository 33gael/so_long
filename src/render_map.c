/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:12:08 by gaeducas          #+#    #+#             */
/*   Updated: 2026/01/06 15:22:14 by gaeducas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_render_map(t_data *data)
{
	int		x;
	int		y;
	void	*img;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			// On choisit quelle image afficher selon le caractère
			if (data->map.grid[y][x] == '1')
				img = data->img_wall;
			else if (data->map.grid[y][x] == 'C')
				img = data->img_collectible;
			else if (data->map.grid[y][x] == 'E')
				img = data->img_exit;
			else if (data->map.grid[y][x] == 'P')
				img = data->img_player;
			else
				img = data->img_floor;

			// On dessine (le fond d'abord, c'est mieux)
			// Astuce : dessine toujours le sol, puis l'objet par dessus si besoin
			// Mais pour commencer, ce code suffit :
			if (img)
				mlx_put_image_to_window(data->mlx, data->win, img, x * 64, y * 64);
			x++;
		}
		y++;
	}
}
