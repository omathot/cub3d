/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:52:31 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/03/23 13:48:22 by oscarmathot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

uint32_t	get_collor(int r, int g, int b, int a);
void		get_rgba(int i, mlx_image_t *to_place, t_rgba *rgb);
void		initialize_rgba(t_rgba *rgba);
void		initialize_tex_variables(t_texture_vars *vars, int cur_x);
void		determine_texture(t_texture_vars *variables,
				t_wall_info wall, t_param_mlx *param);
void		clamp_xy(t_texture_vars *variables,
				double wall_height, t_param_mlx *param, t_wall_info wall);

void	write_line(t_param_mlx *param, int i, int *j, char **to_return)
{
	int	k;

	k = 0;
	while (param->map.file_data[i][(*j)])
	{
		(*to_return)[k] = param->map.file_data[i][(*j)];
		(*j)++;
		k++;
	}
	(*to_return)[k] = '\0';
}

char	*get_data_line(t_param_mlx *param, char x)
{
	static char	*to_return = NULL;
	int			i;
	int			j;

	i = 0;
	if (to_return == NULL)
		to_return = (char *)malloc((ft_strlen(
						param->map.file_data[i]) * 2) + 1);
	while (param->map.file_data[i])
	{
		j = 0;
		if (param->map.file_data[i][j] == x)
		{
			while (!(ft_isspace(param->map.file_data[i][j])))
				j++;
			j++;
			write_line(param, i, &j, &to_return);
		}
		i++;
	}
	return (to_return);
}

//point.y = screen_hight. point.x = screen_x
void	place_wall_slice(t_texture_vars *variables,
	double wall_height, t_param_mlx *param, t_rgba rgba)
{
	int	y;

	y = 0;
	while (y < variables->y_diff)
	{
		if (floor((*variables).start_y + y) >= param->y_resolution
			|| floor((*variables).start_y + y) < 0)
		{
			y++;
			continue ;
		}
		(*variables).texture_y = (int)((y / (wall_height
						/ variables->corrected_height) / 2)
				* variables->to_place->height);
		if (variables->texture_y < 0)
			(*variables).texture_y = 0;
		else if (variables->texture_y >= (int)variables->to_place->height)
			(*variables).texture_y = variables->to_place->height - 1;
		get_rgba((*variables).texture_y * (*variables).to_place->width
			+ (*variables).texture_x, (*variables).to_place, &rgba);
		(*variables).color = get_collor(rgba.r, rgba.g, rgba.b, 255);
		mlx_put_pixel(param->image_to_draw_pixel,
			floor(variables->cur_screen_x),
			(floor((*variables).start_y + y++)), (*variables).color);
	}
}

double	do_the_maths(t_param_mlx *param, int screen_x, double magnitude)
{
	double	angle_drift;
	double	current_angle;
	double	relative_angle;
	double	corrected_height;

	angle_drift = param->map.player.angle_view / param->x_resolution;
	current_angle = param->map.player.angle
		- (param->map.player.angle_view / 2);
	relative_angle = fabs(param->map.player.angle
			- (angle_drift * screen_x + current_angle));
	corrected_height = magnitude * cos(relative_angle * (M_PI / 180));
	corrected_height = magnitude / 3
		+ magnitude / 3 + corrected_height / 3;
	return (corrected_height);
}

void	wall_texture(t_param_mlx *param, int screen_x,
	t_wall_info wall, double wall_height)
{
	t_texture_vars	variables;
	t_rgba			rgba;

	initialize_tex_variables(&variables, screen_x);
	initialize_rgba(&rgba);
	determine_texture(&variables, wall, param);
	clamp_xy(&variables, wall_height, param, wall);
	place_wall_slice(&variables, wall_height, param, rgba);
	mlx_delete_image(param->mlx, variables.to_place);
}
