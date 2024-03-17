/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscar <oscar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:48:24 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/03/17 16:27:35 by oscar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	player_move(void *param);
char	*get_data_line(t_param_mlx *param, char x);
void	handle_mouse(t_param_mlx *mlx);
bool	double_is_zero_modular_tolerence(double number, double tolerence);
bool	is_double_pretty_much_zero(double number);
void 	make_floor_ceil(t_param_mlx *param_real);
void	save_ceil_floor_rgb(t_param_mlx *param);
void	wall_texture(t_param_mlx *param, int screen_x,
			t_wall_info wall, double wall_height);

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
	int	i;

	i = 0;
	while (i < stack->top)
	{
		if (stack->stack[i].x == cord.x && stack->stack[i].y == cord.y)
			return (true);
		i++;
	}
	return (false);
}

t_stack	*init_stack(void)
{
	t_stack	*stack;

	stack = malloc(sizeof(t_stack));
	stack->top = -1;
	return (stack);
}

bool	are_double_in_screen(double x, double y, t_param_mlx *param_real)
{
	if (x > 0 && x < (param_real->x_resolution - 1) && y > 0
		&& y < (param_real->y_resolution - 1))
		return (true);
	return (false);
}

double	find_distance(t_point a, t_point b)
{
	return (sqrt(pow(a.y - b.y, 2) + pow(a.x - b.x, 2)));
}

double	radiant_to_dregre_angle(double angle)
{
	return (angle * (180.0 / M_PI));
}

void	print_vector(char *start_message, t_vector vector)
{
	printf("%s angle = (%f), vector = (%f)\n", start_message,
		radiant_to_dregre_angle(vector.angle), vector.magnitude);
}

t_point	find_clossest_corner(t_point *wall, t_player player)
{
	t_point	clossest_corner;
	double	delta_y;
	double	delta_x;

	delta_y = wall->y - player.pos.y;
	delta_x = wall->x - player.pos.x;
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

// i hard put 400 everywhere for wall_height
t_line	find_wall_down_corner(t_point *wall, t_player player,
	int y_resolution, int i)
{
	t_line		return_line;
	t_point		pixel_point;
	t_vector	wall_vector;
	t_point		clossest_corner;
	t_vector	corner_vector;

	wall_vector.magnitude = sqrt(pow((
					player.pos.x - wall->x), 2)
			+ pow(player.pos.y - wall->y, 2));
	wall_vector.angle = atan2((player.pos.y - wall->y),
			(player.pos.x - wall->x));
	clossest_corner = find_clossest_corner(wall, player);
	corner_vector.magnitude = sqrt(pow((player.pos.x - clossest_corner.x), 2)
			+ pow(player.pos.y - clossest_corner.y, 2));
	corner_vector.angle = atan2((player.pos.y - clossest_corner.y),
			(player.pos.x - clossest_corner.x));
	if (corner_vector.angle > (M_PI * 2))
		corner_vector.angle = corner_vector.angle - (M_PI * 2);
	pixel_point = mk_point(i, ((y_resolution / 2)
				- ((400) / ((wall_vector.magnitude + 0.5)))));
	return_line.A = pixel_point;
	return_line.B = mk_point(pixel_point.x,
			((y_resolution / 2) + ((400)
					/ ((wall_vector.magnitude + 0.5)))));
	return (return_line);
}

bool	is_double_round(double i)
{
	return (double_is_zero_modular_tolerence(i - round(i), 0.1));
}

uint32_t	get_collor(int r, int g, int b, int a)
{
	uint32_t	final;

	final = ((uint32_t)r << 24) | ((uint32_t)g << 16)
		| ((uint32_t)b << 8) | (uint32_t)a;
	return (final);
}

char	other_axis(t_param_mlx *param, t_point current)
{
	if (param->map.board[(int)round(current.y + 0.5)]
		[(int)round(current.x)] == '1')
		return ('S');
	else if (param->map.board[(int)round(current.y - 0.5)]
		[(int)round(current.x)] == '1')
		return ('N');
	else if (param->map.board[(int)round(current.y)]
		[(int)round(current.x + 0.5)] == '1')
		return ('E');
	else
		return ('W');
	return ('1');
}

char	redundancy(t_param_mlx *param, t_point current)
{
	if (param->map.board[(int)round(current.y)]
		[(int)round(current.x - 0.5)] == '1')
		return ('W');
	else if (param->map.board[(int)round(current.y + 0.5)]
		[(int)round(current.x)] == '1')
		return ('S');
	else
		return ('N');
}

char	determine_face(t_param_mlx *param, int i)
{
	t_point	current;

	current = mk_point(param->current_visible_walls[i]->x,
			param->current_visible_walls[i]->y);
	if (double_is_zero_modular_tolerence(
			param->current_visible_walls[i]->x
			- floor(param->current_visible_walls[i]->x)
			- 0.5, 0.01))
	{
		if (param->map.board[(int)round(current.y)]
			[(int)round(current.x + 0.5)] == '1')
		{
			if (param->map.board[(int)round(current.y)]
				[(int)round(current.x - 0.5)] == '1')
				return ('W');
			return ('E');
		}
		else
			return (redundancy(param, current));
	}
	else
		return (other_axis(param, current));
}

void	initialize_wall_info(t_wall_info *wall)
{
	wall->collision.x = 0;
	wall->collision.y = 0;
	wall->wall_face = 'c';
}

void	print_all_walls(t_param_mlx *param_real)
{
	int			i;
	t_wall_info	wall;

	initialize_wall_info(&wall);
	mlx_delete_image(param_real->mlx, param_real->image_to_draw_pixel);
	param_real->image_to_draw_pixel = mlx_new_image(
			param_real->mlx, param_real->x_resolution,
			param_real->y_resolution);
	make_floor_ceil(param_real);
	i = 0;
	while (param_real->current_visible_walls[i])
	{
		wall.collision = *param_real->current_visible_walls[i];
		wall.wall_face = determine_face(param_real, i);
		wall_texture(param_real, i, wall, 400);
		i++;
	}
	mlx_image_to_window(param_real->mlx, param_real->image_to_draw_pixel, 0, 0);
}

void	update_current_wall(t_point ***walls, t_map map, double x_resolution)
{
	(*walls) = view_walls(map, x_resolution);
	return ;
}

void	save_file_data(t_param_mlx *param)
{
	param->map.wall_N = mlx_load_png(get_data_line(param, 'N'));
	param->map.wall_S = mlx_load_png(get_data_line(param, 'S'));
	param->map.wall_E = mlx_load_png(get_data_line(param, 'E'));
	param->map.wall_W = mlx_load_png(get_data_line(param, 'W'));
	save_ceil_floor_rgb(param);
}

void	mlx_shit(t_map map)
{
	t_param_mlx	*param_mlx;
	mlx_t		*mlx;

	param_mlx = malloc(sizeof(t_param_mlx));
	param_mlx->current_visible_walls = view_walls(map, 1080);
	param_mlx->x_resolution = 1080;
	param_mlx->y_resolution = 720;
	param_mlx->map = map;
	save_file_data(param_mlx);
	mlx = mlx_init(1080, 720, "main_window", false);
	param_mlx->image_to_draw_pixel = mlx_new_image(
			mlx, param_mlx->x_resolution, param_mlx->y_resolution);
	if (!mlx)
		exit(1);
	param_mlx->mlx = mlx;
	mlx_loop_hook(mlx, player_move, param_mlx);
	handle_mouse(param_mlx);
	mlx_loop(mlx);
}
