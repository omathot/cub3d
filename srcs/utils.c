/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:07:53 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/02/06 15:27:59 by oscarmathot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_point mk_point(double x, double y)
{
	t_point new_point;

	new_point.x = x;
	new_point.y = y;
	return (new_point);
}

void	print_point(char *start_message, t_point point);

t_point *mk_point_malloc(double x, double y)
{
	t_point *new_point;

	new_point = malloc(sizeof(t_point *));
	new_point->x = x;
	new_point->y = y;
	print_point("new point made with value: ", (*new_point));
	return (new_point);
}

