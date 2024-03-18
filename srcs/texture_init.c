/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:40:05 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/03/18 16:20:59 by oscarmathot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_texture_data	normalize_collision_point(t_point collision_point, bool side)
{
	t_texture_data	data;

	if (!side)
	{
		data.wall_n = round(collision_point.x - 0.5);
		data.decimal = (collision_point.x - data.wall_n);
	}
	else
	{
		data.wall_n = round(collision_point.y - 0.5);
		data.decimal = (collision_point.y - data.wall_n);
	}
	return (data);
}

void	initialize_tex_variables(t_texture_vars *vars, int cur_x)
{
	vars->to_place = NULL;
	vars->screen_height = 720;
	vars->magnitude = 0;
	vars->texture_x = 0;
	vars->start_y = 0;
	vars->end_y = 0;
	vars->y_diff = 0;
	vars->texture_y = 0;
	vars->color = 0;
	vars->size = 0;
	vars->corrected_height = 0;
	vars->cur_screen_x = cur_x;
}

void	initialize_rgba(t_rgba *rgba)
{
	rgba->r = 0;
	rgba->b = 0;
	rgba->g = 0;
}

void	determine_texture(t_texture_vars *variables,
	t_wall_info wall, t_param_mlx *param)
{
	if (wall.wall_face == 'N')
		(*variables).to_place = mlx_texture_to_image(
				param->mlx, param->map.wall_N);
	else if (wall.wall_face == 'S')
		(*variables).to_place = mlx_texture_to_image(
				param->mlx, param->map.wall_S);
	else if (wall.wall_face == 'E')
		(*variables).to_place = mlx_texture_to_image(
				param->mlx, param->map.wall_E);
	else if (wall.wall_face == 'W')
		(*variables).to_place = mlx_texture_to_image(
				param->mlx, param->map.wall_W);
	(*variables).size = (variables->to_place->height
			* variables->to_place->width) - 1;
}

void	clamp_xy(t_texture_vars *variables,
	double wall_height, t_param_mlx *param, t_wall_info wall)
{
	(*variables).magnitude = sqrt(pow((param->map.player.pos.x
					- wall.collision.x), 2) + pow(
				param->map.player.pos.y - wall.collision.y, 2));
	(*variables).normalized = normalize_collision_point(wall.collision,
			wall.wall_face == 'E' || wall.wall_face == 'W');
	(*variables).texture_x = (int)(variables->normalized.decimal
			* variables->to_place->width);
	(*variables).start_y = ((double)param->y_resolution / 2)
		- (wall_height / variables->magnitude);
	if ((*variables).start_y < 0)
		(*variables).start_y = 0;
	(*variables).end_y = ((double)param->y_resolution / 2)
		+ (wall_height / variables->corrected_height);
	if (variables->end_y > variables->screen_height)
		(*variables).end_y = variables->screen_height;
	if (variables->texture_x < 0)
		(*variables).texture_x = 0;
	else if (variables->texture_x >= (int)variables->to_place->width)
		(*variables).texture_x = variables->to_place->width - 1;
	(*variables).y_diff = fabs(variables->start_y - variables->end_y) - 1;
}
