/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 23:10:11 by oscarmathot       #+#    #+#             */
/*   Updated: 2023/12/05 00:07:25 by oscarmathot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_map(char **map, int pos)
{
	int	i;
	int	j;
	int	count;

	i = pos;
	count = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) < 3)
			return (1);
		i++;
	}
	if (i < 3)
		return (1);
	i = pos;
	while (map[i])
	{
		j = 0;
		if (map[i][j] == '\0')
			return (1);
		while (map[i][j])
		{
			if (!(ft_isdigit(map[i][j])) && map[i][j] != 'N' && map[i][j] != 'S'
				&& map[i][j] != 'W' && map[i][j] != 'E' && map[i][j] != ' ')
				{
					puts("bha");
					return (1);
				}
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
				{
					j++;
					count++;
				}
			if (count > 1)
			{
				puts("kha");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
