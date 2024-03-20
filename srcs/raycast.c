/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:02:17 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/03/13 14:09:28 by oscarmathot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	is_out_of_bound(int x, int y, char **board)
{
	int	i;
	int	j;

	i = 0;
	while (board[i])
	{
		i++;
	}
	if (y >= i)
		return (true);
	i = 0;
	j = 0;
	while (board[y][j])
	{
		j++;
	}
	if (x >= j)
		return (true);
	return (false);
}

double	calculate_slope(t_point p1, t_point p2)
{
	return ((p2.y - p1.y) / (p2.x - p1.x));
}

double	round_clossest_half(double number);

double	round_up_pos_down_neg(double number)
{
	if (number > 0)
		return (ceil(number));
	else
		return (floor(number));
}

bool	*find_wall(char **board, t_point cur_coord,
	t_player player, t_point player_offsets)
{
	static bool	find;
	double		average_wall_x;
	double		average_wall_y;

	average_wall_x = cur_coord.x + (player.pos.x) - player_offsets.x;
	average_wall_y = -cur_coord.y + (player.pos.y) - player_offsets.y;
	find = false;
	if (cur_coord.x < -0.0)
		average_wall_x = floor(average_wall_x + 0.4995);
	if (cur_coord.y > 0.0)
		average_wall_y = floor(average_wall_y + 0.4999);
	if ((int)average_wall_y < -0.000 || (int)average_wall_x < -0.000
		|| is_out_of_bound((int)average_wall_x, (int)average_wall_y, board))
	{
		puts("looking beyound map");
		return (NULL);
	}
	if (board[(int)round(average_wall_y)][(int)round(average_wall_x)] == '1')
	{
		find = true;
		return (&find);
	}
	return (&find);
}

bool	double_is_zero_modular_tolerence(double number, double tolerence)
{
	if (fabs(number) < tolerence)
		return (true);
	return (false);
}

bool	is_double_pretty_much_zero(double number)
{
	const double	tolerence = 0.000001;

	if (fabs(number) < tolerence)
		return (true);
	return (false);
}

//ceil 0.5
double	round_next_clossest_half(double number)
{
	if (number < 0.0000)
	{
		return (0);
	}
	return (ceil((number) * 2) / 2);
}

//floor 0.5
double	round_clossest_half(double number)
{
	return (floor((number) * 2) / 2);
}

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

t_point	*convert_coord(t_ray_cast *rascast,
	t_player player, t_point *good_coord)
{
	double	average_wall_x;
	double	average_wall_y;

	average_wall_x = rascast->current_x + round(player.pos.x);
	average_wall_y = -rascast->current_y + round((player.pos.y));
	(*good_coord) = mk_point(average_wall_x, average_wall_y);
	return (good_coord);
}

bool	determine_opposite(double player_offset_x,
	double player_offset_y, t_point furthest)
{
	bool	x_opposite;
	bool	y_opposite;

	x_opposite = false;
	y_opposite = false;
	if (player_offset_x < -0.00 && furthest.x > 0.00)
	{
		x_opposite = true;
	}
	if (player_offset_x > 0.00 && furthest.x < -0.00)
	{
		x_opposite = true;
	}
	if (player_offset_y > 0.00 && furthest.y > 0.00)
	{
		y_opposite = true;
	}
	if (player_offset_y < -0.00 && furthest.y < -0.00)
	{
		y_opposite = true;
	}
	return (x_opposite && y_opposite);
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

void	send_ray_for_case(t_ray_cast *rascast, bool x_neg, bool y_neg)
{
	if (fabs(rascast->slope) > 1)
		rascast->cur_coord
			= rc_get_next_y_incrementation_wall(rascast, x_neg, y_neg);
	else
		rascast->cur_coord
			= rc_get_next_x_incrementation_wall(rascast, x_neg, y_neg);
}

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

t_point	**view_walls(t_map map, int x_resolution)
{
	t_point				**all_walls;
	t_raycast_sender	walls;

	walls.angle_drift = map.player.angle_view / x_resolution;
	walls.current_wall_index = 0;
	walls.current_angle = map.player.angle - (map.player.angle_view / 2);
	walls.final_angle = map.player.angle + (map.player.angle_view / 2);
	walls.number_of_found_walls = ceil(map.player.angle_view
			/ walls.angle_drift);
	all_walls = malloc(sizeof(t_point *) * (walls.number_of_found_walls + 3));
	while (walls.final_angle > walls.current_angle)
	{
		walls.current_wall = ray_casting_to_find_wall(
				map.board, map.player, walls.current_angle);
		if (walls.current_wall != NULL)
		{
			if (walls.current_wall_index == 0)
				all_walls[walls.current_wall_index++] = walls.current_wall;
			else
				all_walls[walls.current_wall_index++] = walls.current_wall;
		}
		walls.current_angle = walls.current_angle + walls.angle_drift;
	}
	all_walls[walls.current_wall_index] = NULL;
	return (all_walls);
}
