/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaeducas <gaeducas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 00:43:45 by gaeducas          #+#    #+#             */
/*   Updated: 2026/01/09 15:32:17 by gaeducas         ###   ########.fr       */
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

# define MAX_WIDTH 30
# define MAX_HEIGHT 16

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		c_count;
	int		e_count;
	int		p_count;
	int		exit_x;
	int		exit_y;
}			t_map;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img_wall;
	void	*img_floor;
	void	*img_player;
	void	*img_exit;
	void	*img_collectible;
	int		moves;
	t_map	map;
}			t_data;

void		key_hook(int key, void *param);
void		window_hook(int event, void *param);
int			ft_parse_map(char *filename, t_data *data);
void		ft_render_map(t_data *data);
void		ft_start_game(t_data *data);
int			ft_init_window(t_data *data);
void		*load_img(t_data *data, char *path);
void		ft_init_images(t_data *data);
void		ft_count_items(t_data *data);
void		ft_move_player(t_data *data, int dx, int dy);
void		ft_destroy_images(t_data *data);
void		ft_free_map(t_data *data);
int			ft_check_map_validity(t_data *data);
int			ft_check_path_validity(t_data *data);
int			ft_check_chars_validity(t_data *data);

#endif