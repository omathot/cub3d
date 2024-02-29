/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:48:24 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/02/10 19:14:45 by oscarmathot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    player_move(void    *param);

bool	stack_full(t_stack *stack)
{
	return (stack->top == 999);
}

void	stack_add(t_stack *stack, t_point cord)
{
	if (stack_full(stack))
		printf("added to full stack");
	stack->stack[stack->top++] = cord;
}

void	print_point(char *start_message, t_point point)
{
	printf("%s (%f, %f)\n", start_message, point.x, point.y);
}

bool	is_in_stack(t_stack *stack, t_point cord)
{
	int i;

	i = 0;
	while (i < stack->top)
	{
		if (stack->stack[i].x == cord.x && stack->stack[i].y == cord.y)
			return (true);
		i++;
	}
	return (false);
}

t_stack *init_stack()
{
	t_stack * stack = malloc(sizeof(t_stack));
	stack->top = -1;
	return(stack);
}

bool	are_double_in_screen(double x, double y, t_param_mlx *param_real)
{
	if (x > 0 && x < (param_real->x_resolution - 1) && y > 0 && y < (param_real->y_resolution - 1))
		return (true);
	return (false);
}

double find_distance(t_point a, t_point b) {
    return sqrt(pow(a.y - b.y, 2) + pow(a.x - b.x, 2));
}

void	draw_line(t_point a, t_point b, t_param_mlx *param_real, uint32_t collor)
{
	// t_vector	vector;
	// vector.magnitude = sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
	// vector.angle = atan2(b.y - a.y, b.x - a.x);
	// if (vector.angle < 0)
	// 	vector.angle = vector.angle + 360;
	double delta_x;
	double delta_y;
	double	i = 0;
	double	x;
	double	y;
	double distance;
	int steps;

	distance = find_distance(a, b);
	delta_x = (a.x - b.x) / distance;
	delta_y = (a.y - b.y) / distance;
	// print_point("delta x and y draw line", mk_point(delta_x, delta_y));
	steps = fabs(ceil(distance));
	if (fabs(delta_y) <= fabs(delta_x))
	{
		if (fabs(b.x) <= fabs(a.x))
		{
			x = a.x;
			y = a.y;
		}
		else
		{
			x = b.x;
			y = b.y;
		}
	}
	else
	{
		if (fabs(b.y) <= fabs(a.y))
		{
			x = a.x;
			y = a.y;
		}
		else
		{
			x = b.x;
			y = b.y;
		}
	}
	while (i < steps)
	{
		x = x + delta_x;
		y = y + delta_y;
		if (are_double_in_screen(floor(x), floor(y), param_real))
		{
			mlx_put_pixel(param_real->image_to_draw_pixel, floor(x), floor(y), collor);
		}
		i++;
	}
}

void	draw_line_l(t_line line, t_param_mlx *param_real, uint32_t collor)
{
	draw_line(line.A, line.B, param_real, collor);
}

double	radiant_to_dregre_angle(double angle)
{
	return (angle * (180.0 / M_PI));
}

void	print_vector(char *start_message, t_vector vector)
{
	printf("%s angle = (%f), vector = (%f)\n", start_message, radiant_to_dregre_angle(vector.angle), vector.magnitude);
}

// t_point *mk_point_malloc(double x, double y);

t_point	find_clossest_corner(t_point *wall, t_player player)
{
	t_point	clossest_corner;
	double delta_y = wall->y - player.pos.y;
	double delta_x = wall->x - player.pos.x;
	if (delta_x > 0)
		clossest_corner.x = wall->x + 0.5;
	else
		clossest_corner.x = wall->x - 0.5;
	if (delta_y > 0)
		clossest_corner.y = wall->y + 0.5;
	else
		clossest_corner.y = wall->y - 0.5;
	return (clossest_corner);
}


