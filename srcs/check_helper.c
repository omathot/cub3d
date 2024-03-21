/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:16:06 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/03/21 21:47:05 by oscarmathot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		else_free_locs(t_file_loc **locs);
void	free_locs(t_file_loc **locs);
void	cp_until_sp(char *str, int *pos, char **temp);

int	check_nm(int *i, char *str, char **sprite_loc)
{
	char	*temp;

	(*i) += 2;
	while (ft_isspace(str[(*i)]))
		(*i)++;
	cp_until_sp(str, i, &temp);
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
	free(temp);
	return (0);
}

int	last_checks(char *str, t_file_loc **locs, int *i, t_file_reqs **check)
{
	if (str[(*i)] == 'E' && str[(*i) + 1] == 'A')
	{
		if (check_nm(i, str, &(*locs)->e_wall) == 1)
		{
			free_locs(locs);
			return (1);
		}
		(*check)->ea++;
	}
	else
	{
		free_locs(locs);
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

// changed for free, if error here it's related to else_free()
int	check_texture(char *str, int *i, t_file_reqs **check)
{
	t_file_loc	*locs;
	int			len;

	locs = (t_file_loc *)malloc(sizeof(t_file_loc));
	len = ft_strlen(str);
	if ((*i) + 2 < len)
	{
		if (str[(*i)] == 'N' && str[(*i) + 1] == 'O')
		{
			if (check_nm(i, str, &locs->n_wall) == 1)
				return (free(locs), 1);
			(*check)->no++;
		}
		else if (other_checks(str, &locs, i, check) == 1)
			return (free(locs), 1);
	}
	else
		return (free(locs), 1);
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
