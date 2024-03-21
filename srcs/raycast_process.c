/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samuel <samuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:33:50 by samuel            #+#    #+#             */
/*   Updated: 2024/03/21 14:35:34 by samuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	send_ray_for_case(t_ray_cast *rascast, bool x_neg, bool y_neg);
double	round_clossest_half(double number);
double	calculate_slope(t_point p1, t_point p2);
bool	*find_wall(char **board, t_point cur_coord,
			t_player player, t_point player_offsets);
t_point	*convert_coord(t_ray_cast *rascast,
			t_player player, t_point *good_coord);

void	handle_case(t_ray_cast *rascast, bool x_neg, bool y_neg)
{
	send_ray_for_case(rascast, x_neg, y_neg);
}

void	ray_cast_x_only(t_ray_cast *rascast, t_point furthest_point)
{
	if (furthest_point.x < -0.000001)
		(*rascast).current_x = round_clossest_half(
				(*rascast).current_x - (*rascast).change_wall_size_look);
	else
		(*rascast).current_x = round_clossest_half(
				(*rascast).current_x + (*rascast).change_wall_size_look);
	(*rascast).cur_coord = mk_point((*rascast).current_x, (*rascast).current_y);
}

void	ray_cast_y_only(t_ray_cast *rascast, t_point furthest_point)
{
	if (furthest_point.y < -0.000001)
		(*rascast).current_y = round_clossest_half(
				(*rascast).current_y - (*rascast).change_wall_size_look);
	else
		(*rascast).current_y = round_clossest_half(
				(*rascast).current_y + (*rascast).change_wall_size_look);
	(*rascast).cur_coord = mk_point((*rascast).current_x, (*rascast).current_y);
}

t_point	ray_cast_init(t_ray_cast *rascast,
		double *randiant_angle_looking, double angle, t_player player)
{
	t_point			furthest_point;

	(*rascast).lenght_check = 1;
	(*randiant_angle_looking) = (angle) * (M_PI / 180);
	furthest_point = mk_point((*rascast).lenght_check
			* sin(*randiant_angle_looking),
			(*rascast).lenght_check * cos(*randiant_angle_looking));
	(*rascast).current_x = 0;
	(*rascast).current_y = 0;
	(*rascast).player_offsets = mk_point(-(round((player.pos.x))
				- player.pos.x), -(round((player.pos.y)) - player.pos.y));
	(*rascast).change_wall_size_look = 0.5;
	(*rascast).good_coord = (t_point *)malloc(sizeof(t_point));
	(*rascast).slope = calculate_slope(mk_point(0, 0), furthest_point);
	(*rascast).cur_coord = mk_point(0, 0);
	(*rascast).current_y = -(*rascast).player_offsets.y;
	(*rascast).current_x = (*rascast).player_offsets.x;
	return (furthest_point);
}

t_point	*ray_casting_to_find_wall(char **board, t_player player, double angle)
{
	double			randiant_angle_looking;
	t_point			furthest;
	bool			*good;
	t_ray_cast		ray;

	furthest = ray_cast_init(&ray, &randiant_angle_looking, angle, player);
	while (furthest.x != (ray.cur_coord.x) || furthest.y != (ray.cur_coord.y))
	{
		if (is_double_pretty_much_zero(furthest.y))
			ray_cast_x_only(&ray, furthest);
		else if (is_double_pretty_much_zero(furthest.x))
			ray_cast_y_only(&ray, furthest);
		else if ((furthest.x > 0.000001 && furthest.y > 0.000001))
			handle_case(&ray, false, false);
		else if ((furthest.x < -0.000001 && furthest.y > 0.000001))
			handle_case(&ray, true, false);
		else if (furthest.x > +0.000001 && furthest.y < -0.000001)
			handle_case(&ray, false, true);
		else if (furthest.x < -0.000001 && furthest.y < -0.000001)
			handle_case(&ray, true, true);
		good = find_wall(board, ray.cur_coord, player, ray.player_offsets);
		if (*good)
			return (convert_coord(&ray, player, ray.good_coord));
	}
	return (NULL);
}
