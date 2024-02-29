/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 13:23:51 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/02/11 10:29:39 by oscarmathot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void print_all_walls(t_param_mlx *param_real);

void mlx_mouse_hide(t_param_mlx *mlx) {
  mlx_set_cursor_mode(mlx->mlx, MLX_MOUSE_HIDDEN);
}

void mlx_mouse_show(t_param_mlx *mlx) {
  mlx_set_cursor_mode(mlx->mlx, MLX_MOUSE_NORMAL);
}

void mouse_movement(double x, double y, void *param) {
  t_param_mlx *mlx;
  t_point32 center;
  t_point32 change;

  mlx = (t_param_mlx *)param;
  mlx_get_monitor_size(0, &center.x, &center.y);

  // this is hardcoded for a specific size, need to have it depend on the
  // resolution size
  x = 540;
  y = 360;
  mlx_get_mouse_pos(mlx->mlx, &change.x, &change.y);
  printf("center x = (%f), center y = (%f)\n", x, y);
  printf("change x = (%d), change y = (%d)\n", change.x, change.y);
  printf("player angle = (%f)\n", mlx->map.player.angle);
  if (change.x > x) {
    if (mlx->map.player.angle >= 360)
      mlx->map.player.angle = 0;
    mlx->map.player.angle += 2;
    printf("player angle = (%f)\n", mlx->map.player.angle);
  }
  if (change.x < x) {
    if (mlx->map.player.angle <= 0)
      mlx->map.player.angle = 360;
    mlx->map.player.angle -= 2;
    printf("player angle = (%f)\n", mlx->map.player.angle);
  }
}

void handle_mouse(t_param_mlx *mlx) {
  t_point32 center;

  mlx->cursor = mlx_create_std_cursor(MLX_CURSOR_CROSSHAIR);
  mlx_set_cursor(mlx->mlx, mlx->cursor);
  mlx_set_mouse_pos(mlx->mlx, 540, 360);
  mlx_get_mouse_pos(mlx->mlx, &center.x, &center.y);
  mlx_cursor_hook(mlx->mlx, mouse_movement, mlx);
}
