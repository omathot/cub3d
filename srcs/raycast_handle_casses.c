/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_handle_casses.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samuel <samuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:34:32 by samuel            #+#    #+#             */
/*   Updated: 2024/03/21 14:35:20 by samuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	round_next_clossest_half(double number);
double	round_clossest_half(double number);

void	rc_get_next_y_incre_wall_init(t_ray_cast *raycast,
		double *current_x_round, bool x_neg, bool y_neg)
{
	if (!y_neg)
		((*raycast).current_y) = round_clossest_half(
				((*raycast).current_y) + (*raycast).change_wall_size_look);
	else
		((*raycast).current_y) = -round_clossest_half(
				-((*raycast).current_y) + (*raycast).change_wall_size_look);
	if (fabs((*raycast).current_x) > 0.000)
	{
		if (!x_neg)
			(*current_x_round) = round_next_clossest_half((*raycast).current_x);
		else
			(*current_x_round) = -round_next_clossest_half(
					-(*raycast).current_x);
	}
	else
		(*current_x_round) = 0;
}

t_point	rc_get_next_y_incrementation_wall(t_ray_cast *raycast,
		bool x_neg, bool y_neg)
{
	double	current_x_round;
	t_point	cur_coord;
	double	past_x;
	bool	is_x_closser_to_previous_ray;

	rc_get_next_y_incre_wall_init(raycast, &current_x_round, x_neg, y_neg);
	past_x = ((*raycast).current_x);
	is_x_closser_to_previous_ray = false;
	((*raycast).current_x) = ((*raycast).current_y + (*raycast)
			.player_offsets.y) / (*raycast).slope + (*raycast).player_offsets.x;
	if (!x_neg && current_x_round <= ((*raycast).current_x)
		&& !is_double_pretty_much_zero(current_x_round - past_x))
		is_x_closser_to_previous_ray = true;
	if (x_neg && current_x_round >= ((*raycast).current_x)
		&& !is_double_pretty_much_zero(current_x_round - past_x))
		is_x_closser_to_previous_ray = true;
	if (is_x_closser_to_previous_ray)
	{
		((*raycast).current_x) = current_x_round;
		((*raycast).current_y) = ((*raycast).current_x
				- (*raycast).player_offsets.x)
			* (*raycast).slope - (*raycast).player_offsets.y;
	}
	cur_coord = mk_point(((*raycast).current_x), ((*raycast).current_y));
	return (cur_coord);
}

void	rc_get_next_x_incre_wall_init(t_ray_cast *raycast,
		double *current_y_round, bool x_neg, bool y_neg)
{
	if (!x_neg)
		((*raycast).current_x) = round_clossest_half(
				((*raycast).current_x) + (*raycast).change_wall_size_look);
	else
		((*raycast).current_x) = -round_clossest_half(
				-((*raycast).current_x) + (*raycast).change_wall_size_look);
	if (fabs((*raycast).current_y) > 0.000)
	{
		if (!y_neg)
			(*current_y_round) = round_next_clossest_half((*raycast).current_y);
		else
			(*current_y_round) = -round_next_clossest_half(
					-(*raycast).current_y);
	}
	else
		(*current_y_round) = 0;
}

t_point	rc_get_next_x_incrementation_wall(
		t_ray_cast *raycast, bool x_neg, bool y_neg)
{
	t_point	cur_coord;
	double	current_y_round;
	double	past_y;
	bool	is_y_closser_to_wall;

	rc_get_next_x_incre_wall_init(raycast, &current_y_round, x_neg, y_neg);
	past_y = ((*raycast).current_y);
	is_y_closser_to_wall = false;
	((*raycast).current_y) = ((*raycast).current_x - (*raycast)
			.player_offsets.x) * (*raycast).slope - (*raycast).player_offsets.y;
	if (!y_neg && current_y_round <= ((*raycast).current_y)
		&& !is_double_pretty_much_zero(current_y_round - past_y))
		is_y_closser_to_wall = true;
	if (y_neg && current_y_round >= ((*raycast).current_y)
		&& !is_double_pretty_much_zero(current_y_round - past_y))
		is_y_closser_to_wall = true;
	if (is_y_closser_to_wall)
	{
		((*raycast).current_y) = current_y_round;
		((*raycast).current_x) = ((*raycast).current_y
				+ (*raycast).player_offsets.y)
			/ (*raycast).slope + (*raycast).player_offsets.x;
	}
	cur_coord = mk_point(((*raycast).current_x), ((*raycast).current_y));
	return (cur_coord);
}

void	send_ray_for_case(t_ray_cast *rascast, bool x_neg, bool y_neg)
{
	if (fabs(rascast->slope) > 1)
		rascast->cur_coord
			= rc_get_next_y_incrementation_wall(rascast, x_neg, y_neg);
	else
		rascast->cur_coord
			= rc_get_next_x_incrementation_wall(rascast, x_neg, y_neg);
}
