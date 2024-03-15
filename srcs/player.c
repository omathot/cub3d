/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 13:14:21 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/03/15 12:06:30 by oscarmathot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <math.h>
#include <stdio.h>

void	print_all_walls(t_param_mlx *param_real);
void	update_current_wall(t_point ***walls, t_map map, double x_resolution);
void	handle_mouse(t_param_mlx *mlx);
t_point	mk_point(double x, double y);

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

// int cast_ray(char **board, t_point *player, int angle)
// {
//   double radian = (angle * (M_PI / 180));
//   t_point furthest_point = mk_point(round(sin(radian) + player->x), round(-cos(radian) + player->y));
//   if (search_board_walls(board, furthest_point, player) == 1)
//     return (1);
//   return (0);
// }

// --- -- --- -- -- -  -- - - -- - - -- - - - -- - - - - -- - - - -- - - -- - - -
// int search_board_walls(char **board, t_point furthest_point, t_point *player) {
//   int i;
//   int j;
//   double wall_x;
//   double wall_y;
//   double offset;
//   // t_point current;

//   i = 0;
//   offset = 0.5;
//   // current = mk_point(0, 0);
//   while (board[i]) {
//     j = 0;
//     while (board[i][j]) {
//       if (board[i][j] == '1') {
//         wall_y = (double)i;
//         wall_x = (double)j;
//         // printf(
//         //     "player x = (%f), player y = (%f)\nwall x = (%f), wall y =
//         //     (%f)\n", player->x, player->y, wall_x, wall_y);
//         // current = mk_point( ,)
//         if (fabs(furthest_point.x - wall_x) <= offset &&
//             fabs(furthest_point.y - wall_y) <= offset) {
//           puts("!COLLIDE!");
//           return (1);
//         }
//         // if (param->map.player.pos.y == wall_y)
//         //     return (1);
//       }
//       j++;
//     }
//     i++;
//   }
//   return (0);
//   printf("%f\n", player->x);
// }

// int cast_ray(char **board, t_point *player, int angle) {
//   double radian = (angle * (M_PI / 180));
//   t_point furthest_point =
//       mk_point(round(sin(radian) + player->x), round(-cos(radian) + player->y));
//   if (search_board_walls(board, furthest_point, player) == 1)
//     return (1);
//   return (0);
// }

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

void	move_left(t_param_mlx *param, float angle_radians, float move_speed)
{
	int	coll_angle;

	coll_angle = (int)(param->map.player.angle + 270) % 360;
	if (!cast_ray(param->map.board,
			&param->map.player.pos, coll_angle))
	{
		param->map.player.pos.x -= cos(angle_radians) * move_speed;
		param->map.player.pos.y -= sin(angle_radians) * move_speed;
		update_current_wall(&param->current_visible_walls,
			param->map, param->x_resolution);
	}
}

void	move_right(t_param_mlx *param, float angle_radians, float move_speed)
{
	int	coll_angle;

	coll_angle = (int)(param->map.player.angle + 90) % 360;
	if (!cast_ray(param->map.board,
			&param->map.player.pos, coll_angle))
	{
		param->map.player.pos.x += cos(angle_radians) * move_speed;
		param->map.player.pos.y += sin(angle_radians) * move_speed;
		update_current_wall(&param->current_visible_walls,
			param->map, param->x_resolution);
	}
}

void	handle_movement(t_param_mlx *param,
	float angle_radians, float move_speed, int mode)
{
	if (mode == 1)
		move_forward(param, angle_radians, move_speed);
	if (mode == 2)
		move_backwards(param, angle_radians, move_speed);
	if (mode == 3)
		move_left(param, angle_radians, move_speed);
	if (mode == 4)
		move_right(param, angle_radians, move_speed);
}

void	handle_angle(t_param_mlx *param, int mode)
{
	if (mode == 1)
	{
		if (param->map.player.angle <= 0)
			param->map.player.angle = 360;
		param->map.player.angle -= 2;
		update_current_wall(&param->current_visible_walls, param->map,
			param->x_resolution);
	}
	if (mode == 2)
	{
		if (param->map.player.angle >= 360)
			param->map.player.angle = 0;
		param->map.player.angle += 2;
		update_current_wall(&param->current_visible_walls, param->map,
			param->x_resolution);
	}
}

void	player_move(void *param)
{
	t_param_mlx	*param_real;
	float		move_speed;
	float		angle_radians;

	param_real = (t_param_mlx *)param;
	move_speed = 0.03;
	print_all_walls(param_real);
	if (mlx_is_key_down(param_real->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(param_real->mlx);
	angle_radians = param_real->map.player.angle * M_PI / 180;
	if (mlx_is_key_down(param_real->mlx, MLX_KEY_W))
		handle_movement(param, angle_radians, move_speed, 1);
	if (mlx_is_key_down(param_real->mlx, MLX_KEY_S))
		handle_movement(param, angle_radians, move_speed, 2);
	if (mlx_is_key_down(param_real->mlx, MLX_KEY_A))
		handle_movement(param, angle_radians, move_speed, 3);
	if (mlx_is_key_down(param_real->mlx, MLX_KEY_D))
		handle_movement(param, angle_radians, move_speed, 4);
	if (mlx_is_key_down(param_real->mlx, MLX_KEY_Q))
		handle_angle(param, 1);
	if (mlx_is_key_down(param_real->mlx, MLX_KEY_E))
		handle_angle(param, 2);
}
