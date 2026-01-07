/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:11:45 by gaeducas          #+#    #+#             */
/*   Updated: 2026/01/07 16:14:57 by gaeducas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* src/map_check.c */
#include "../includes/so_long.h"

// Vérifie si la map est bien fermée par des murs '1'
static int	check_walls(t_data *data)
{
	int	i;

	// 1. Vérifier la première et la dernière ligne (Haut/Bas)
	i = 0;
	while (i < data->map.width)
	{
		if (data->map.grid[0][i] != '1' || data->map.grid[data->map.height - 1][i] != '1')
			return (0);
		i++;
	}

	// 2. Vérifier la première et la dernière colonne (Gauche/Droite)
	i = 0;
	while (i < data->map.height)
	{
		if (data->map.grid[i][0] != '1' || data->map.grid[i][data->map.width - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

// Vérifie les compteurs (1 P, 1 E, au moins 1 C)
static int	check_counts(t_data *data)
{
	if (data->map.p_count != 1)
	{
		ft_printf("Error\nThe map must contain exactly 1 Player (P).\n");
		return (0);
	}
	if (data->map.e_count != 1)
	{
		ft_printf("Error\nThe map must contain exactly 1 Exit (E).\n");
		return (0);
	}
	if (data->map.c_count < 1)
	{
		ft_printf("Error\nThe map must contain at least 1 Collectible (C).\n");
		return (0);
	}
	return (1);
}

// Fonction globale qui appelle les deux autres
int	ft_check_map_validity(t_data *data)
{
	// On vérifie d'abord les murs
	if (!check_walls(data))
	{
		ft_printf("Error\nThe map is not surrounded by walls (1).\n");
		return (0);
	}
	
	// Ensuite on vérifie le contenu (P, E, C)
	// Note : Les variables p_count/e_count sont remplies par ft_count_items
	if (!check_counts(data))
		return (0);

	return (1);
}