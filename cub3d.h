/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 17:28:46 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/03/23 14:05:56 by oscarmathot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "lib/MLX42/include/MLX42/MLX42.h"
# include "lib/libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_point_int
{
	int	x;
	int	y;
}	t_point_int;

typedef struct s_texture_data
{
	double	decimal;
	int		wall_n;
}	t_texture_data;

typedef struct s_point32
{
	int32_t	x;
	int32_t	y;
}	t_point32;

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_stack
{
	t_point	stack[500];
	int		top;
}	t_stack;

typedef struct s_line
{
	t_point	a;
	t_point	b;
}	t_line;

typedef struct s_vector
{
	double	angle;
	double	magnitude;
}	t_vector;

typedef struct s_file_loc
{
	char	*n_wall;
	char	*s_wall;
	char	*e_wall;
	char	*w_wall;
}	t_file_loc;

typedef struct s_file_reqs
{
	int	no;
	int	so;
	int	we;
	int	ea;
	int	f;
	int	c;
}	t_file_reqs;

typedef struct s_xy
{
	int	x;
	int	y;
}	t_xy;

typedef struct s_sprites
{
	mlx_image_t	*n_wall;
	mlx_image_t	*s_wall;
	mlx_image_t	*e_wall;
	mlx_image_t	*w_wall;
}	t_sprites;

typedef struct s_player
{
	t_point	pos;
	double	angle;
	double	angle_view;
}	t_player;

typedef struct s_rgba
{
	int	r;
	int	g;
	int	b;
}	t_rgba;

typedef struct s_map
{
	mlx_t			*mlx;
	t_player		player;
	char			*map_name;
	char			**content;
	char			**board;
	char			**file_data;
	mlx_texture_t	*wall_n;
	mlx_texture_t	*wall_s;
	mlx_texture_t	*wall_e;
	mlx_texture_t	*wall_w;
	int				width;
	int				height;
	t_rgba			*floor_rgb;
	t_rgba			*ceil_rgb;
	int				size;
}	t_map;

typedef struct s_param_mlx
{
	mlx_t				*mlx;
	mlx_win_cursor_t	*cursor;
	mlx_image_t			*image_to_draw_pixel;
	t_point				**current_visible_walls;
	t_map				map;
	int					x_resolution;
	int					y_resolution;
}	t_param_mlx;

typedef struct s_wall_info
{
	t_point	collision;
	char	wall_face;
}	t_wall_info;

typedef struct s_texture_vars
{
	t_texture_data	normalized;
	mlx_image_t		*to_place;
	u_int32_t		color;
	int				texture_x;
	double			start_y;
	int				y_diff;
	int				end_y;
	int				screen_height;
	double			corrected_height;
	int				size;
	double			magnitude;
	int				texture_y;
	int				cur_screen_x;
}	t_texture_vars;

typedef struct s_ray_cast
{
	double	current_x;
	double	current_y;
	t_point	player_offsets;
	double	change_wall_size_look;
	t_point	*good_coord;
	double	slope;
	t_point	cur_coord;
	double	lenght_check;

}	t_ray_cast;

typedef struct s_raycast_sender
{
	double	angle_drift;
	int		current_wall_index;
	double	current_angle;
	double	final_angle;
	double	nb_walls;
	t_point	*current_wall;
}	t_raycast_sender;

void		print_map(char **map);
bool		ft_isspace(unsigned char c);
void		free_double_char(char **array);
int			are_letters(char *str);
int			no_numbers(char *str, int *pos);
t_point		mk_point(double x, double y);
t_point		**view_walls(t_map map, int x_resolution);
char		**debug_copy(char **board);
void		mlx_shit(t_map *map);
void		print_point(char *start_message, t_point point);
t_point_int	mk_point_int(int x, int y);
bool		double_is_zero_modular_tolerence(double number, double tolerence);
bool		is_double_pretty_much_zero(double number);
void		free_map(t_map *map);

#endif
