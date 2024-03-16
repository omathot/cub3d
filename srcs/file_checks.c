/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 18:51:58 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/03/16 15:23:55 by oscarmathot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_file_reqs(t_file_reqs **reqs);
int		check_map(char **map, int pos);

int	check_nm(int *i, char *str, char **sprite_loc)
{
	char	*temp;

	(*i) += 2;
	while (ft_isspace(str[(*i)]))
		(*i)++;
	temp = cp_until_sp(str, i);
	(*sprite_loc) = temp;
	while (str[(*i)] != '\0')
	{
		if (!(ft_isspace(str[(*i)])))
		{
			free(temp);
			return (1);
		}
		(*i)++;
	}
	if (access(temp, F_OK) == -1)
	{
		free(temp);
		return (1);
	}
	return (0);
}

int	last_checks(char *str, t_file_loc **locs, int *i, t_file_reqs **check)
{
	if (str[(*i)] == 'E' && str[(*i) + 1] == 'A')
	{
		if (check_nm(i, str, &(*locs)->e_wall) == 1)
		{
			free((*locs));
			return (1);
		}
		(*check)->ea++;
	}
	else
	{
		free((*locs));
		return (1);
	}
	return (0);
}

int	other_checks(char *str, t_file_loc **locs, int *i, t_file_reqs **check)
{
	if (str[(*i)] == 'S' && str[(*i) + 1] == 'O')
	{
		if (check_nm(i, str, &(*locs)->s_wall) == 1)
		{
			free((*locs));
			return (1);
		}
		(*check)->so++;
	}
	else if (str[(*i)] == 'W' && str[(*i) + 1] == 'E')
	{
		if (check_nm(i, str, &(*locs)->w_wall) == 1)
		{
			free((*locs));
			return (1);
		}
		(*check)->we++;
	}
	else if (last_checks(str, locs, i, check) == 1)
		return (1);
	return (0);
}

int	check_texture(char *str, int *i, t_file_reqs **check)
{
	t_file_loc	*locs;
	int			len;

	locs = (t_file_loc *)malloc(sizeof(t_file_loc));
	printf("(%s)\n", str);
	len = ft_strlen(str);
	if ((*i) + 2 < len)
	{
		if (str[(*i)] == 'N' && str[(*i) + 1] == 'O')
		{
			if (check_nm(i, str, &locs->n_wall) == 1)
			{
				free(locs);
				return (1);
			}
			(*check)->no++;
		}
		else if (other_checks(str, &locs, i, check) == 1)
			return (1);
	}
	else
		return (1);
	free(locs);
	return (0);
}

void	set_cnf_reqs(char ref, t_file_reqs **reqs)
{
	if (ref == 'C')
		(*reqs)->c++;
	else if (ref == 'F')
		(*reqs)->f++;
}

int	check_cnf(char *str, int *i, t_file_reqs **reqs, char ref)
{
	char	**nbrs;
	int		j;

	(*i) += 1;
	while (str[(*i)])
	{
		j = 0;
		while (ft_isspace(str[(*i)]))
			(*i)++;
		if (no_numbers(str, i) == 1)
			return (1);
		nbrs = ft_split(&str[(*i)], ',');
		while (nbrs[j])
		{
			if (ft_atoi(nbrs[j]) > 255 || ft_atoi(nbrs[j]) < 0)
			{
				free_double_char(nbrs);
				return (1);
			}
			j++;
		}
		(*i)++;
	}
	set_cnf_reqs(ref, reqs);
	return (0);
}

int	check_line(char *str, t_file_reqs **reqs)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
	{
		if (check_texture(str, &i, reqs) == 1)
			return (1);
	}
	else if (str[i] == 'C' || str[i] == 'F')
	{
		if (check_cnf(str, &i, reqs, str[i]) == 1)
			return (1);
	}
	else if (ft_isdigit(str[i]))
		return (2);
	else
		return (1);
	return (0);
}

int	check_reqs(t_file_reqs *reqs)
{
	if (reqs->c != 1 || reqs->ea != 1 || reqs->f != 1 || reqs->no != 1
		|| reqs->so != 1 || reqs->we != 1)
		return (1);
	else if (reqs->c == 1 || reqs->ea == 1 || reqs->f == 1 || reqs->no == 1
		|| reqs->so == 1 || reqs->we == 1)
		return (2);
	return (0);
}

char	**make_board(char **content, int start)
{
	int		i;
	char	**to_return;

	i = 0;
	while (content[start + i])
		i++;
	to_return = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (content[start + i])
	{
		to_return[i] = ft_strdup(content[start + i]);
		i++;
	}
	to_return[i] = NULL;
	return (to_return);
}

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
	while (index >= 0)
	{
		if (longest < (int)ft_strlen(content[index]))
			longest = ft_strlen(content[index]);
		index--;
	}
	index = start;
	to_return = (char **)malloc(sizeof(char *) * (6 + 1));
	while (i < 6)
	{
		to_return[i] = (char *)malloc(sizeof(char) * (longest + 1));
		if (to_return[i] != NULL)
			to_return[i][0] = '\0';
		i++;
	}
	fetch_filedata(content, index, &to_return);
	i = 0;
	while (to_return[i])
	{
		printf("fetched data = (%s)\n", to_return[i]);
		i++;
	}
	return (to_return);
}

int	final_format_check(t_file_reqs *reqs, t_map *map, int i)
{
	if (check_reqs(reqs) == 1)
		return (1);
	if (check_map((*map).content, i) == 1)
		return (1);
	return (0);
}

int	check_format(t_map *map)
{
	int			i;
	int			res;
	t_file_reqs	*reqs;

	reqs = (t_file_reqs *)malloc(sizeof(t_file_reqs));
	i = 0;
	init_file_reqs(&reqs);
	while ((*map).content[i])
	{
		res = check_line((*map).content[i], &reqs);
		if (res == 1)
		{
			free(reqs);
			return (1);
		}
		else if (res == 2)
		{
			(*map).board = make_board((*map).content, i);
			(*map).file_data = make_filedata((*map).content, i);
			break ;
		}
		i++;
	}
	final_format_check(reqs, map, i);
	return (0);
}
