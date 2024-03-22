/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:05:27 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/03/21 21:54:06 by oscarmathot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_visible_walls(t_point **walls)
{
	int	i;

	i = 0;
	while (walls[i])
	{
		free(walls[i]);
		i++;
	}
	free(walls);
}

void	free_locs(t_file_loc **locs)
{
	if ((*locs)->e_wall)
		free((*locs)->e_wall);
	if ((*locs)->w_wall)
		free((*locs)->w_wall);
	if ((*locs)->n_wall)
		free((*locs)->n_wall);
	if ((*locs)->s_wall)
		free((*locs)->s_wall);
}

void	free_map(t_map *map)
{
	if (map->board)
		free_double_char(map->board);
	if (map->content)
		free_double_char(map->content);
	if (map->file_data)
		free_double_char(map->file_data);
	// if (map->wall_e)
	// 	mlx_delete_texture(map->wall_e);
	// if (map->wall_w)
	// 	mlx_delete_texture(map->wall_w);
	// if (map->wall_s)
	// 	mlx_delete_texture(map->wall_s);
	// if (map->wall_n)
	// 	mlx_delete_texture(map->wall_n);
}

int	else_free_locs(t_file_loc **locs)
{
	free_locs(locs);
	return (1);
}

int	else_free_reqs(t_file_reqs **reqs)
{
	free((*reqs));
	return (1);
}