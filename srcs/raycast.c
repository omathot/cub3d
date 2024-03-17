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
		print_point("current is ", cur_coord);
		print_point("player poss is ", player.pos);
		print_point("wall_colition ", mk_point(player.pos.x - player_offsets.x + cur_coord.x, player.pos.y - player_offsets.y - cur_coord.y));
		pause();
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

t_point	get_wall_cell_for_wall(double current_x, double current_y,
	bool x_neg, bool y_neg, double slope, double change_wall_size_look)
{
	t_point	wall_cor;

	if (fabs(slope) < 1)
	{
		if (!y_neg)
			wall_cor = mk_point(current_x, current_y - change_wall_size_look);
		else
			wall_cor = mk_point(current_x, current_y + change_wall_size_look);
	}
	else
	{
		if (!x_neg)
			wall_cor = mk_point(current_x - change_wall_size_look, current_y);
		else
			wall_cor = mk_point(current_x + change_wall_size_look, current_y);
	}
	return (wall_cor);
}

t_point	rc_get_next_y_incrementation_wall(t_ray_cast *raycast, bool x_neg, bool y_neg)
{
	double	current_x_round;
	t_point	cur_coord;
	double	past_x;
	bool	is_x_closser_to_previous_ray;

	is_x_closser_to_previous_ray = false;
	if (!y_neg)
		((*raycast).current_y) = round_clossest_half(((*raycast).current_y) + (*raycast).change_wall_size_look);
	else
		((*raycast).current_y) = -round_clossest_half(-((*raycast).current_y) + (*raycast).change_wall_size_look);
	if (fabs((*raycast).current_x) > 0.000)
	{
		if (!x_neg)
			current_x_round = round_next_clossest_half(((*raycast).current_x));
		else
			current_x_round = -round_next_clossest_half(-((*raycast).current_x));
		past_x = ((*raycast).current_x);
	}
	else
		current_x_round = 0;
	is_x_closser_to_previous_ray = false;
	((*raycast).current_x) = ((*raycast).current_y + (*raycast).player_offsets.y) / (*raycast).slope + (*raycast).player_offsets.x;
	if (!x_neg && current_x_round <= ((*raycast).current_x) && !is_double_pretty_much_zero(current_x_round - past_x))
			is_x_closser_to_previous_ray = true;
	if (x_neg && current_x_round >= ((*raycast).current_x) && !is_double_pretty_much_zero(current_x_round - past_x))
		is_x_closser_to_previous_ray = true;
	if (is_x_closser_to_previous_ray)
	{
		((*raycast).current_x) = current_x_round;
		((*raycast).current_y) = ((*raycast).current_x - (*raycast).player_offsets.x) * (*raycast).slope - (*raycast).player_offsets.y;
	}
	cur_coord = mk_point(((*raycast).current_x), ((*raycast).current_y));
	return (cur_coord);
}

t_point	rc_get_next_x_incrementation_wall(t_ray_cast *raycast, bool x_neg, bool y_neg)
{
	t_point	cur_coord;
	double	current_y_round;
	double	past_y;
	bool	is_y_closser_to_wall;

	if (!x_neg)
		((*raycast).current_x) = round_clossest_half(((*raycast).current_x) + (*raycast).change_wall_size_look);
	else
		((*raycast).current_x) = -round_clossest_half(-((*raycast).current_x) + (*raycast).change_wall_size_look);
	if (fabs((*raycast).current_y) > 0.000)
	{
		if (!y_neg)
			current_y_round = round_next_clossest_half(((*raycast).current_y));
		else
			current_y_round = -round_next_clossest_half(-((*raycast).current_y));
	}
	else
		current_y_round = 0;
	past_y = ((*raycast).current_y);
	is_y_closser_to_wall = false;
	((*raycast).current_y) = ((*raycast).current_x - (*raycast).player_offsets.x) * (*raycast).slope - (*raycast).player_offsets.y;
	if (!y_neg && current_y_round <= ((*raycast).current_y) && !is_double_pretty_much_zero(current_y_round - past_y))
			is_y_closser_to_wall = true;
	if (y_neg && current_y_round >= ((*raycast).current_y) && !is_double_pretty_much_zero(current_y_round - past_y))
			is_y_closser_to_wall = true;
	if (is_y_closser_to_wall)
	{
		((*raycast).current_y) = current_y_round;
		((*raycast).current_x) = ((*raycast).current_y + (*raycast).player_offsets.y) / (*raycast).slope + (*raycast).player_offsets.x;
	}
	cur_coord = mk_point(((*raycast).current_x), ((*raycast).current_y));
	return (cur_coord);
}



