/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 13:14:21 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/02/11 11:05:17 by oscarmathot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <math.h>
#include <stdio.h>

void print_all_walls(t_param_mlx *param_real);
void update_current_wall(t_point ***walls, t_map map);
void handle_mouse(t_param_mlx *mlx);
t_point mk_point(double x, double y);

int search_board_walls(char **board, t_point furthest_point, t_point *player) {
  int i;
  int j;
  double wall_x;
  double wall_y;
  double offset;
  // t_point current;

  printf("map inside of board serach here:\n");
  print_map(board);
  printf("\n");
  i = 0;
  offset = 0.5;
  // current = mk_point(0, 0);
  while (board[i]) {
    j = 0;
    while (board[i][j]) {
      if (board[i][j] == '1') {
        wall_y = (double)i;
        wall_x = (double)j;
        printf(
            "player x = (%f), player y = (%f)\nwall x = (%f), wall y = (%f)\n",
            player->x, player->y, wall_x, wall_y);
        // current = mk_point( ,)
        if (fabs(furthest_point.x - wall_x) <= offset &&
            fabs(furthest_point.y - wall_y) <= offset) {
          puts("!COLLIDE!");
          return (1);
        }
        // if (param->map.player.pos.y == wall_y)
        // 	return (1);
      }
      j++;
    }
    i++;
  }
  return (0);
}

int cast_ray(char **board, t_point *player, int angle) {
  double radian = (angle * (M_PI / 180));
  t_point furthest_point =
      mk_point(round(sin(radian) + player->x), round(-cos(radian) + player->y));
  if (search_board_walls(board, furthest_point, player) == 1)
    return (1);
  return (0);
}

// int player
void player_move(void *param) {
  t_param_mlx *param_real;

  param_real = (t_param_mlx *)param;
  print_all_walls(param_real);
  handle_mouse(param_real);
  if (mlx_is_key_down(param_real->mlx, MLX_KEY_ESCAPE)) {
    mlx_close_window(param_real->mlx);
  }
  if (mlx_is_key_down(param_real->mlx, MLX_KEY_W)) {
    if (!cast_ray(param_real->map.board, &param_real->map.player.pos, 0)) {
      param_real->map.player.pos.y -= 0.01;
      update_current_wall(&param_real->current_visible_walls, param_real->map);
    }
  }
  if (mlx_is_key_down(param_real->mlx, MLX_KEY_S)) {
    if (!cast_ray(param_real->map.board, &param_real->map.player.pos, 180)) {
      param_real->map.player.pos.y += 0.01;
      update_current_wall(&param_real->current_visible_walls, param_real->map);
    }
  }
  if (mlx_is_key_down(param_real->mlx, MLX_KEY_A)) {
    if (!cast_ray(param_real->map.board, &param_real->map.player.pos, 270)) {
      param_real->map.player.pos.x -= 0.01;
      update_current_wall(&param_real->current_visible_walls, param_real->map);
    }
  }
  if (mlx_is_key_down(param_real->mlx, MLX_KEY_D)) {
    if (!cast_ray(param_real->map.board, &param_real->map.player.pos, 90)) {
      param_real->map.player.pos.x += 0.01;
      update_current_wall(&param_real->current_visible_walls, param_real->map);
    }
    // param_real->map.player.pos.x += 0.002;
    // update_current_wall(&param_real->current_visible_walls, param_real->map);
  }
}
