/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_walls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:31:30 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/03/18 15:47:27 by oscarmathot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_point	find_clossest_corner(t_point *wall, t_player player);
bool	double_is_zero_modular_tolerence(double number, double tolerence);

t_line	find_wall_down_corner(t_point *wall, t_player player,
	int y_resolution, int i)
{
	t_line		return_line;
	t_point		pixel_point;
	t_vector	wall_vector;
	t_point		clossest_corner;
	t_vector	corner_vector;

	wall_vector.magnitude = sqrt(pow((
					player.pos.x - wall->x), 2)
			+ pow(player.pos.y - wall->y, 2));
	wall_vector.angle = atan2((player.pos.y - wall->y),
			(player.pos.x - wall->x));
	clossest_corner = find_clossest_corner(wall, player);
	corner_vector.magnitude = sqrt(pow((player.pos.x - clossest_corner.x), 2)
			+ pow(player.pos.y - clossest_corner.y, 2));
	corner_vector.angle = atan2((player.pos.y - clossest_corner.y),
			(player.pos.x - clossest_corner.x));
	if (corner_vector.angle > (M_PI * 2))
		corner_vector.angle = corner_vector.angle - (M_PI * 2);
	pixel_point = mk_point(i, ((y_resolution / 2)
				- ((400) / ((wall_vector.magnitude + 0.5)))));
	return_line.A = pixel_point;
	return_line.B = mk_point(pixel_point.x,
			((y_resolution / 2) + ((400)
					/ ((wall_vector.magnitude + 0.5)))));
	return (return_line);
}

char	other_axis(t_param_mlx *param, t_point current)
{
	if (param->map.board[(int)round(current.y + 0.5)]
		[(int)round(current.x)] == '1')
		return ('S');
	else if (param->map.board[(int)round(current.y - 0.5)]
		[(int)round(current.x)] == '1')
		return ('N');
	else if (param->map.board[(int)round(current.y)]
		[(int)round(current.x + 0.5)] == '1')
		return ('E');
	else
		return ('W');
	return ('1');
}

char	redundancy(t_param_mlx *param, t_point current)
{
	if (param->map.board[(int)round(current.y)]
		[(int)round(current.x - 0.5)] == '1')
		return ('W');
	else if (param->map.board[(int)round(current.y + 0.5)]
		[(int)round(current.x)] == '1')
		return ('S');
	else
		return ('N');
}

char	determine_face(t_param_mlx *param, int i)
{
	t_point	current;

	current = mk_point(param->current_visible_walls[i]->x,
			param->current_visible_walls[i]->y);
	if (double_is_zero_modular_tolerence(
			param->current_visible_walls[i]->x
			- floor(param->current_visible_walls[i]->x)
			- 0.5, 0.01))
	{
		if (param->map.board[(int)round(current.y)]
			[(int)round(current.x + 0.5)] == '1')
		{
			if (param->map.board[(int)round(current.y)]
				[(int)round(current.x - 0.5)] == '1')
				return ('W');
			return ('E');
		}
		else
			return (redundancy(param, current));
	}
	else
		return (other_axis(param, current));
}

void	initialize_wall_info(t_wall_info *wall)
{
	wall->collision.x = 0;
	wall->collision.y = 0;
	wall->wall_face = 'c';
}
