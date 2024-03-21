/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge_verification.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:19:06 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/03/18 15:20:24 by oscarmathot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_updown_player(char **board, int i, int j, int mode)
{
	if (mode == 1)
	{
		if (board[i + 1][j] != 'N' && board[i + 1][j] != 'S'
					&& board[i + 1][j] != 'E'
					&& board[i + 1][j] != 'W')
			return (1);
	}
	if (mode == 2)
	{
		if (board[i - 1][j] != 'N' && board[i - 1][j] != 'S'
				&& board[i - 1][j] != 'E'
				&& board[i - 1][j] != 'W')
			return (1);
	}
	return (0);
}

int	is_player(char **board, int i, int j, int mode)
{
	if (mode == 1)
	{
		if (board[i][j - 1] != 'N' && board[i][j - 1] != 'S'
				&& board[i][j - 1] != 'E'
				&& board[i][j - 1] != 'W')
			return (1);
	}
	if (mode == 2)
	{
		if (board[i][j + 1] != 'N' && board[i][j + 1] != 'S'
				&& board[i][j + 1] != 'E'
				&& board[i][j + 1] != 'W')
			return (1);
	}
	if (mode == 3)
	{
		if (check_updown_player(board, i, j, 1) == 1)
			return (1);
	}
	if (mode == 4)
	{
		if (check_updown_player(board, i, j, 2) == 1)
			return (1);
	}
	return (0);
}

int	check_updown_diagonals(char **board, int i, int j, int mode)
{
	if (mode == 1)
	{
		if (board[i - 1][j - 1] != '1' && board[i - 1][j - 1] != '0')
			return (1);
		if (board[i - 1][j + 1] != '1' && board[i - 1][j + 1] != '0')
			return (1);
	}
	if (mode == 2)
	{
		if (board[i + 1][j - 1] != '1' && board[i + 1][j - 1] != '0')
			return (1);
		if (board[i + 1][j + 1] != '1' && board[i + 1][j + 1] != '0')
			return (1);
	}
	return (0);
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
		if (board[i - 1][j - 1] != '1' && board[i - 1][j - 1] != '0')
			return (1);
		if (board[i + 1][j - 1] != '1' && board[i + 1][j - 1] != '0')
			return (1);
	}
	if (board[i][j + 1] == '1')
	{
		if (board[i - 1][j + 1] != '1' && board[i - 1][j + 1] != '0')
			return (1);
		if (board[i + 1][j + 1] != '1' && board[i + 1][j + 1] != '0')
			return (1);
	}
	return (0);
}

int	check_context(char **board, int i, int j)
{
	if (check_1_edges(board, i, j) == 1)
		return (1);
	if (board[i][j - 1] != '1' && board[i][j - 1]
			!= '0' && is_player(board, i, j, 1) == 1)
		return (1);
	if (board[i][j + 1] != '1' && board[i][j + 1]
			!= '0' && is_player(board, i, j, 2) == 1)
		return (1);
	if (board[i + 1])
	{
		if (j > (int)ft_strlen(board[i + 1]))
			return (1);
		if (board[i + 1][j] != '1' && board[i + 1][j]
				!= '0' && is_player(board, i, j, 3) == 1)
			return (1);
	}
	if (board[i - 1][j] != '1' && board[i - 1][j] != '0'
			&& is_player(board, i, j, 4) == 1)
		return (1);
	return (0);
}
