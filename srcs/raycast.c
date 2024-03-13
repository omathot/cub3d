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
	int i;

  i = 0;
  while (board[i]) {
    i++;
  }
  if (y < i)
    return (false);
  int j;
  i = 0;
  while (board[i]) {
    j = 0;
    while (board[i][j]) {
      j++;
    }
    if (i == y)
      if (j <= x)
        return (false);
    i++;
  }
  return (true);
}

double calculate_slope(t_point p1, t_point p2) {
	return (p2.y - p1.y) / (p2.x - p1.x);
}

double	round_clossest_half(double number);

double	round_up_pos_down_neg(double number)
{
	if (number > 0)
		return (ceil(number));
	else
		return (floor(number));
}

bool	*find_wall(char **board, t_point cur_coord, t_player player)
{
	static bool	find;
	find = false;
	// if (cur_coord.x < 0.5)
	// 	cur_coord.x -= player_offset_x;
	// if (cur_coord.y < 0.5)
	// 	cur_coord.y -= player_offset_y;
	double average_wall_x = cur_coord.x + round(player.pos.x);
	double average_wall_y = -cur_coord.y + round(player.pos.y);
	if ((int)average_wall_y < -0.000 || (int)average_wall_x < -0.000)
	{
		puts("found wall at neg values");
		// print_point("average_wall_x kill at is", mk_point(average_wall_x, average_wall_y));
		pause();
		return (NULL);
	}
	if (is_out_of_bound((int)average_wall_x, (int)average_wall_y, board))
	{
		puts("looking beyound map");
		// print_point("cur coord", cur_coord);
		// print_point("player pos", player.pos);
		return (NULL);
	}
	if (board[(int)average_wall_y][(int)average_wall_x] == '\0')
	{
		puts("fazed out bro");
		return (NULL);
	}

	// double average_wall_x_low = cur_coord.x + floor(player.pos.x);
	// double average_wall_y_low = -cur_coord.y + floor((player.pos.y));
	// double average_wall_x_high = cur_coord.x + ceil(player.pos.x);
	// double average_wall_y_high = -cur_coord.y + ceil((player.pos.y));
	// if (is_double_pretty_much_zero(cur_coord.y))
	// {

	// }
	// else if (cur_coord.y < -0)
	// 	average_wall_y = average_wall_y_low;
	// else
	// 	average_wall_y = average_wall_y_high;
	// if (is_double_pretty_much_zero(cur_coord.x))
	// {

	// }
	if (cur_coord.x < -0.0)
	{
		average_wall_x = floor(average_wall_x + 0.48);
		// puts("x neg");
	}
	if (cur_coord.y > -0.0)
	{
		average_wall_y = floor(average_wall_y + 0.48);
		// puts("y neg");
	}
	// if (cur_coord.y > 0.000)
	// 	average_wall_y = round(average_wall_y - 0.00001);
	// else
	// 	average_wall_y = floor(average_wall_y);
	// if (cur_coord.x > 0.000)
	// 	average_wall_x = ceil(average_wall_x);
	// else
	// 	average_wall_x = floor(average_wall_x);


	if (board[(int)round(average_wall_y)][(int)round(average_wall_x)] == '1')
	{
		// if (round(average_wall_y) - average_wall_y - 0.5 > 0.00)
		// 	return (&find);
		// if (round(average_wall_y) - average_wall_y - 0.5 > 0.00)
		// 	return (&find);
		// *good_coord = mk_point((cur_coord.x + player.pos.x), (-cur_coord.y + player.pos.y)); 
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

t_point	get_wall_cell_for_wall(double current_x, double current_y, bool x_neg, bool y_neg, double slope, double change_wall_size_look)
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

t_point	rc_get_next_y_incrementation_wall(double *current_x, double *current_y, double slope, double change_wall_size_look, bool x_neg, bool y_neg, double player_offset_x, double player_offset_y)
{
	double	current_x_round;
	t_point	cur_coord;


	if (!y_neg)
	{
		(*current_y) = round_clossest_half((*current_y) + change_wall_size_look);

	}
	else
	{
		(*current_y) = -round_clossest_half(-(*current_y) + change_wall_size_look);
	}
	if (fabs(*current_x) > 0.000)
	{
		if (!x_neg)
		{
			current_x_round = round_next_clossest_half((*current_x));
		}
		else
		{
			current_x_round = -round_next_clossest_half(-(*current_x));
		}
	}
	else
		current_x_round = 0;
	double past_x = (*current_x);
	bool	is_x_closser_to_previous_ray = false;
	// (*current_x) = (*current_y) / slope;
	(*current_x) = (*current_y + player_offset_y) / slope + player_offset_x;
	if (!x_neg)
	{
		if (current_x_round <= (*current_x) && !is_double_pretty_much_zero(current_x_round - past_x))
			is_x_closser_to_previous_ray = true;
	}
	else
	{
		if (current_x_round >= (*current_x) && !is_double_pretty_much_zero(current_x_round - past_x))
			is_x_closser_to_previous_ray = true;
	}
	if (is_x_closser_to_previous_ray)
	{
		(*current_x) = current_x_round;
		// (*current_y) = (*current_x) * slope;
		(*current_y) = (*current_x - player_offset_x) * slope - player_offset_y;
	// 	if (!y_neg)
	// 	{
	// 		// cur_coord = mk_point((*current_x) - change_wall_size_look, (*current_y));
	// // 		cur_coord = mk_point((*current_x), (*current_y) + change_wall_size_look);
	// 		cur_coord = mk_point((*current_x), (*current_y));
	// 	}
	// 	else
	// 	{
	// 		// cur_coord = mk_point((*current_x) + change_wall_size_look, (*current_y));
	// 		cur_coord = mk_point((*current_x), (*current_y) - change_wall_size_look);
	// 	}
	}
	// else
	// {
	// 	if (!x_neg)
	// 	{
	// 		cur_coord = mk_point((*current_x), (*current_y));
	// // 		cur_coord = mk_point((*current_x) - change_wall_size_look, (*current_y));
	// 	}
	// 	else
	// 	{
	// 		// cur_coord = mk_point((*current_x), (*current_y));
	// 		cur_coord = mk_point((*current_x) + change_wall_size_look, (*current_y));
	// 	}
	// }
	cur_coord = mk_point((*current_x), (*current_y));

	// cur_coord = get_wall_cell_for_wall((*current_x), (*current_y), x_neg, y_neg, slope, change_wall_size_look);

	return (cur_coord);
}

t_point	rc_get_next_x_incrementation_wall(double *current_x, double *current_y, double slope, double change_wall_size_look, bool x_neg, bool y_neg, double player_offset_x, double player_offset_y)
{
	t_point	cur_coord;
	double	current_y_round;
	if (!x_neg)
	{
		(*current_x) = round_clossest_half((*current_x) + change_wall_size_look);
	}
	else
	{
		(*current_x) = -round_clossest_half(-(*current_x) + change_wall_size_look);
	}
	if (fabs(*current_y) > 0.000)
	{
		if (!y_neg)
		{
			current_y_round = round_next_clossest_half((*current_y));
		}
		else
		{
			current_y_round = -round_next_clossest_half(-(*current_y));
		}
		// if (!y_neg)
		// {
		// 	current_y_round = round_clossest_half((*current_y));
		// }
		// else
		// {
		// 	current_y_round = -round_clossest_half(-(*current_y));
		// }
	}
	else
		current_y_round = 0;
	double past_y = (*current_y);

	bool	is_y_closser_to_wall = false;
	// (*current_y) = (*current_x) * slope;
	(*current_y) = (*current_x - player_offset_x) * slope - player_offset_y;
	if (!y_neg)
	{
		if (current_y_round <= (*current_y) && current_y_round != 0 && !is_double_pretty_much_zero(current_y_round - past_y))
			is_y_closser_to_wall = true;
	}
	else
	{
		if (current_y_round >= (*current_y) && current_y_round != 0 && !is_double_pretty_much_zero(current_y_round - past_y))
			is_y_closser_to_wall = true;
	}
	if (is_y_closser_to_wall)
	{
		(*current_y) = current_y_round;
		// (*current_x) = (*current_y) / slope;
		(*current_x) = (*current_y + player_offset_y) / slope + player_offset_x;
		// if (!x_neg)
		// {
		// 	cur_coord = mk_point((*current_x), (*current_y));
		// 	// cur_coord = mk_point((*current_x) - change_wall_size_look, (*current_y));
		// }
		// else
		// {
		// 	// cur_coord = mk_point((*current_x), (*current_y));
		// 	cur_coord = mk_point((*current_x) + change_wall_size_look, (*current_y));
		// }
	}
	// else
	// {
	// 	if (!y_neg)
	// 	{
	// 		cur_coord = mk_point((*current_x), (*current_y));
	// 		// cur_coord = mk_point((*current_x), (*current_y) - change_wall_size_look);
	// 	}
	// 	else
	// 	{
	// 		// cur_coord = mk_point((*current_x), (*current_y));
	// 		cur_coord = mk_point((*current_x), (*current_y) - change_wall_size_look);
	// 	}
	// }
	cur_coord = mk_point((*current_x), (*current_y));
	// cur_coord = get_wall_cell_for_wall((*current_x), (*current_y), x_neg, y_neg, slope, change_wall_size_look);
	return (cur_coord);
}

t_point	*convert_good_coordinates_wall(t_point *good_coord, t_player player, double cur_x, double cur_y)
{
	double average_wall_x = cur_x + round(player.pos.x);// - fabs(player_offset_x);
	double average_wall_y = -cur_y + round((player.pos.y));// - fabs(player_offset_x);
	(*good_coord) = mk_point(average_wall_x, average_wall_y);
	// (*good_coord) = mk_point((cur_x), (-cur_y));
	return (good_coord);
}

t_point *ray_casting_to_find_wall(char **board, t_player player, double angle)
{
	int lenght_check = 10;
	double  randiant_angle_looking = (angle) * (M_PI / 180);


	// t_vector    direction_ray;
	// direction_ray.magnitude = lenght_check;
	// direction_ray.angle = angle;
	t_point furthest_point = mk_point(lenght_check * sin(randiant_angle_looking), lenght_check * cos(randiant_angle_looking));
	double current_x = 0;
	double current_y = 0;
	// double	player_offset_x = -(round((player.pos.x * 2) / 2)- player.pos.x);
	// double	player_offset_y = (round(-(player.pos.y * 2) / 2) + player.pos.y);
	double	player_offset_x = -(round((player.pos.x))- player.pos.x);
	double	player_offset_y = (-round((player.pos.y)) + player.pos.y);
	
	
	if (is_double_pretty_much_zero(player_offset_x))
		player_offset_x = 0;
	if (is_double_pretty_much_zero(player_offset_y))
		player_offset_y = 0;
	t_point cur_coord;
	// double	delta_x = sin((direction_ray.angle) * (M_PI / 180)) / 2;
	// double	delta_y = cos((direction_ray.angle) * (M_PI / 180)) / 2;
	double	change_wall_size_look = 0.5;
	t_point *good_coord = (t_point *)malloc(sizeof(t_point));
	bool *good;
	double	slope = calculate_slope(mk_point(0,0), furthest_point);
	// t_orientation	wall_face;
	cur_coord = mk_point(0, 0);
	current_y = 0;
	current_x = 0;
	// current_x = -(round((player.pos.x))- player.pos.x);
	// current_y = (-round((player.pos.y)) + player.pos.y);

		while (furthest_point.x != floor(cur_coord.x) || furthest_point.y != floor(cur_coord.y))
		{
			if ((furthest_point.x > 0.000001 && furthest_point.y > 0.000001) || is_double_pretty_much_zero(furthest_point.x))
			{
				if (is_double_pretty_much_zero(furthest_point.x))
				{
					if (furthest_point.y < -0.000001)
					{
						current_y = round_clossest_half(current_y - change_wall_size_look);
						// cur_coord = mk_point(current_x, current_y + change_wall_size_look);
						cur_coord = mk_point(current_x, current_y);
					}
					else
					{
						current_y = round_clossest_half(current_y + change_wall_size_look);
						// cur_coord = mk_point(current_x, current_y - change_wall_size_look);
						cur_coord = mk_point(current_x, current_y);
					}
				}
				// ! this is now not good enought
				else if (round_clossest_half(current_x + change_wall_size_look) / slope < round_clossest_half(current_y + change_wall_size_look))
					cur_coord = rc_get_next_y_incrementation_wall(&current_x, &current_y, slope, change_wall_size_look, false, false, player_offset_x, player_offset_y);
				else
					cur_coord = rc_get_next_x_incrementation_wall(&current_x, &current_y, slope, change_wall_size_look, false, false, player_offset_x, player_offset_y);
				good = find_wall(board, cur_coord, player);
				if (good == NULL)
					puts("raycast out of bound 1");
				else if (*good)
					return (convert_good_coordinates_wall(good_coord, player, current_x, current_y));
			}
			else if ((furthest_point.x < -0.000001 && furthest_point.y > 0.000001) || is_double_pretty_much_zero(furthest_point.y))
			{
				if (is_double_pretty_much_zero(furthest_point.y))
				{
					if (furthest_point.x < -0.000001)
					{
						current_x = round_clossest_half(current_x - change_wall_size_look);
						// cur_coord = mk_point(current_x + change_wall_size_look, current_y);
						cur_coord = mk_point(current_x, current_y);
					}
					else
					{
						current_x = round_clossest_half(current_x + change_wall_size_look);
						// cur_coord = mk_point(current_x - change_wall_size_look, current_y);
						cur_coord = mk_point(current_x, current_y);
					}
				}
				// ! this is now not good enought
				else if (round_clossest_half(current_x - change_wall_size_look) / slope < round_clossest_half(current_y + change_wall_size_look))
					cur_coord = rc_get_next_y_incrementation_wall(&current_x, &current_y, slope, change_wall_size_look, true, false, player_offset_x, player_offset_y);
				else
					cur_coord = rc_get_next_x_incrementation_wall(&current_x, &current_y, slope, change_wall_size_look, true, false, player_offset_x, player_offset_y);
				good = find_wall(board, cur_coord, player);
				if (good == NULL)
					puts("raycast out of bound 1");
				else if (*good)
					return (convert_good_coordinates_wall(good_coord, player, current_x, current_y));
			}
			else if (furthest_point.x > +0.000001 && furthest_point.y < -0.000001)
			{
				// ! this is now not good enought
				if (round_clossest_half(current_x + change_wall_size_look) / slope > round_clossest_half(current_y - change_wall_size_look))
					cur_coord = rc_get_next_y_incrementation_wall(&current_x, &current_y, slope, change_wall_size_look, false, true, player_offset_x, player_offset_y);
				else
					cur_coord = rc_get_next_x_incrementation_wall(&current_x, &current_y, slope, change_wall_size_look, false, true, player_offset_x, player_offset_y);
				good = find_wall(board, cur_coord, player);
				if (good == NULL)
					puts("raycast out of bound 1");
				else if (*good)
					return (convert_good_coordinates_wall(good_coord, player, current_x, current_y));
			}
			else if (furthest_point.x < -0.000001 && furthest_point.y < -0.000001)
			{
				// ! this is now not good enought
				if (round_clossest_half(current_x - change_wall_size_look) / slope > round_clossest_half(current_y - change_wall_size_look))
					cur_coord = rc_get_next_y_incrementation_wall(&current_x, &current_y, slope, change_wall_size_look, true, true, player_offset_x, player_offset_y);
				else
					cur_coord = rc_get_next_x_incrementation_wall(&current_x, &current_y, slope, change_wall_size_look, true, true, player_offset_x, player_offset_y);
				good = find_wall(board, cur_coord, player);
				if (good == NULL)
					puts("raycast out of bound 1");
				else if (*good)
					return (convert_good_coordinates_wall(good_coord, player, current_x, current_y));
			}
		}
	puts("didn't found wall");
	puts("");
	return (NULL);
}

t_point **view_walls(t_map map, int x_resolution)
{
	t_point **all_walls;
	double angle_drift = map.player.angle_view / x_resolution;
	int     current_wall_index = 0;
	double  current_angle = map.player.angle - (map.player.angle_view  / 2);
	double  final_angle = map.player.angle + (map.player.angle_view  / 2);
	double  number_of_found_walls = ceil(map.player.angle_view  / angle_drift);
	// print_point("playerpos is ", map.player.pos);
	all_walls = malloc(sizeof(t_point *) * (number_of_found_walls + 3));
	while (final_angle > current_angle)
	{
		t_point *current_wall;
		current_wall =  ray_casting_to_find_wall(map.board, map.player, current_angle);
		// print_point("current wall is",*current_wall);
		if (current_wall != NULL)
		{
			if (current_wall_index == 0)
			{
				all_walls[current_wall_index] = current_wall;
				current_wall_index++;
			}
			else if ((*current_wall).x == (*all_walls[current_wall_index - 1]).x && (*current_wall).y == (*all_walls[current_wall_index - 1]).y)
			{
				// puts("dup wall");
			}
			else
			{
				all_walls[current_wall_index] = current_wall;
				current_wall_index++;
			}
		}
		current_angle = current_angle + angle_drift;
	}
	all_walls[current_wall_index] = NULL;
	// printf("curent walls are %i\n", current_wall_index);
	return (all_walls);
}
