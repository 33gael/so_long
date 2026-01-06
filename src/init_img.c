/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:17:10 by gaeducas          #+#    #+#             */
/*   Updated: 2026/01/06 15:41:14 by gaeducas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// Fonction pour charger une image en toute sécurité
void	*load_img(t_data *data, char *path)
{
	int		w;
	int		h;
	void	*img;

	// Avec MacroLibX, on utilise souvent mlx_png_file_to_image
	img = mlx_new_image_from_file(data->mlx, path, &w, &h);
	if (!img)
	{
		ft_printf("Error\nImpossible to load image : %s\n", path);
		// Ici, tu devrais idéalement faire une fonction de nettoyage et exit
		exit(1);
	}
	return (img);
}

void	ft_init_images(t_data *data)
{
	// Charge tes images une par une
	data->img_wall = load_img(data, "textures/wall.png");
	data->img_floor = load_img(data, "textures/floor.png");
	data->img_player = load_img(data, "textures/player.png");
	data->img_collectible = load_img(data, "textures/collectible.png");
	data->img_exit = load_img(data, "textures/exit.png");
}