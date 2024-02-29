/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 17:28:37 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/02/10 15:33:28 by oscarmathot      ###   ########.fr       */
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

// void	initialize_board(t_map	*map)
// {

// }


int check_map_walls(char **board);

//  ./cub3d <file>
int	main(int argc, char **argv)
{
	t_map	map;
	// t_param_mlx *param_mlx;

	input_n_file_checks(argc, argv, &map);
	// initialize_board(&map);
	if (check_format(&map) == 1 || check_map_walls(map.board) == 1)
	{
		free_double_char(map.board);
		write(2, "Invalid map format\n", 19);
		exit(EXIT_FAILURE);
	}
  save_player_data(&map);
	printf("player pos.x (%f), pos.y (%f), angle (%f)\n", map.player.pos.x, map.player.pos.y, map.player.angle);
	print_map(map.board);
	view_walls(map, 1080);
	map.player.angle_view = 180;
	// param_mlx = malloc(sizeof(t_param_mlx));
	// pause();
	// mlx_t   *mlx;
	// mlx = mlx_init(1080,720, "main_window", false);
	// param_mlx->image_to_draw_pixel = mlx_new_image(mlx, 1080,720);
	// if (!mlx)
	// 	exit(1);
	// param_mlx->mlx = mlx;
	mlx_shit(map);
	// mlx_loop_hook(mlx, player_move, param_mlx);
	// mlx_loop(mlx);
	return (0);
}
