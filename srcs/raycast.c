/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samuel <samuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:02:17 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/03/21 14:40:31 by samuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	round_clossest_half(double number);
t_point	*ray_casting_to_find_wall(char **board, t_player player, double angle);

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

t_point	*convert_coord(t_ray_cast *rascast,
	t_player player, t_point *good_coord)
{
	double	average_wall_x;
	double	average_wall_y;

	average_wall_x = rascast->current_x + round(player.pos.x);
	average_wall_y = -rascast->current_y + round((player.pos.y));
	// good_coord = (t_point *)malloc(sizeof(t_point));
	(*good_coord) = mk_point(average_wall_x, average_wall_y);
	return (good_coord);
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
	// printf("walls.number_of_found_walls + 3 == %f, angle view %f, angle dirfe %f\n", (walls.number_of_found_walls), map.player.angle_view, walls.angle_drift);
	all_walls = (t_point **)malloc(sizeof(t_point *) * (walls.number_of_found_walls + 3));
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
