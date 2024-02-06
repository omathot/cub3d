/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:48:24 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/02/06 17:56:36 by oscarmathot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	draw_line(t_point a, t_point b, t_param_mlx *param_real, uint32_t collor)
{
	t_vector	vector;
	vector.magnitude = sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
	vector.angle = atan2(a.y - b.y, a.x - b.x );
	t_point	temp;
	if (a.x > b.x || a.y > b.y)
	temp = a;
	else
		temp = b;
	double	i = 0;
	t_stack	*cords;
	cords = init_stack();
	while (i < vector.magnitude)
	{
		if (!is_in_stack(cords, mk_point(temp.x + i * cos(vector.angle), temp.y +  i * sin(vector.angle))))
			stack_add(cords, mk_point(temp.x + i * cos(vector.angle), temp.y + i * sin(vector.angle)));
		i++;
	}
	int j = 0;
	while (j < cords->top)
	{
		printf("x = %f, y = %f\n", cords->stack[j].x, cords->stack[j].y);
		mlx_put_pixel(param_real->image_to_draw_pixel, cords->stack[j].x, cords->stack[j].y, collor);
		j++;
	}
	mlx_image_to_window(param_real->mlx, param_real->image_to_draw_pixel, 0, 0);
}

void    ft_hook(void    *param)
{
	t_param_mlx *param_real;

	param_real = (t_param_mlx *)param;
	if (mlx_is_key_down(param_real->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(param_real->mlx);
	}
	if (mlx_is_key_down(param_real->mlx, MLX_KEY_W))
		draw_line(mk_point(0, 0), mk_point(500, 500), param_real, 255 * 256 * 256 + 255 * 256 + 255);
}

void	mlx_shit()
{
	t_param_mlx *param_mlx;
	
	param_mlx = malloc(sizeof(t_param_mlx));
	// pause();
	mlx_t   *mlx;
	mlx = mlx_init(1080,720, "main_window", false);
	param_mlx->image_to_draw_pixel = mlx_new_image(mlx, 1080,720);
	if (!mlx)
		exit(1);
	param_mlx->mlx = mlx;
	mlx_loop_hook(mlx, ft_hook, param_mlx);
	mlx_loop(mlx);
}

