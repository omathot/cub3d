/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filedata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omathot <omathot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:11:49 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/05/01 14:07:00 by omathot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_end_map(char *str);
int	validate_line(char *line);

void	add_line(char **content, char ***to_return, t_point_int data, int *j)
{
	int	cursor;
	int	k;

	cursor = 0;
	k = (*j);
	while (!(ft_isspace(content[data.x][k])))
	{
		(*to_return)[data.y][cursor] = content[data.x][k];
		cursor++;
		k++;
	}
	while (ft_isspace(content[data.x][k]))
		k++;
	(*to_return)[data.y][cursor] = ' ';
	cursor++;
	while (!(ft_isspace(content[data.x][k])) && content[data.x][k])
	{
		(*to_return)[data.y][cursor] = content[data.x][k];
		cursor++;
		k++;
	}
	(*to_return)[data.y][cursor] = '\0';
}

void	add_fnc(char **content, char ***to_return, t_point_int data, int j)
{
	int	cursor;
	int	k;

	cursor = 0;
	k = j;
	while (!(ft_isspace(content[data.x][k])))
	{
		(*to_return)[data.y][cursor] = content[data.x][k];
		cursor++;
		k++;
	}
	while (ft_isspace(content[data.x][k]))
		k++;
	(*to_return)[data.y][cursor] = ' ';
	cursor++;
	while (content[data.x][k])
	{
		if (!(ft_isspace(content[data.x][k])))
		{
			(*to_return)[data.y][cursor] = content[data.x][k];
			cursor++;
		}
		k++;
	}
	(*to_return)[data.y][cursor] = '\0';
}

void	fetch_filedata(char **content, int index, char ***to_return)
{
	int	j;

	j = 0;
	while (index >= 0)
	{
		j = 0;
		while (ft_isspace(content[index][j]))
			j++;
		if (content[index][j] == 'N')
			add_line(content, to_return, mk_point_int(index, 0), &j);
		if (content[index][j] == 'S')
			add_line(content, to_return, mk_point_int(index, 1), &j);
		if (content[index][j] == 'E')
			add_line(content, to_return, mk_point_int(index, 2), &j);
		if (content[index][j] == 'W')
			add_line(content, to_return, mk_point_int(index, 3), &j);
		if (content[index][j] == 'F')
			add_fnc(content, to_return, mk_point_int(index, 4), j);
		if (content[index][j] == 'C')
			add_fnc(content, to_return, mk_point_int(index, 5), j);
		index--;
	}
	(*to_return)[6] = NULL;
}

char	**make_filedata(char **content, int start)
{
	char	**to_return;
	int		i;
	int		index;
	int		longest;

	i = 0;
	index = start;
	longest = ft_strlen(content[index]);
	to_return = NULL;
	while (index >= 0)
	{
		if (validate_line(content[index]) == 1)
			return (NULL);
		if (longest < (int)ft_strlen(content[index]))
			longest = ft_strlen(content[index]);
		index--;
	}
	index = start;
	to_return = (char **)malloc(sizeof(char *) * (6 + 1));
	while (i < 6)
		to_return[i++] = (char *)malloc(sizeof(char) * (longest + 1));
	fetch_filedata(content, index, &to_return);
	return (to_return);
}

char	**make_board(char **content, int start)
{
	int		i;
	char	**to_return;

	i = 0;
	while (content[start + i])
		i++;
	if (i < 3)
		return (NULL);
	to_return = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (content[start + i])
	{
		if (check_end_map(content[start + i]))
			break ;
		to_return[i] = ft_strdup(content[start + i]);
		i++;
	}
	to_return[i] = NULL;
	return (to_return);
}
