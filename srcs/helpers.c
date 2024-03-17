/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 01:28:19 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/03/13 17:27:07 by oscarmathot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

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
}

char	*cp_until_sp(char *str, int *pos)
{
	int		i;
	char	*final;

	i = 0;
	final = (char *)malloc(ft_strlen(str) + 1);
	while (str[i + (*pos)])
	{
		if (ft_isspace(str[i + (*pos)]))
		{
			final[i] = '\0';
			(*pos) = (*pos) + i;
			return (final);
		}
		final[i] = str[i + (*pos)];
		i++;
	}
	final[i] = '\0';
	(*pos) = (*pos) + i;
	return (final);
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
	return (0);
}
