/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 17:28:46 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/02/06 17:51:48 by oscarmathot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include "lib/libft/libft.h"
# include "lib/MLX42/include/MLX42/MLX42.h"

typedef struct s_param_mlx
{
	mlx_t *mlx;
	mlx_image_t* image_to_draw_pixel;
} t_param_mlx;

typedef struct s_point
{
	double x;
	double y;
} t_point;

typedef	struct s_stack
{
	t_point stack[1000];
	int top;
}	t_stack;

typedef struct s_vector
{
	double  angle;
	double  magnitude;
} t_vector;

typedef struct	s_file_loc
{
	char	*n_wall;
	char	*s_wall;
	char	*e_wall;
	char	*w_wall;
	char	*path;
	char	*gun;
	char	*portal1;
	char	*portal2;
	char	*nazis;
	char	*decor;
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

typedef struct	s_sprites
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
}	t_player;


typedef struct s_map
{
	mlx_t		*mlx;
	t_player	player;
	char		*map_name;
	char		**content;
	char		**board;
	int			width;			// x axis
	int			height;			// y axis
	int			size;			// x * y (may need to adjust for spaces and empty areas in map layout e.g. example.cub)
}	t_map;


void	print_map(char **map);
bool	ft_isspace(unsigned char c);
void	free_double_char(char **array);
char	*cp_until_sp(char *str, int *pos);
int		are_letters(char *str);
int		no_numbers(char *str, int *pos);
t_point	mk_point(double x, double y);
t_point	**view_walls(t_map map);
char	**debug_copy(char **board);
void	mlx_shit();


#endif