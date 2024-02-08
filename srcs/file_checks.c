/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omathot <omathot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 18:51:58 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/02/08 15:09:05 by omathot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_file_reqs(t_file_reqs **reqs);
int	check_map(char **map, int pos);

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

int	check_texture(char *str, int *i, t_file_reqs **check)
{
	t_file_loc	*locs;
	int		len;

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
		else if (str[(*i)] == 'S' && str[(*i) + 1] == 'O')
		{
			if (check_nm(i, str, &locs->s_wall) == 1)
			{
				free(locs);
				return (1);
			}
			(*check)->so++;
		}
		else if (str[(*i)] == 'W' && str[(*i) + 1] == 'E')
		{
			if (check_nm(i, str, &locs->w_wall) == 1)
			{
				free(locs);
				return (1);
			}
			(*check)->we++;
		}
		else if (str[(*i)] == 'E' && str[(*i) + 1] == 'A')
		{
			if (check_nm(i, str, &locs->e_wall) == 1)
			{
				free(locs);	
				return (1);
			}
			(*check)->ea++;
		}
		else
		{
			free(locs);
			return (1);
		}
	}
	else
		return (1);
	free(locs);
	return (0);
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
	if (ref == 'C')
		(*reqs)->c++;
	else if (ref == 'F')
		(*reqs)->f++;
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
	if (reqs->c != 1 || reqs->ea != 1 || reqs->f != 1
		|| reqs->no != 1 || reqs->so != 1 || reqs->we != 1)
		return (1);
	else if (reqs->c == 1 || reqs->ea == 1 || reqs->f == 1
		|| reqs->no == 1 || reqs->so == 1 || reqs->we == 1)
		return (2);
	return (0);
}


char	**make_board(char **content, int start)
{
	int	i;
	char **to_return;

	i = 0;
	while (content[start + i])
		i++;
	to_return = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (content[start  + i])
	{
		to_return[i] = ft_strdup(content[start + i]);
		i++;
	}
	to_return[i] = NULL;
	return (to_return);
}

// char	**make_filedata(char **content, int start)
// {
// 	char	**to_return;
// 	int	i;

// 	i = 0;
// 	while (content[start - i])
// 		i++;
// }

int	check_format(t_map	*map)
{
	int			i;
	int			res;
	t_file_reqs	*reqs;

	reqs = (t_file_reqs *)malloc(sizeof(t_file_reqs));
	i = 0;
	res = 0;
	init_file_reqs(&reqs);
	while ((*map).content[i])
	{
		puts("++");
		// if (check_reqs(reqs) == 2)
		// {
		// 	puts("breaking cause reqs met");
		// 	break ;
		// }
		res = check_line((*map).content[i], &reqs);
		if (res == 1)
		{
			free(reqs);
			puts("1");
			return (1);
		}
		else if (res == 2)
		{
			puts("breaking cause digit");
			(*map).board = make_board((*map).content, i);
			// (*map).file_data = make_filedata((*map).content, i);
			break ;
		}
		i++;
	}
	if (check_reqs(reqs) == 1)
	{
		puts("2");
		return (1);

	}
	if (check_map((*map).content, i) == 1)
		return (1);
	printf("reqs->ea = %i\n", reqs->ea);
	printf("reqs->we = %i\n", reqs->we);
	printf("reqs->no = %i\n", reqs->no);
	printf("reqs->so = %i\n", reqs->so);
	return (0);
}
