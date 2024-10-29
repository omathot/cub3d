/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 17:28:37 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/06/03 17:32:37 by oscarmathot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	input_n_file_checks(int argc, char **argv, t_map *map);
int		check_format(t_map *map);
int		check_map_walls(char **board);

void	assign_start_angle(t_map *map, int k, int i)
{
	map->player.pos = mk_point((double)k, (double)i);
	if ((*map).board[i][k] == 'W')
		map->player.angle = 270;
	if ((*map).board[i][k] == 'E')
		map->player.angle = 90;
	if ((*map).board[i][k] == 'N')
		map->player.angle = 0;
	if ((*map).board[i][k] == 'S')
		map->player.angle = 180;
	(*map).board[i][k] = '0';
}

void	save_player_data(t_map *map)
{
	int	i;
	int	k;

	i = 0;
	while ((*map).board[i])
	{
		k = 0;
		while ((*map).board[i][k])
		{
			if ((*map).board[i][k] == 'W' || (*map).board[i][k] == 'E' ||
				(*map).board[i][k] == 'S' || (*map).board[i][k] == 'N')
			{
				assign_start_angle(map, k, i);
				return ;
			}
			k++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_map	map;

	input_n_file_checks(argc, argv, &map);
	if (check_format(&map) == 1 || check_map_walls(map.board) == 1)
	{
		free_map(&map);
		write(2, "Invalid map/file format\n", 24);
		exit(EXIT_FAILURE);
	}
	save_player_data(&map);
	map.player.angle_view = 90;
	mlx_shit(&map);
	free_map(&map);
	return (0);
}
