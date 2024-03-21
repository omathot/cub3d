/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgba.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:39:13 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/03/18 15:39:40 by oscarmathot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// Get the red channel
int	get_r(int rgba)
{
	return ((rgba >> 24) & 0xFF);
}

// Get the green channel
int	get_g(int rgba)
{
	return ((rgba >> 16) & 0xFF);
}

// Get the blue channel.
int	get_b(int rgba)
{
	return ((rgba >> 8) & 0xFF);
}

void	get_rgba(int i, mlx_image_t *to_place, t_rgba *rgb)
{
	int	rgba;

	rgba = (to_place->pixels[i * 4] << 24) | (to_place->pixels[i * 4 + 1] << 16)
		| (to_place->pixels[i * 4 + 2] << 8) | (to_place->pixels[i * 4 + 3]);
	(*rgb).r = get_r(rgba);
	(*rgb).g = get_g(rgba);
	(*rgb).b = get_b(rgba);
}
