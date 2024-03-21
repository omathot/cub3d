/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:08:47 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/03/18 15:45:00 by oscarmathot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	update_current_wall(t_point ***walls, t_map map, double x_resolution);

int	search_board_walls(char **board, t_point furthest_point)
{
	t_point	wall_coord;

	if (furthest_point.y < -0)
		wall_coord = mk_point(0, furthest_point.y);
	else
		wall_coord = mk_point(0, furthest_point.y);
	if (furthest_point.x < -0)
		wall_coord.x = furthest_point.x;
	else
		wall_coord.x = furthest_point.x;
	if (board[(int)wall_coord.y][(int)wall_coord.x] == '1')
		return (1);
	return (0);
}

int	cast_ray(char **board, t_point *player, int angle)
{
	double	radian;
	double	delta_x;
	double	delta_y;
	t_point	save_furthest_point;
	t_point	furthest_point;

	radian = (angle * (M_PI / 180));
	delta_x = sin(radian) / 1.5;
	delta_y = -cos(radian) / 1.5;
	save_furthest_point = mk_point(delta_x
			+ (player->x), delta_y + (player->y));
	furthest_point = mk_point(delta_x + (player->x), delta_y + (player->y));
	if (delta_x < -0.0)
		furthest_point.x = floor(furthest_point.x + 0.4999);
	else
		furthest_point.x = round(furthest_point.x);
	if (delta_y < -0.0)
		furthest_point.y = floor(furthest_point.y + 0.4999);
	else
		furthest_point.y = round(furthest_point.y);
	if (fabs(furthest_point.x - save_furthest_point.x) < 0.5
		|| fabs(furthest_point.y - save_furthest_point.y) < 0.5)
		if (search_board_walls(board, furthest_point) == 1)
			return (1);
	return (0);
}

void	move_forward(t_param_mlx *param, float angle_radians, float move_speed)
{
	if (!cast_ray(param->map.board, &param->map.player.pos,
			param->map.player.angle))
	{
		param->map.player.pos.x += sin(angle_radians) * move_speed;
		param->map.player.pos.y -= cos(angle_radians) * move_speed;
		update_current_wall(&param->current_visible_walls,
			param->map, param->x_resolution);
	}
}

void	move_backwards(t_param_mlx *param,
	float angle_radians, float move_speed)
{
	int	coll_angle;

	coll_angle = (int)(param->map.player.angle + 180) % 360;
	if (!cast_ray(param->map.board,
			&param->map.player.pos, coll_angle))
	{
		param->map.player.pos.x -= sin(angle_radians) * move_speed;
		param->map.player.pos.y += cos(angle_radians) * move_speed;
		update_current_wall(&param->current_visible_walls,
			param->map, param->x_resolution);
	}
}
