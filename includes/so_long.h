/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaak <zaak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 00:43:45 by gaeducas          #+#    #+#             */
/*   Updated: 2025/12/24 17:13:33 by zaak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libs/MacroLibX/includes/mlx.h"
# include "../libs/libft/libft.h"
# include "../libs/ft_printf/ft_printf.h"
# include <fcntl.h>

typedef struct s_data
{
	mlx_context	mlx;
	mlx_window	win;
    void    *img_wall;
	char		**map;
	int width;  // Nombre de colonnes
	int height; // Nombre de lignes
	int			moves;
	// Ajoute ici tes pointeurs d'images plus tard
}				t_data;

// Prototypes
void			parse_map(t_data *data, char *map_path);

#endif
