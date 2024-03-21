/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 23:10:11 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/03/21 21:00:20 by oscarmathot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_spaces(char **map);
int	check_context(char **board, int i, int j);
int	check_enclosure(char **map, int *j, int i, int rows);
int	check_map_walls(char **board);

int	verify_edges(char **board, int *j, int rows, int i)
{
	int	decrement;
	int	length;

	decrement = ft_strlen(board[i]) - 1;
	length = ft_strlen(board[i]) - 1;
	while (ft_isspace(board[i][(*j)]))
		(*j)++;
	if ((*j) == 0 || i == 0 || i == rows)
	{
		if (board[i][(*j)] != '1' && board[i][(*j)] != ' ')
			return (1);
	}
	if ((*j) == length)
	{
		if (board[i][(*j)] != '1' && board[i][(*j)] != ' ')
			return (1);
		while (ft_isspace(board[i][decrement]))
			decrement--;
		if (board[i][decrement] != '1')
			return (1);
	}
	return (0);
}

int	handle_fun_cases(char **board)
{
	int	i;
	int	j;

	i = 1;
	while (board[i])
	{
		j = 0;
		while (board[i][j])
		{
			if (board[i][j] == '0')
			{
				if (check_context(board, i, j) == 1)
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_characters(char **map, int *j, int i, int *count)
{
	if (!(ft_isdigit(map[i][(*j)])) && map[i][(*j)] != 'N'
		&& map[i][(*j)] != 'S' &&
		map[i][(*j)] != 'W' && map[i][(*j)] != 'E' && map[i][(*j)] != ' ')
		return (1);
	if (map[i][(*j)] == 'N' || map[i][(*j)] == 'S' || map[i][(*j)] == 'W' ||
		map[i][(*j)] == 'E')
	{
		printf("found player");
		(*count)++;
	}
	(*j)++;
	return (0);
}

int	check_dimensions(char **map, int *i)
{
	while (map[(*i)])
	{
		if (ft_strlen(map[(*i)]) < 3)
			return (1);
		(*i)++;
	}
	if ((*i) < 3)
		return (1);
	return (0);
}

int	check_map(char **map, int pos)
{
	int	i;
	int	j;
	int	count;

	i = pos;
	count = 0;
	if (check_dimensions(map, &i) == 1)
		return (1);
	i = pos;
	while (map[i])
	{
		j = 0;
		if (map[i][j] == '\0')
			return (1);
		while (map[i][j])
		{
			if (check_characters(map, &j, i, &count) == 1)
				return (1);
		}
		i++;
	}
	if (count > 1 || count == 0)
	{
		printf("count check = %i\n", count);
		return (1);
	}
	return (0);
}