t_line	find_wall_down_corner(t_point *wall, t_player player, int y_resolution, int i)
{
	t_line			return_line;
	t_point		pixel_point;
	t_vector	wall_vector;
	t_point		clossest_corner;
	t_vector	corner_vector;
	// const int	y_off_set = 50;
	const int	wall_hight = 400;
	// const int	y_off_set = 200;

	wall_vector.magnitude = sqrt(pow((player.pos.x - wall->x), 2) + pow(player.pos.y - wall->y, 2));
	wall_vector.angle = atan2((player.pos.y - wall->y), (player.pos.x - wall->x));
	clossest_corner = find_clossest_corner(wall, player);
	corner_vector.magnitude = sqrt(pow((player.pos.x - clossest_corner.x), 2) + pow(player.pos.y - clossest_corner.y, 2));
	corner_vector.angle = atan2((player.pos.y - clossest_corner.y), (player.pos.x - clossest_corner.x));
	if (corner_vector.angle > (M_PI * 2))
		corner_vector.angle = corner_vector.angle - (M_PI * 2);
	// if (wall_vector.angle < 0)
	// 	wall_vector.angle = (M_PI * 2) + wall_vector.angle;
	// if ()
	// {
	// 	t_vector	corner_vector;
	// }
	// print_point("wall point is ", (*wall));
	// print_point("player point is ", player.pos);
	// print_vector("wall_vector is ", wall_vector);
	// printf("player viewing angle is = %f, and angle is at = %f\n", player.angle_view, player.angle);
	// printf("player viewing angle is = %f, and angle is at = %f\n", player.angle_view, player.angle);
	// printf("angle screen is %f, dif wall angle and players is %f, and half players vsdiew angle %f\n",((radiant_to_dregre_angle(wall_vector.angle) - player.angle) + (player.angle_view / 2)), (wall_vector.angle - player.angle), (player.angle_view / 2));
	
	// pixel_point = mk_point((((radiant_to_dregre_angle(wall_vector.angle) - player.angle)) / player.angle_view) * (x_resolution - 1),
	// 						(y_off_set - (y_off_set) / (wall_vector.magnitude)));
	
	pixel_point = mk_point(i,
							((y_resolution / 2) - ((wall_hight) / ((wall_vector.magnitude + 0.5)))));
	// pixel_point = mk_point(i,
	// 						(floor(player.pos.y / wall_hight) * wall));
	// print_point("pixel point is =", pixel_point);
	// print_point("wall is =", (*wall));
	// puts("");
	// print_vector("corner_vector is ", wall_vector);
	return_line.A = pixel_point;
	// return_line.B = mk_point(pixel_point.x, (pixel_point.y + 5));
	return_line.B = mk_point(pixel_point.x, ((y_resolution / 2) + ((wall_hight) / ((wall_vector.magnitude + 0.5)))));
	// return_line.B = mk_point(pixel_point.x, y_resolution - 1 - y_resolution / (y_off_set / (wall_vector.magnitude)));
	// return_line.B = mk_point(pixel_point.x, pixel_point.y + 3);
	// puts("");
	return (return_line);
	print_vector("",wall_vector);
}


bool	double_is_zero_modular_tolerence(double number, double tolerence);

bool	is_double_round(double i)
{
	return (double_is_zero_modular_tolerence(i - round(i), 0.1));
}

// Red (R): 0 to 255
// Green (G): 0 to 255
// Blue (B): 0 to 255
// Alpha (A): 0 to 255, where 0 represents full transparency and 255 represents full opacity.
uint32_t	get_collor(int r, int g, int b, int a)
{
	//255 * 256 * 256 + 255 * 256 + 255
	// uint32_t final = r * pow(256, 3) + g * pow(256, 2) + b * 256 + a;
	    uint32_t final = ((uint32_t)r << 24) | ((uint32_t)g << 16) | ((uint32_t)b << 8) | (uint32_t)a;
	return (final);
}

