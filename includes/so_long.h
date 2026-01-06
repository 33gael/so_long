/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 00:43:45 by gaeducas          #+#    #+#             */
/*   Updated: 2026/01/06 13:41:34 by gaeducas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libs/MacroLibX/includes/mlx.h"
# include "../libs/ft_printf/ft_printf.h"
# include "../libs/get_next_line/get_next_line.h"
# include "../libs/libft/libft.h"
# include "../src/utils/utils.h"
# include <fcntl.h>

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		c_count;
	int		e_count;
	int		p_count;
}			t_map;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_map	map;
}			t_data;

void		key_hook(int key, void *param);
void		window_hook(int event, void *param);
int			parse_map(char *filename, t_data *data);

#endif