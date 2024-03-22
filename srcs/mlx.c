/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omathot <omathot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:48:24 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/03/22 08:48:26 by omathot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_visible_walls(t_point **walls);
void	player_move(void *param);
double	find_distance(t_point a, t_point b);
double	radiant_to_dregre_angle(double angle);
char	*get_data_line(t_param_mlx *param, char x);
void	handle_mouse(t_param_mlx *mlx);
bool	double_is_zero_modular_tolerence(double number, double tolerence);
bool	is_double_pretty_much_zero(double number);
void	save_file_data(t_param_mlx *param);
bool	are_double_in_screen(double x, double y, t_param_mlx *param_real);
void	print_all_walls(t_param_mlx *param_real);
t_stack	*init_stack(void);
void	print_point(char *start_message, t_point point);
void	wall_texture(t_param_mlx *param, int screen_x,
			t_wall_info wall, double wall_height);

t_point	find_clossest_corner(t_point *wall, t_player player)
{
	t_point	clossest_corner;
	double	delta_y;
	double	delta_x;

	delta_y = wall->y - player.pos.y;
	delta_x = wall->x - player.pos.x;
	if (delta_x > 0)
		clossest_corner.x = wall->x + 0.5;
	else
		clossest_corner.x = wall->x - 0.5;
	if (delta_y > 0)
		clossest_corner.y = wall->y + 0.5;
	else
		clossest_corner.y = wall->y - 0.5;
	return (clossest_corner);
}

bool	is_double_round(double i)
{
	return (double_is_zero_modular_tolerence(i - round(i), 0.1));
}

uint32_t	get_collor(int r, int g, int b, int a)
{
	uint32_t	final;

	final = ((uint32_t)r << 24) | ((uint32_t)g << 16)
		| ((uint32_t)b << 8) | (uint32_t)a;
	return (final);
}

void	update_current_wall(t_point ***walls, t_map map, double x_resolution)
{
	free_visible_walls((*walls));
	(*walls) = view_walls(map, x_resolution);
	return ;
}

void	mlx_shit(t_map *map)
{
	t_param_mlx	*param_mlx;
	mlx_t		*mlx;

	param_mlx = malloc(sizeof(t_param_mlx));
	param_mlx->current_visible_walls = view_walls((*map), 1080);
	param_mlx->x_resolution = 1080;
	param_mlx->y_resolution = 720;
	param_mlx->map = (*map);
	save_file_data(param_mlx);
	mlx = mlx_init(1080, 720, "main_window", false);
	param_mlx->image_to_draw_pixel = mlx_new_image(
			mlx, param_mlx->x_resolution, param_mlx->y_resolution);
	if (!mlx)
		exit(1);
	param_mlx->mlx = mlx;
	mlx_loop_hook(mlx, player_move, param_mlx);
	handle_mouse(param_mlx);
	mlx_loop(mlx);
	free_map(map);
	mlx_terminate(mlx);
	free_visible_walls(param_mlx->current_visible_walls);
	if (param_mlx->map.wall_e)
		free(param_mlx->map.wall_e);
	if (param_mlx->map.wall_w)
		free(param_mlx->map.wall_w);
	if (param_mlx->map.wall_s)
		free(param_mlx->map.wall_s);
	if (param_mlx->map.wall_n)
		free(param_mlx->map.wall_n);
	free(param_mlx);
}
