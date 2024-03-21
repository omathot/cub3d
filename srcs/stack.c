/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:27:31 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/03/18 15:36:43 by oscarmathot      ###   ########.fr       */
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
