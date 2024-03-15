/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 13:23:51 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/03/15 21:03:14 by oscarmathot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_all_walls(t_param_mlx *param_real);
void	update_current_wall(t_point ***walls, t_map map, double x_resolution);
void	print_all_walls(t_param_mlx *param_real);

void	mlx_mouse_hide(t_param_mlx *mlx)
{
	mlx_set_cursor_mode(mlx->mlx, MLX_MOUSE_HIDDEN);
}

void	mlx_mouse_show(t_param_mlx *mlx)
{
	mlx_set_cursor_mode(mlx->mlx, MLX_MOUSE_NORMAL);
}

// static t_point32	center;
// mlx_get_monitor_size(0, &center.x, &center.y);
void	mouse_movement(double x, double y, void *param)
{
	t_param_mlx			*mlx;
	static t_point32	change;

	mlx = (t_param_mlx *)param;
	x = 540;
	y = 360;
	mlx_get_mouse_pos(mlx->mlx, &change.x, &change.y);
	if (change.x > x)
	{
		if (mlx->map.player.angle >= y)
			mlx->map.player.angle = 0;
		mlx->map.player.angle += 5;
		update_current_wall(&mlx->current_visible_walls, mlx->map,
			mlx->x_resolution);
	}
	if (change.x < x)
	{
		if (mlx->map.player.angle <= 0)
			mlx->map.player.angle = 360;
		mlx->map.player.angle -= 5;
		update_current_wall(&mlx->current_visible_walls, mlx->map,
			mlx->x_resolution);
	}
	mlx_set_mouse_pos(mlx->mlx, 540, y);
}

void	handle_mouse(t_param_mlx *mlx)
{
	mlx->cursor = mlx_create_std_cursor(MLX_CURSOR_CROSSHAIR);
	mlx_set_cursor(mlx->mlx, mlx->cursor);
	mlx_set_mouse_pos(mlx->mlx, 540, 360);
	mlx_cursor_hook(mlx->mlx, mouse_movement, mlx);
}
