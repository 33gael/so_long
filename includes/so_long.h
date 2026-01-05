/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 00:43:45 by gaeducas          #+#    #+#             */
/*   Updated: 2026/01/05 11:33:02 by gaeducas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libs/MacroLibX/includes/mlx.h"
# include "../libs/ft_printf/ft_printf.h"
# include "../libs/libft/libft.h"
# include <fcntl.h>

typedef struct s_sprite
{
	int			p_collectibles;
	int			p_player;
	int			p_exit;
}				t_sprite;

typedef struct s_data
{
	mlx_context	mlx;
	mlx_window	win;
	void		*img_wall;
	char		**map;
	int			width;
	int			height;
	int			moves;
	int			pos_x;
	int			pos_y;
}				t_data;

#endif