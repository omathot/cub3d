/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 23:10:11 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/03/15 15:55:48 by oscarmathot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_spaces(char **map);

int	check_line_diff2(size_t len, char **board, int i, int *diff)
{
	if (len < ft_strlen(board[i + 1]) - 1)
	{
		(*diff) = ft_strlen(board[i + 1]) - 1 - len;
		while ((*diff) != 0)
		{
			if (board[i + 1][ft_strlen(board[i]) - 1 + (*diff)] != '1')
				return (1);
			(*diff)--;
		}
	}
	return (0);
}

int	check_line_diff(size_t len, char **board, int i, int *diff)
{
	if (len > ft_strlen(board[i + 1]) - 1)
	{
		(*diff) = (len - ft_strlen(board[i + 1]) - 1);
		while ((*diff) != 0)
		{
			if (board[i][ft_strlen(board[i + 1]) - 1 + (*diff)] != '1')
				return (1);
			(*diff)--;
		}
	}
	return (0);
}

int	handle_uneven_lines(char **board)
{
	int		i;
	int		diff;
	size_t	len;

	i = 0;
	diff = 0;
	while (board[i])
	{
		len = ft_strlen(board[i]) - 1;
		if (board[i + 1] != NULL)
		{
			if (ft_strlen(board[i + 1]) - 1 != len
				&& ft_strlen(board[i + 1]) != 0)
			{
				if (check_line_diff(len, board, i, &diff) == 1)
					return (1);
				if (check_line_diff2(len, board, i, &diff) == 1)
					return (1);
			}
		}
		i++;
	}
	return (0);
}

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
	if (handle_uneven_lines(board) == 1)
		return (1);
	if (check_spaces(board) == 1)
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
			{
				if (map[i - 1][(*j)] != '1' && map[i - 1][(*j)] != ' ')
					return (1);
			}
			if (map[i + 1] && (i + 1) <= rows)
			{
				if (map[i + 1][(*j)] != '1' && map[i + 1][(*j)] != ' ')
					return (1);
			}
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

int	check_characters(char **map, int *j, int i, int *count)
{
	if (!(ft_isdigit(map[i][(*j)])) && map[i][(*j)] != 'N'
		&& map[i][(*j)] != 'S' &&
		map[i][(*j)] != 'W' && map[i][(*j)] != 'E' && map[i][(*j)] != ' ')
		return (1);
	if (map[i][(*j)] == 'N' || map[i][(*j)] == 'S' || map[i][(*j)] == 'W' ||
		map[i][(*j)] == 'E')
	{
		(*j)++;
		(*count)++;
	}
	if ((*count) > 1)
		return (1);
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
	return (0);
}
