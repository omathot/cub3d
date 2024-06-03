/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omathot <omathot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 18:54:13 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/05/01 14:19:48 by omathot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_cell_player(char c);
int	check_updown_diagonals(char **board, int i, int j, int mode);

void	init_file_reqs(t_file_reqs **reqs)
{
	(*reqs)->no = 0;
	(*reqs)->so = 0;
	(*reqs)->we = 0;
	(*reqs)->ea = 0;
	(*reqs)->f = 0;
	(*reqs)->c = 0;
}

void	handle_escape(t_param_mlx **param)
{
	mlx_close_window((*param)->mlx);
	mlx_terminate((*param)->mlx);
	free_map(&(*param)->map);
	exit(0);
}

int	check_diagonals(char **board, int i, int j)
{
	return (board[i][j] != '1' && board[i][j]
		!= '0' && !(is_cell_player(board[i][j])));
}

int	check_1_edges(char **board, int i, int j)
{
	if (board[i - 1][j] == '1')
	{
		if (check_updown_diagonals(board, i, j, 1) == 1)
			return (1);
	}
	if (board[i + 1][j] == '1')
	{
		if (check_updown_diagonals(board, i, j, 2) == 1)
			return (1);
	}
	if (board[i][j - 1] == '1')
	{
		if (check_diagonals(board, i - 1, j - 1))
			return (1);
		if (check_diagonals(board, i + 1, j - 1))
			return (1);
	}
	if (board[i][j + 1] == '1')
	{
		if (check_diagonals(board, i - 1, j + 1))
			return (1);
		if (check_diagonals(board, i + 1, j + 1))
			return (1);
	}
	return (0);
}
