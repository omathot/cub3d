/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omathot <omathot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 17:28:37 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/02/08 15:09:06 by omathot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	input_n_file_checks(int argc, char **argv, t_map *map);
int		check_format(t_map	*map);

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
			if ((*map).board[i][k] == 'W' || (*map).board[i][k] == 'E' || (*map).board[i][k] == 'S' || (*map).board[i][k] == 'N')
			{
				printf("found player at y = (%i), x = (%i)\n", i, k);
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
				return ;
			}
			k++;
		}
		i++;
	}
	printf("OUIN OUIN ");
}

//  ./cub3d <file>
int	main(int argc, char **argv)
{
	t_map	map;

	input_n_file_checks(argc, argv, &map);
	if (check_format(&map) == 1)
	{
		// if (map.board != NULL)
		// 	free_double_char(map.board);
		write(2, "Invalid map format\n", 19);
		exit(EXIT_FAILURE);
	}
	puts("change player angle");

	save_player_data(&map);
	printf("player pos.x (%f), pos.y (%f), angle (%f)\n", map.player.pos.x, map.player.pos.y, map.player.angle);
	printf("\n");
	print_map(map.content);
	// map.player.angle = 45;
	// map.player.angle_view = 90;
	map.player.angle_view = 120;
	mlx_shit(map);
	return (0);
}
