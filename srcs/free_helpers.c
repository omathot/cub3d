/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omathot <omathot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:05:27 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/05/01 14:00:02 by omathot          ###   ########.fr       */
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
	{
		free_double_char(map->board);
		map->board = NULL;
	}
	if (map->content)
	{
		free_double_char(map->content);
		map->content = NULL;
	}
	if (map->file_data != NULL)
	{
		free_double_char(map->file_data);
		map->file_data = NULL;
	}
	if (map->ceil_rgb)
	{
		free(map->ceil_rgb);
		map->ceil_rgb = NULL;
	}
	if (map->floor_rgb)
	{
		free(map->floor_rgb);
		map->floor_rgb = NULL;
	}
}

int	else_free_locs(t_file_loc **locs)
{
	free_locs(locs);
	(*locs) = NULL;
	return (1);
}

int	else_free_reqs(t_file_reqs **reqs)
{
	free((*reqs));
	(*reqs) = NULL;
	return (1);
}
