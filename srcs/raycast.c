/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omathot <omathot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:02:17 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/02/08 15:09:08 by omathot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// needs to be justified
t_point get_destitaion_vector(t_vector vector)
{
	double  x;
	double  y;
	double  absolute_positive_angle;

	absolute_positive_angle = vector.angle;
	while (absolute_positive_angle > 90)
	{
		absolute_positive_angle = absolute_positive_angle - 90;
	}
	x = sin(absolute_positive_angle * (M_PI / 180));
	y = cos(absolute_positive_angle * (M_PI / 180));
	if (vector.angle <= 90)
		return (mk_point(x, y));
	if (vector.angle <= 180)
		return (mk_point(x, -y));
	if (vector.angle <= 270)
		return (mk_point(-x, -y));
	// if (vector.angle <= 360)
	return (mk_point(-x, y));
}

bool	is_out_of_bound(int x, int y, char **board)
{
	int i;

	i = 0;
	while (board[i])
	{
		i++;
	}
	if (y < i)
		return (false);
	int j;
	i = 0;
	while (board[i])
	{
		j = 0;
		while (board[i][j])
		{
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

bool	*find_wall(char **board, t_point cur_coord, t_player player, t_point *good_coord)
{
	static bool	find;
	find = false;

	if ((int)round(-cur_coord.y + player.pos.y) < 0 || (int)round(cur_coord.x + player.pos.x) < 0)
	{
		puts("found wall at neg values");
		pause();
		return (NULL);
	}
	if (is_out_of_bound((int)round(cur_coord.x + player.pos.x), (int)round(-cur_coord.y + player.pos.y), board))
	{
		puts("looking beyound map");
		print_point("cur coord", cur_coord);
		print_point("player pos", player.pos);
		return (NULL);
	}
	if (board[(int)round(-cur_coord.y + player.pos.y)][(int)round(cur_coord.x + player.pos.x)] == '\0')
	{
		puts("fazed out bro");
		return (NULL);
	}
	if (board[(int)round(-cur_coord.y + player.pos.y)][(int)round(cur_coord.x + player.pos.x)] == '1')
	{
		*good_coord = mk_point((cur_coord.x + player.pos.x), (-cur_coord.y + player.pos.y)); 
		find = true;
		return (&find);
	}
	return (&find);
}

void	convert_good_coordinates_wall(t_point *good_coord, t_player player, t_point cur_coord)
{
	(*good_coord) = mk_point(((*good_coord).x + player.pos.x), (-(*good_coord).y + player.pos.y));
}

// Calculate the next multiples of 0.5
int closest_to_next_half_v1(double num1, double num2, double slope, t_point furthest_point) 
{
	double next_half1, next_half2;
	double slopeleft1, slopeleft2;
	double diff1, diff2, slope1, slope2;

	if (num1 == 0 && num2 == 0)
	{
		if (fabs(furthest_point.x) > fabs(furthest_point.y))
			return 1; 
		return 2;
	}


	if (furthest_point.x == 0)
		return (2);
	if (furthest_point.y == 0)
		return (1);
	next_half1 = ceil((num1) * 2) / 2;
	next_half2 = ceil((num2) * 2) / 2; 

	diff1 = fabs(next_half1 - num1 );
	diff2 = fabs(next_half2 - num2);

	slope1 = diff1 ;
	slope2 = diff2 ;
	if (slope1 < slope2)
		return (1);
	else if (slope2 < slope1)
		return (2);
	if (fabs(slope) < 1)
		return (1);
	return (2);
}

bool	is_double_pretty_much_zero(double number)
{
	const double	tolerence = 0.000001;
	if (fabs(number) < tolerence)
		return (true);
	return (false);
}

int closest_to_next_half(double num1, double num2, double delta_1, double delta_2)
{
	double	next_half1;
	double	next_half2;

	if (num1 == 0 && num2 == 0)
	{
		return (0);
	}
	next_half1 = ceil((num1) * 2) / 2;
	next_half2 = ceil((num2) * 2) / 2;
	
	double tollerence = 0.00001;
	if (next_half1 - num1 <= delta_1 + tollerence && !is_double_pretty_much_zero(next_half1 - num1))
		return (1);
	if (next_half2 - num2 <= delta_2 + tollerence && !is_double_pretty_much_zero(next_half2 - num2))
		return (2);
	return (0);
}




double	round_next_clossest_half(double number)
{
	return (ceil((number) * 2) / 2);
}

double	round_clossest_half(double number)
{
	return (floor((number) * 2) / 2);
}

t_point	rc_get_next_y_incrementation_wall(double *current_x, double *current_y, double slope, double change_wall_size_look, bool x_neg, bool y_neg)
{
	double	current_x_round;
	t_point	cur_coord;


	if (!y_neg)
		(*current_y) = round_clossest_half((*current_y) + change_wall_size_look);
	else
		(*current_y) = -round_clossest_half(-(*current_y) + change_wall_size_look);
	// (*current_y) = round_clossest_half((*current_y) + change_wall_size_look);
	if (fabs(*current_x) > 0.000)
		if (!x_neg)
		{
			current_x_round = round_next_clossest_half((*current_x));
		}
		else
		{
			current_x_round = -round_next_clossest_half(-(*current_x));
		}
	else
		current_x_round = 0;
	double past_x = (*current_x);
	bool	is_x_closser_to_wall = false;
	(*current_x) = (*current_y) / slope;
	if (!x_neg)
	{
		if (current_x_round <= (*current_x) && current_x_round != 0 && !is_double_pretty_much_zero(current_x_round - past_x))
			is_x_closser_to_wall = true;
	}
	else
	{
		if (current_x_round >= (*current_x) && current_x_round != 0 && !is_double_pretty_much_zero(current_x_round - past_x))
			is_x_closser_to_wall = true;
	}
	if (is_x_closser_to_wall)
	{
		(*current_x) = current_x_round;
		(*current_y) = (*current_x) * slope;

		if (!y_neg)
			cur_coord = mk_point((*current_x), (*current_y) - change_wall_size_look);
		else
			cur_coord = mk_point((*current_x), (*current_y) + change_wall_size_look);

		// cur_coord = mk_point((*current_x), (*current_y) - change_wall_size_look);
	}
	else
		if (!x_neg)
		{
			cur_coord = mk_point((*current_x) - change_wall_size_look, (*current_y));
		}
		else
		{
			cur_coord = mk_point((*current_x) + change_wall_size_look, (*current_y));
		}
	return (cur_coord);
}

t_point	rc_get_next_x_incrementation_wall(double *current_x, double *current_y, double slope, double change_wall_size_look, bool x_neg, bool y_neg)
{
	t_point	cur_coord;
	double	current_y_round;
	if (!x_neg)
		(*current_x) = round_clossest_half((*current_x) + change_wall_size_look);
	else
		(*current_x) = -round_clossest_half(-(*current_x) + change_wall_size_look);
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
	}
	else
		current_y_round = 0;
	// if ((*current_y) > 0.000)
	// 	current_y_round = round_next_clossest_half((*current_y));
	// else
	// 	current_y_round = 0;
	double past_y = (*current_y);

	bool	is_y_closser_to_wall = false;
	(*current_y) = (*current_x) * slope;
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
		(*current_x) = (*current_y) / slope;
		if (!x_neg)
			cur_coord = mk_point((*current_x) - change_wall_size_look, (*current_y));
		else
			cur_coord = mk_point((*current_x) + change_wall_size_look, (*current_y));
	}
	else
	{
		if (!y_neg)
		{
			cur_coord = mk_point((*current_x), (*current_y) - change_wall_size_look);
		}
		else
		{
			cur_coord = mk_point((*current_x), (*current_y) + change_wall_size_look);
		}
		// cur_coord = mk_point((*current_x), (*current_y) - change_wall_size_look);
	}
	// (*current_y) = (*current_x) * slope;
	// if (current_y_round <= (*current_y) && current_y_round != 0 && !is_double_pretty_much_zero(current_y_round - past_y))
	// {
	// 	(*current_y) = current_y_round;
	// 	(*current_x) = (*current_y) / slope;
	// 	if (!x_neg)
	// 		cur_coord = mk_point((*current_x) - change_wall_size_look, (*current_y));
	// 	else
	// 		cur_coord = mk_point((*current_x) + change_wall_size_look, (*current_y));
	// }
	// else
	// 	cur_coord = mk_point((*current_x), (*current_y) - change_wall_size_look);
	return (cur_coord);
}

t_point *ray_casting_to_find_wall(char **board, t_player player, double angle)
{
	int lenght_check = 10;
	double  randiant_angle_looking = (angle) * (M_PI / 180);


	t_vector    direction_ray;
	direction_ray.magnitude = lenght_check;
	direction_ray.angle = angle;
	t_point furthest_point = mk_point(lenght_check * sin(randiant_angle_looking), lenght_check * cos(randiant_angle_looking));
	double current_x = 0;
	double current_y = 0;
	double current_x_round = 0;
	double current_y_round = 0;
	t_point cur_coord;
	// double	delta_x = sin((direction_ray.angle) * (M_PI / 180)) / 2;
	// double	delta_y = cos((direction_ray.angle) * (M_PI / 180)) / 2;
	double	change_wall_size_look = 0.5;
	t_point *good_coord = (t_point *)malloc(sizeof(t_point));
	bool *good;
	double	slope = calculate_slope(mk_point(0,0), furthest_point);
	t_orientation	wall_face;
	cur_coord = mk_point(0, 0);
	current_y = 0;
	current_x = 0;
		while (furthest_point.x != floor(cur_coord.x) || furthest_point.y != floor(cur_coord.y))
		{
			if ((furthest_point.x > 0.000001 && furthest_point.y > 0.000001) || is_double_pretty_much_zero(furthest_point.x))
			{
				if (is_double_pretty_much_zero(furthest_point.x))
				{
					current_y = round_clossest_half(current_y + change_wall_size_look);
					cur_coord = mk_point(current_x, current_y - change_wall_size_look);
				}
				else if (round_clossest_half(current_x + change_wall_size_look) / slope < round_clossest_half(current_y + change_wall_size_look))
				{
					// current_y = round_clossest_half(current_y + change_wall_size_look);
					// if (current_x > 0.000)
					// 	current_x_round = round_next_clossest_half(current_x);
					// else
					// 	current_x_round = 0;
					// double past_x = current_x;
					// current_x = current_y / slope;
					// if (current_x_round <= current_x && current_x_round != 0 && !is_double_pretty_much_zero(current_x_round - past_x))
					// {
					// 	current_x = current_x_round;
					// 	current_y = current_x * slope;
					// 	cur_coord = mk_point(current_x, current_y - change_wall_size_look);
					// }
					// else
					// 	cur_coord = mk_point(current_x - change_wall_size_look, current_y);
					cur_coord = rc_get_next_y_incrementation_wall(&current_x, &current_y, slope, change_wall_size_look, false, false);
				}
				else
				{
					// current_x = round_clossest_half(current_x + change_wall_size_look);
					// if (current_y > 0.000)
					// 	current_y_round = round_next_clossest_half(current_y);
					// else
					// 	current_y_round = 0;
					// double past_y = current_y;
					// current_y = current_x * slope;
					// if (current_y_round <= current_y && current_y_round != 0 && !is_double_pretty_much_zero(current_y_round - past_y))
					// {
					// 	current_y = current_y_round;
					// 	current_x = current_y / slope;
					// 	cur_coord = mk_point(current_x - change_wall_size_look, current_y);
					// }
					// else
					// 	cur_coord = mk_point(current_x, current_y - change_wall_size_look);
					cur_coord = rc_get_next_x_incrementation_wall(&current_x, &current_y, slope, change_wall_size_look, false, false);
				}
				good = find_wall(board, cur_coord, player, good_coord);
				if (good == NULL)
					puts("raycast out of bound 1");
				else if (*good)
				{
					(*good_coord).x = current_x;
					(*good_coord).y = current_y;
					convert_good_coordinates_wall(good_coord, player, cur_coord);
					return (good_coord);
				}
			}
			else if ((furthest_point.x < -0.000001 && furthest_point.y > 0.000001) || is_double_pretty_much_zero(furthest_point.y))
			{
				if (is_double_pretty_much_zero(furthest_point.y))
				{
					current_x = round_clossest_half(current_x + change_wall_size_look);
					cur_coord = mk_point(current_x + change_wall_size_look, current_y);
				}
				else if (round_clossest_half(current_x - change_wall_size_look) / slope < round_clossest_half(current_y + change_wall_size_look))
				{
					// current_y = round_clossest_half(current_y + change_wall_size_look);
					// if (current_x < 0.000)
					// 	current_x_round = -round_next_clossest_half(-current_x);
					// else
					// 	current_x_round = 0;
					// double past_x = current_x;
					// current_x = current_y / slope;
					// if (current_x_round >= current_x && current_x_round != 0 && !is_double_pretty_much_zero(current_x_round - past_x))
					// {
					// 	current_x = current_x_round;
					// 	current_y = current_x * slope;
					// 	cur_coord = mk_point(current_x, current_y - change_wall_size_look);
					// }
					// else
					// 	cur_coord = mk_point(current_x + change_wall_size_look, current_y);
					cur_coord = rc_get_next_y_incrementation_wall(&current_x, &current_y, slope, change_wall_size_look, true, false);
				}
				else
				{
					// current_x = -round_clossest_half(-current_x + change_wall_size_look);
					// if (current_y > 0.000)
					// 	current_y_round = round_next_clossest_half(current_y);
					// else
					// 	current_y_round = 0;
					// double past_y = current_y;
					// current_y = current_x * slope;
					// if (current_y_round < current_y && current_y_round != 0 && !is_double_pretty_much_zero(current_y_round - past_y))
					// {
					// 	current_y = current_y_round;
					// 	current_x = current_y / slope;
					// 	cur_coord = mk_point(current_x + change_wall_size_look, current_y);
					// }
					// else
					// 	cur_coord = mk_point(current_x, current_y - change_wall_size_look);
					cur_coord = rc_get_next_x_incrementation_wall(&current_x, &current_y, slope, change_wall_size_look, true, false);
				}
				good = find_wall(board, cur_coord, player, good_coord);
				if (good == NULL)
					puts("raycast out of bound 1");
				else if (*good)
				{
					(*good_coord).x = current_x;
					(*good_coord).y = current_y;
					convert_good_coordinates_wall(good_coord, player, cur_coord);
					print_point("wall is at", (*good_coord));
					puts("");
					return (good_coord);
				}
			}
			else if (furthest_point.x > +0.000001 && furthest_point.y < -0.000001)
			{
				if (round_clossest_half(current_x + change_wall_size_look) / slope > round_clossest_half(current_y - change_wall_size_look))
				{
					cur_coord = rc_get_next_y_incrementation_wall(&current_x, &current_y, slope, change_wall_size_look, false, true);
				}
				else
				{
					cur_coord = rc_get_next_x_incrementation_wall(&current_x, &current_y, slope, change_wall_size_look, false, true);
				}
				good = find_wall(board, cur_coord, player, good_coord);
				if (good == NULL)
					puts("raycast out of bound 1");
				else if (*good)
				{
					(*good_coord).x = current_x;
					(*good_coord).y = current_y;
					convert_good_coordinates_wall(good_coord, player, cur_coord);
					print_point("wall is at", (*good_coord));
					puts("");
					return (good_coord);
				}
			}
			else if (furthest_point.x < 0 && furthest_point.y < 0)
			{
				if (round_clossest_half(current_x - change_wall_size_look) / slope > round_clossest_half(current_y - change_wall_size_look))
				{
					cur_coord = rc_get_next_y_incrementation_wall(&current_x, &current_y, slope, change_wall_size_look, true, true);
				}
				else
				{
					cur_coord = rc_get_next_x_incrementation_wall(&current_x, &current_y, slope, change_wall_size_look, true, true);
				}
				good = find_wall(board, cur_coord, player, good_coord);
				if (good == NULL)
					puts("raycast out of bound 1");
				else if (*good)
				{
					(*good_coord).x = current_x;
					(*good_coord).y = current_y;
					convert_good_coordinates_wall(good_coord, player, cur_coord);
					print_point("wall is at", (*good_coord));
					puts("");
					return (good_coord);
				}
			}



			// curent_case = closest_to_next_half(current_x, current_y, delta_x, delta_y, slope, furthest_point); 
			// if ((curent_case == 1 || curent_case == 3 || furthest_point.y == 0))
			// {
			// 	nulls = 0;
			// 	if (curent_case == 3)
			// 		case_neg = -1;
			// 	else
			// 		case_neg = 1;
			// 	if (curent_case == 1)
			// 	{
			// 		if (delta_x > 0)
			// 			current_x = (floor(current_x * 2) / 2) + (change_wall_size_look);
			// 		else
			// 			current_x = (floor(current_x * 2) / 2) - (change_wall_size_look);
			// 	}

			// 	if (furthest_point.y == 0.00000)
			// 		current_y = 0;
			// 	else
			// 		current_y = current_x * slope;

			// 	printf("current x = %f, current y = %f\n", current_x, current_y);
			// 	if (furthest_point.y == 0)
			// 	{
			// 		cur_coord = mk_point((current_x), current_y);
			// 	}
			// 	else
			// 	{
			// 		if (delta_x > 0)
			// 			cur_coord = mk_point(round(current_x + (change_wall_size_look * case_neg)), 0);
			// 		else
			// 			cur_coord = mk_point(round(current_x - (change_wall_size_look * case_neg)), 0);
			// 		case_neg = 0;
			// 		// cur_coord = mk_point(round(current_x + (change_wall_size_look * case_neg)), 0);
			// 		if (delta_y > 0)
			// 			cur_coord.y = round(current_y - (change_wall_size_look * case_neg));
			// 		else
			// 			cur_coord.y = round(current_y + (change_wall_size_look * case_neg));
			// 	}

			// 	good = find_wall(board, cur_coord, player, good_coord);
			// 	if (good == NULL)
			// 	{
			// 		nulls++;
			// 	}
			// 	else if (*good)
			// 	{
			// 		// print_point("pileur was at", (*good_coord));
			// 		(*good_coord).x = current_x;
			// 		(*good_coord).y = current_y;
			// 		convert_good_coordinates_wall(good_coord, player, cur_coord);
			// 		print_point("wall is at", (*good_coord));
			// 		puts("");
			// 		return (good_coord);
			// 	}

			// }
			// else
			// {
			// 	nulls = 0;
				
			// 	if (curent_case == 4)
			// 		case_neg = -1;
			// 	else
			// 		case_neg = 1;
			// 	if (curent_case == 2)
			// 	{
			// 		if (delta_y > 0)
			// 			current_y = (floor(current_y * 2) / 2) + (change_wall_size_look);
			// 		else
			// 			current_y = (floor(current_y * 2) / 2) - (change_wall_size_look);
			// 	}
			// 	if (furthest_point.x == 0.00000)
			// 		current_x = current_x;
			// 	else
			// 	printf("current x = %f, current y = %f\n", current_x, current_y);
			// 	if (furthest_point.x == 0.00000)
			// 		current_x = 0;
			// 	else
			// 		current_x = current_y / slope;


			// 		// current_x = current_y / slope;
			// 	if (furthest_point.x == 0.00000)
			// 	{
			// 		cur_coord = mk_point(current_x, current_y);
			// 	}
			// 	else
			// 	{
			// 		// if (curent_case == 2)
			// 		// if (delta_y > 0)
			// 		// 	case_neg = case_neg;
			// 		// else
			// 		// 	case_neg = -case_neg;
			// 		if (delta_y > 0)
			// 			cur_coord = mk_point(round(current_x), round(current_y + (change_wall_size_look * case_neg)));
			// 		else
			// 			cur_coord = mk_point(round(current_x), round(current_y - (change_wall_size_look * case_neg)));
			// 		case_neg = 0;
			// 		// cur_coord = mk_point(0, round(current_y + (change_wall_size_look * case_neg)));
			// 		if (delta_x > 0)
			// 			cur_coord.x = round(current_x - (change_wall_size_look * case_neg));
			// 		else
			// 			cur_coord.x = round(current_x + (change_wall_size_look * case_neg));
			// 	}

			// 	good = find_wall(board, cur_coord, player, good_coord);
			// 	if (good == NULL)
			// 		nulls++;
			// 	else if (*good)
			// 	{
			// 		// print_point("pileur was at", (*good_coord));
			// 		(*good_coord).x = current_x;
			// 		(*good_coord).y = current_y;
			// 		convert_good_coordinates_wall(good_coord, player, cur_coord);
			// 		// convert_good_coordinates_wall(good_coord, player, cur_coord);
			// 		print_point("wall is at", (*good_coord));
			// 		puts("");
			// 		return (good_coord);
			// 	}
			// }
		}
	puts("didn't found wall");
	puts("");
	return (NULL);
}

t_point **view_walls(t_map map, int x_resolution)
{
	t_point **all_walls;
	double angle_drift = map.player.angle_view / x_resolution;
	// printf("$f angligle drift");
	// map.player.angle_view = 180;
	int     current_wall_index = 0;
	double  current_angle = map.player.angle - (map.player.angle_view  / 2);
	double  final_angle = map.player.angle + (map.player.angle_view  / 2);
	double  number_of_found_walls = ceil(map.player.angle_view  / angle_drift);

	all_walls = malloc(sizeof(t_point *) * (number_of_found_walls + 3));
	while (final_angle > current_angle)
	{
		// printf("current angle is %f'\n", current_angle);
		t_point *current_wall;
		// if (current_angle < 0)
		// 	current_wall =  ray_casting_to_find_wall(map, player_position, current_angle + 360);
		// else if (current_angle > 360)
		// 	current_wall =  ray_casting_to_find_wall(map, player_position, current_angle - 360);
		// else
		current_wall =  ray_casting_to_find_wall(map.board, map.player, current_angle);
		// printf("address of currentwall %p\n", current_wall);
		print_point("current map is", (*current_wall));
		if (current_wall != NULL)
		{
			if (current_wall_index == 0)
			{
				all_walls[current_wall_index] = current_wall;
				// printf("wall found at (%f, %f)\n", (*all_walls[current_wall_index]).x, (*all_walls[current_wall_index]).y);
				current_wall_index++;
			}
			else if ((*current_wall).x == (*all_walls[current_wall_index - 1]).x && (*current_wall).y == (*all_walls[current_wall_index - 1]).y)
			{
				// printf("curent (%f, %f), last was (%f, %f)\n", (*current_wall).x ,(*current_wall).y, (*all_walls[current_wall_index - 1]).x, (*all_walls[current_wall_index - 1]).y);
				// puts("dup wall");
			}
			else
			{
				all_walls[current_wall_index] = current_wall;
				// printf("wall found at (%f, %f)\n", (*all_walls[current_wall_index]).x, (*all_walls[current_wall_index]).y);
				current_wall_index++;
			}
			// puts("");
		}
		current_angle = current_angle + angle_drift;
	}
	all_walls[current_wall_index] = NULL;
	printf("curent walls are %i\n", current_wall_index);
	// char **map_emty;
	// map_emty = debug_copy(map.board);
	// map_emty[(int)map.player.pos.y][(int)map.player.pos.x] = '3';

	// current_wall_index = 0;
	// while (all_walls[current_wall_index] != NULL)
	// {
	//     map_emty[(int)(*all_walls[current_wall_index]).y][(int)(*all_walls[current_wall_index]).x] = '1';
	//     current_wall_index++;
	// }
	// print_map(map_emty);
	return (all_walls);
}