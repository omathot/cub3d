/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samuel <samuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:34:00 by samuel            #+#    #+#             */
/*   Updated: 2024/03/21 14:34:23 by samuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

//ceil 0.5
double	round_next_clossest_half(double number)
{
	if (number < 0.0000)
	{
		return (0);
	}
	return (ceil((number) * 2) / 2);
}

//floor 0.5
double	round_clossest_half(double number)
{
	return (floor((number) * 2) / 2);
}

double	calculate_slope(t_point p1, t_point p2)
{
	return ((p2.y - p1.y) / (p2.x - p1.x));
}