void	print_all_walls(t_param_mlx *param_real)
{
	int i;
	t_line	corner_line;
	// bool	prev_corner = false;
	// t_line	prev_corner_line;
	
	mlx_delete_image(param_real->mlx, param_real->image_to_draw_pixel);
	param_real->image_to_draw_pixel = mlx_new_image(param_real->mlx, param_real->x_resolution, param_real->y_resolution);
	i = 0;
	while (param_real->current_visible_walls[i + 2])
	{
		corner_line = find_wall_down_corner(param_real->current_visible_walls[i], param_real->map.player, param_real->y_resolution, i);
		if (!are_double_in_screen(corner_line.A.x, corner_line.A.y, param_real))
		{
			// prev_corner = false;
			i++;
			continue ;
		}
		// if (prev_corner)
		// {
		// 	print_point("prev A is", prev_corner_line.A);
		// 	print_point("cur A is", corner_line.A);
		// 	draw_line(prev_corner_line.A, corner_line.A, param_real, 255 * 256 * 256 + 255 * 256 + 255);
		// 	draw_line(prev_corner_line.B, corner_line.B, param_real, 255 * 256 * 256 + 255 * 256 + 255);
		// }
		if (are_double_in_screen(corner_line.A.x, corner_line.A.y, param_real))
		{
			// if (corner_line.B.x > param_real->x_resolution)
			// 	draw_line_l(corner_line, param_real, 255 + 255 * 256 + 255);
			// else
			// 	draw_line_l(corner_line, param_real, 255 * 256 * 256 + 255 * 256 + 255);
			
			if (
				(is_double_round(param_real->current_visible_walls[i]->x + 0.5) &&  
				is_double_round(param_real->current_visible_walls[i]->y - 0.5)) 
				|| (is_double_round(param_real->current_visible_walls[i]->x - 0.5) &&  
				is_double_round(param_real->current_visible_walls[i]->y + 0.5))
				|| (is_double_round(param_real->current_visible_walls[i]->x - 0.5) &&  
				is_double_round(param_real->current_visible_walls[i]->y - 0.5)) 
				|| (is_double_round(param_real->current_visible_walls[i]->x + 0.5) &&  
				is_double_round(param_real->current_visible_walls[i]->y + 0.5)))
				draw_line_l(corner_line, param_real, get_collor(0, 255, 0, 255));
			else
				draw_line_l(corner_line, param_real, get_collor(0, 0, 255, 255));
		}
		// prev_corner_line = corner_line;
		// prev_corner_line.A.x = corner_line.A.x;
		// prev_corner_line.A.y = corner_line.A.y;
		// prev_corner_line.B = corner_line.B;
		// prev_corner = true;
		i++;
	}
	mlx_image_to_window(param_real->mlx, param_real->image_to_draw_pixel, 0, 0);
}

void	update_current_wall(t_point ***walls, t_map map, double x_resolution)
{
	// int i;
	// while (walls[i])
	// {
	// 	free(walls[i]);
	// 	i++;
	// }
	// free(walls);
	(*walls) = view_walls(map, x_resolution);
	return ;
	// update_current_wall(walls, map);
}

// void    ft_hook(void    *param)
// {
// 	t_param_mlx *param_real;

// 	param_real = (t_param_mlx *)param;
// 	print_all_walls(param_real);
// 	if (mlx_is_key_down(param_real->mlx, MLX_KEY_ESCAPE))
// 	{
// 		mlx_close_window(param_real->mlx);
// 	}
// 	// if (mlx_is_key_down(param_real->mlx, MLX_KEY_E))
// 	// {
// 	// }
// 	if (mlx_is_key_down(param_real->mlx, MLX_KEY_W))
// 	{
// 		param_real->map.player.pos.y += 0.002;
// 		update_current_wall(&param_real->current_visible_walls, param_real->map);
// 	}
// 	if (mlx_is_key_down(param_real->mlx, MLX_KEY_S))
// 	{
// 		param_real->map.player.pos.y -= 0.002;
// 		update_current_wall(&param_real->current_visible_walls, param_real->map);
// 	}
// 	if (mlx_is_key_down(param_real->mlx, MLX_KEY_A))
// 	{
// 		param_real->map.player.pos.x += 0.002;
// 		update_current_wall(&param_real->current_visible_walls, param_real->map);
// 	}
// 	if (mlx_is_key_down(param_real->mlx, MLX_KEY_D))
// 	{
// 		param_real->map.player.pos.x -= 0.002;
// 		update_current_wall(&param_real->current_visible_walls, param_real->map);
// 	}
// }


void handle_mouse(t_param_mlx *mlx);

void	mlx_shit(t_map map)
{
	t_param_mlx *param_mlx;
	param_mlx = malloc(sizeof(t_param_mlx));
	param_mlx->current_visible_walls = view_walls(map, 1080);
	param_mlx->x_resolution = 1080;
	param_mlx->y_resolution = 720;
	param_mlx->map = map;
	// pause();
	mlx_t   *mlx;
	mlx = mlx_init(1080,720, "main_window", false);
	param_mlx->image_to_draw_pixel = mlx_new_image(mlx, param_mlx->x_resolution,param_mlx->y_resolution);
	if (!mlx)
		exit(1);
	param_mlx->mlx = mlx;
	mlx_loop_hook(mlx, player_move, param_mlx);
  handle_mouse(param_mlx);
	mlx_loop(mlx);
}

