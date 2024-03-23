/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:21:28 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/03/23 13:39:29 by oscarmathot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	verify_edges(char **board, int *j, int rows, int i);
int	handle_fun_cases(char **board);

int	check_map_walls(char **board)
{
	int	i;
	int	j;
	int	rows;

	i = 0;
	rows = 0;
	while (board[rows])
		rows++;
	rows--;
	while (board[i])
	{
		j = 0;
		while (board[i][j])
		{
			if (verify_edges(board, &j, rows, i) == 1)
				return (1);
			j++;
		}
		i++;
	}
	if (handle_fun_cases(board) == 1)
		return (1);
	return (0);
}

int	check_enclosure(char **map, int *j, int i, int rows)
{
	while (ft_isspace(map[i][(*j)]))
		(*j)++;
	while (map[i][(*j)] && map[i][(*j)] != ' ')
		(*j)++;
	if (map[i][(*j)] == ' ')
	{
		if (map[i][(*j) - 1] != '1')
			return (1);
		while (ft_isspace(map[i][(*j)]))
		{
			if (map[i - 1] && (i - 1) > 0)
				if (map[i - 1][(*j)] != '1' && map[i - 1][(*j)] != ' ')
					return (1);
			if (map[i + 1] && (i + 1) <= rows)
				if (map[i + 1][(*j)] != '1' && map[i + 1][(*j)] != ' ')
					return (1);
			(*j)++;
		}
		if (map[i][(*j)] != '1')
			return (1);
	}
	return (0);
}

int	check_spaces(char **map)
{
	int	i;
	int	j;
	int	rows;

	i = 1;
	rows = 1;
	while (map[rows])
		rows++;
	rows -= 2;
	while (i <= rows)
	{
		j = 0;
		while (map[i][j])
		{
			if (check_enclosure(map, &j, i, rows) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}
