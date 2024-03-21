/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samuel <samuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:07:53 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/03/21 14:35:05 by samuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_point_int	mk_point_int(int x, int y)
{
	t_point_int	new_point;

	new_point.x = x;
	new_point.y = y;
	return (new_point);
}

t_point	mk_point(double x, double y)
{
	t_point	new_point;

	new_point.x = x;
	new_point.y = y;
	return (new_point);
}

// void	print_point(char *start_message, t_point point);

t_point	*mk_point_malloc(double x, double y)
{
	t_point	*new_point;

	new_point = malloc(sizeof(t_point *));
	new_point->x = x;
	new_point->y = y;
	print_point("new point made with value: ", (*new_point));
	return (new_point);
}

bool	double_is_zero_modular_tolerence(double number, double tolerence)
{
	if (fabs(number) < tolerence)
		return (true);
	return (false);
}

bool	is_double_pretty_much_zero(double number)
{
	const double	tolerence = 0.000001;

	if (fabs(number) < tolerence)
		return (true);
	return (false);
}
