/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 01:28:19 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/03/21 21:14:47 by oscarmathot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	ft_isspace(unsigned char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (true);
	return (false);
}

void	free_double_char(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	cp_until_sp(char *str, int *pos, char **temp)
{
	int		i;

	i = 0;
	(*temp) = (char *)malloc(ft_strlen(str) + 1);
	while (str[i + (*pos)])
	{
		if (ft_isspace(str[i + (*pos)]))
		{
			(*temp)[i] = '\0';
			(*pos) = (*pos) + i;
			return ;
		}
		(*temp)[i] = str[i + (*pos)];
		i++;
	}
	(*temp)[i] = '\0';
	(*pos) = (*pos) + i;
}

int	are_letters(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122))
			return (1);
		i++;
	}
	return (0);
}

int	no_numbers(char *str, int *pos)
{
	int	i;
	int	commas;

	i = (*pos);
	commas = 0;
	while (str[(i)])
	{
		if (str[i] == ',')
			commas++;
		if ((str[i] > 57 || str[i] < 48)
			&& !ft_isspace(str[i]) && str[i] != '\0')
		{
			if (commas <= 2 && str[i] == ',')
			{
				i++;
				continue ;
			}
			return (1);
		}
		i++;
	}
	if (commas != 2)
		return (1);
	return (0);
}
