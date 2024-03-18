/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:16:06 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/03/18 15:16:15 by oscarmathot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