t_point	*convert_good_coordinates_wall(t_point *good_coord,
	t_player player, double cur_x, double cur_y)
{
	double	average_wall_x;
	double	average_wall_y;

	average_wall_x = cur_x + round(player.pos.x);
	average_wall_y = -cur_y + round((player.pos.y));
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

t_point	ray_cast_init(t_ray_cast *rascast, double *randiant_angle_looking, double angle, t_player player)
{
	t_point			furthest_point;
	furthest_point = mk_point((*rascast).lenght_check * sin(*randiant_angle_looking), (*rascast).lenght_check * cos(*randiant_angle_looking));

	(*randiant_angle_looking) = (angle) * (M_PI / 180);
	(*rascast).current_x = 0;
	(*rascast).current_y = 0;
	(*rascast).player_offsets = mk_point(-(round((player.pos.x)) - player.pos.x), -(round((player.pos.y)) - player.pos.y));
	(*rascast).change_wall_size_look = 0.5;
	(*rascast).good_coord = (t_point *)malloc(sizeof(t_point));
	(*rascast).slope = calculate_slope(mk_point(0, 0), furthest_point);
	(*rascast).cur_coord = mk_point(0, 0);
	(*rascast).current_y = -(*rascast).player_offsets.y;
	(*rascast).current_x = (*rascast).player_offsets.x;
	(*rascast).lenght_check = 10;
	return (furthest_point);
}

void send_ray_for_case(t_ray_cast *rascast, bool x_neg, bool y_neg)
{
    if (fabs(rascast->slope) > 1)
        rascast->cur_coord = rc_get_next_y_incrementation_wall(rascast, x_neg, y_neg);
    else
        rascast->cur_coord = rc_get_next_x_incrementation_wall(rascast, x_neg, y_neg);
}

void handle_case(t_ray_cast *rascast, bool x_neg, bool y_neg)
{
    send_ray_for_case(rascast, x_neg, y_neg);
}

void	ray_cast_x_only(t_ray_cast *rascast, t_point furthest_point)
{
	if (furthest_point.x < -0.000001)
		(*rascast).current_x = round_clossest_half((*rascast).current_x - (*rascast).change_wall_size_look);
	else
		(*rascast).current_x = round_clossest_half((*rascast).current_x + (*rascast).change_wall_size_look);
	(*rascast).cur_coord = mk_point((*rascast).current_x, (*rascast).current_y);
}

void	ray_cast_y_only(t_ray_cast *rascast, t_point furthest_point)
{
	if (furthest_point.y < -0.000001)
		(*rascast).current_y = round_clossest_half((*rascast).current_y - (*rascast).change_wall_size_look);
	else
		(*rascast).current_y = round_clossest_half((*rascast).current_y + (*rascast).change_wall_size_look);
	(*rascast).cur_coord = mk_point((*rascast).current_x, (*rascast).current_y);
}

t_point	*ray_casting_to_find_wall(char **board, t_player player, double angle)
{
	double			randiant_angle_looking;
	t_point			furthest_point;
	bool			*good;
	t_ray_cast		rascast;

	furthest_point = ray_cast_init(&rascast, &randiant_angle_looking, angle, player);
	while (furthest_point.x != floor(rascast.cur_coord.x) || furthest_point.y != floor(rascast.cur_coord.y))
	{
		if (is_double_pretty_much_zero(furthest_point.y))
			ray_cast_x_only(&rascast, furthest_point);
		else if (is_double_pretty_much_zero(furthest_point.x))
			ray_cast_y_only(&rascast, furthest_point);
		else if ((furthest_point.x > 0.000001 && furthest_point.y > 0.000001))
			handle_case(&rascast, false, false);
		else if ((furthest_point.x < -0.000001 && furthest_point.y > 0.000001))
			handle_case(&rascast, true, false);
		else if (furthest_point.x > +0.000001 && furthest_point.y < -0.000001)
			handle_case(&rascast, false, true);
		else if (furthest_point.x < -0.000001 && furthest_point.y < -0.000001)
			handle_case(&rascast, true, true);
		good = find_wall(board, rascast.cur_coord, player, rascast.player_offsets);
		if (good == NULL)
			puts("raycast out of bound 1");
		else if (*good)
			return (convert_good_coordinates_wall(rascast.good_coord, player, rascast.current_x, rascast.current_y));
	}
	return (NULL);
}

t_point	**view_walls(t_map map, int x_resolution)
{
	t_point	**all_walls;
	double	angle_drift;
	int		current_wall_index;
	double	current_angle;
	double	final_angle;
	double	number_of_found_walls;
	t_point	*current_wall;
	
	angle_drift = map.player.angle_view / x_resolution;
	current_wall_index = 0;
	current_angle = map.player.angle - (map.player.angle_view / 2);
	final_angle = map.player.angle + (map.player.angle_view / 2);
	number_of_found_walls = ceil(map.player.angle_view / angle_drift);
	all_walls = malloc(sizeof(t_point *) * (number_of_found_walls + 3));
	while (final_angle > current_angle)
	{
		current_wall = ray_casting_to_find_wall(map.board, map.player, current_angle);
		if (current_wall != NULL)
		{
			if (current_wall_index == 0)
				all_walls[current_wall_index++] = current_wall;
			else if ((*current_wall).x == (*all_walls[current_wall_index - 1]).x && (*current_wall).y == (*all_walls[current_wall_index - 1]).y)
				puts("Big problem with raycast");
			else
				all_walls[current_wall_index++] = current_wall;
		}
		current_angle = current_angle + angle_drift;
	}
	all_walls[current_wall_index] = NULL;
	return (all_walls);
}
