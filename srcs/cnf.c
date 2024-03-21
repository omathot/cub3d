/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cnf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 16:22:53 by oscar             #+#    #+#             */
/*   Updated: 2024/03/21 19:34:16 by oscarmathot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

uint32_t	get_collor(int r, int g, int b, int a);
// void		get_rgba(int i, mlx_image_t *to_place, int *r, int *g, int *b);
char		*get_data_line(t_param_mlx *param, char x);

void	make_floor_ceil(t_param_mlx *param_real)
{
	int	x;
	int	y;

	y = 0;
	while (y < param_real->y_resolution)
	{
		x = 0;
		while (x < param_real->x_resolution)
		{
			if (y > param_real->y_resolution / 2)
				mlx_put_pixel(param_real->image_to_draw_pixel, x, y,
					get_collor(param_real->map.ceil_rgb->r,
						param_real->map.ceil_rgb->g,
						param_real->map.ceil_rgb->b, 255));
			else
				mlx_put_pixel(param_real->image_to_draw_pixel, x, y,
					get_collor(param_real->map.floor_rgb->r,
						param_real->map.floor_rgb->g,
						param_real->map.floor_rgb->b, 255));
			x++;
		}
		y++;
	}
}

char	*return_at_comma(int x, char *str)
{
	int	i;
	int	comma_counter;

	i = 0;
	comma_counter = 0;
	while (str[i])
	{
		if (str[i] == ',')
		{
			comma_counter++;
			if (comma_counter == x)
				return (&str[i + 1]);
		}
		i++;
	}
	puts("big data problem");
	pause();
	return (NULL);
}

int	get_rgb__data(t_param_mlx *param, char f_c, char rgb)
{
	if (f_c == 'f')
	{
		if (rgb == 'r')
			return (ft_atoi(get_data_line(param, 'F')));
		else if (rgb == 'g')
			return (ft_atoi(return_at_comma(1, get_data_line(param, 'F'))));
		else
			return (ft_atoi(return_at_comma(2, get_data_line(param, 'F'))));
	}
	else
	{
		if (rgb == 'r')
			return (ft_atoi(get_data_line(param, 'C')));
		else if (rgb == 'g')
			return (ft_atoi(return_at_comma(1, get_data_line(param, 'C'))));
		else
			return (ft_atoi(return_at_comma(2, get_data_line(param, 'C'))));
	}
}

void	save_ceil_floor_rgb(t_param_mlx *param)
{
	int	temp;

	(param)->map.ceil_rgb = (t_rgba *)malloc(sizeof(t_rgba));
	temp = get_rgb__data(param, 'c', 'r');
	(param)->map.ceil_rgb->r = temp;
	temp = get_rgb__data(param, 'c', 'g');
	(param)->map.ceil_rgb->g = temp;
	temp = get_rgb__data(param, 'c', 'b');
	(param)->map.ceil_rgb->b = temp;
	(param)->map.floor_rgb = (t_rgba *)malloc(sizeof(t_rgba));
	temp = get_rgb__data(param, 'f', 'r');
	(param)->map.floor_rgb->r = temp;
	temp = get_rgb__data(param, 'f', 'g');
	(param)->map.floor_rgb->g = temp;
	temp = get_rgb__data(param, 'f', 'b');
	(param)->map.floor_rgb->b = temp;
}
