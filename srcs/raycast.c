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

t_point *ray_casting_to_find_wall(char **board, t_player player, double angle)
{
	int lenght_check = 10;
	double  randiant_angle_looking = (angle) * (M_PI / 180);
	printf("current angle is %f, radian it %f\n", angle, randiant_angle_looking);

	t_vector    direction_ray;
	direction_ray.magnitude = lenght_check;
	direction_ray.angle = angle;
	// t_point furthest_point = get_destitaion_vector(direction_ray);
	t_point furthest_point = mk_point(lenght_check * sin(randiant_angle_looking), lenght_check * cos(randiant_angle_looking));
	puts("test");
	
	printf("fardestpoint is (%f, %f)\n", furthest_point.x, furthest_point.y);
	double current_x = 0;
	double current_y = 0;
	t_point cur_coord;
	cur_coord = mk_point(0, 0);
	printf("furthwers point fabs %f %f\n", fabs(furthest_point.x), fabs(furthest_point.y));
	if (fabs(furthest_point.x) > fabs(furthest_point.y))
	{
		while (furthest_point.x != floor(cur_coord.x))
		{
			current_x = floor(cur_coord.x);
			if (furthest_point.x >= 0)
				current_x++;
			else
				current_x--;
			cur_coord = mk_point(current_x, current_x / tan((direction_ray.angle) * (M_PI / 180)));
			printf("curentposition looking is (%f, %f)\n", cur_coord.x, cur_coord.y);
			// need to replace with map bound check
			printf("curentposition looking is (%f, %f)\n", cur_coord.x + player.pos.x, -cur_coord.y + player.pos.y);
			if ((int)round(-cur_coord.y + player.pos.y) < 0 || (int)round(cur_coord.x + player.pos.x) < 0)
			{
				printf("curentposition looking is (%f, %f)\n", cur_coord.x, cur_coord.y);
				puts("found wall at neg values");
				// return (NULL);
				break ;
			}
			if (is_out_of_bound((int)round(cur_coord.x + player.pos.x), (int)round(-cur_coord.y + player.pos.y), board))
			{
				printf("curentposition looking is (%f, %f)\n", cur_coord.x, cur_coord.y);
				puts("looking beyound map");
				// return (NULL);
				break ;
			}
			if (board[(int)round(-cur_coord.y + player.pos.y)][(int)round(cur_coord.x + player.pos.x)] == '\0')
			{
				puts("fazed out bro");
				break ;
			}
			if (board[(int)round(-cur_coord.y + player.pos.y)][(int)round(cur_coord.x + player.pos.x)] == '1')
			{
				puts("wall!");
				t_point *good_coord = malloc(sizeof(t_point));
				*good_coord = mk_point((int)round(cur_coord.x + player.pos.x), (int)round(-cur_coord.y + player.pos.y)); 
				printf("final pos looking is (%f, %f)\n", (*good_coord).x, (*good_coord).y);
				return (good_coord);
			}
		}
	}
		puts("doing with Y");
	current_x = 0;
	current_y = 0;
	cur_coord = mk_point(0, 0);
	while (furthest_point.y != floor(cur_coord.y) + 1)
	{
		current_y = floor(cur_coord.y);
		if (furthest_point.y >= 0)
			current_y++;
		else
			current_y--;
		cur_coord = mk_point(current_y * tan((direction_ray.angle) * (M_PI / 180)), current_y);
		if ((int)round(-cur_coord.y + player.pos.y) < 0 || (int)round(cur_coord.x + player.pos.x) < 0)
		{
			printf("curentposition looking is (%f, %f)\n", cur_coord.x, cur_coord.y);
			puts("found wall at neg values");
			return (NULL);
		}
		if (is_out_of_bound((int)round(cur_coord.x + player.pos.x), (int)round(-cur_coord.y + player.pos.y), board))
		{
			printf("curentposition looking is (%f, %f)\n", cur_coord.x, cur_coord.y);
			puts("looking beyound map");
			return (NULL);
		}
		if (board[(int)round(-cur_coord.y + player.pos.y)][(int)round(cur_coord.x + player.pos.x)] == '1')
		{
			t_point *good_coord = malloc(sizeof(t_point));
			*good_coord = mk_point((int)round(cur_coord.x + player.pos.x), (int)round(-cur_coord.y + player.pos.y)); 
			printf("final pos looking is (%f, %f)\n", (*good_coord).x, (*good_coord).y);
			return (good_coord);
		}
	}
	puts("didn't found wall");
	return (NULL);
}

t_point **view_walls(t_map map)
{
	t_point **all_walls;
	double angle_drift = 5;
	// map.player.angle_view = 180;
	int     current_wall_index = 0;
	double  current_angle = map.player.angle - (map.player.angle_view  / 2);
	double  final_angle = map.player.angle + (map.player.angle_view  / 2);
	double  number_of_found_walls = ceil(map.player.angle_view  / angle_drift);

	all_walls = malloc(sizeof(t_point *) * (number_of_found_walls + 1));
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
	char **map_emty;
	map_emty = debug_copy(map.board);
	map_emty[(int)map.player.pos.y][(int)map.player.pos.x] = '3';

	current_wall_index = 0;
	while (all_walls[current_wall_index] != NULL)
	{
	    map_emty[(int)(*all_walls[current_wall_index]).y][(int)(*all_walls[current_wall_index]).x] = '1';
	    current_wall_index++;
	}
	print_map(map_emty);
	return (all_walls);
}