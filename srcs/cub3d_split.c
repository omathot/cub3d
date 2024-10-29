/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 08:51:04 by omathot           #+#    #+#             */
/*   Updated: 2024/03/25 22:05:16 by oscarmathot      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_longest(char *str, char c)
{
	int	i;
	int	len;
	int	count;

	len = 0;
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			if (len < count)
				len = count;
			count = 0;
		}
		i++;
		count++;
	}
	return (len);
}

void	init_array(char *str, char c, char ***to_return)
{
	int	i;
	int	rows;
	int	count;

	i = 0;
	count = 0;
	rows = 0;
	while (str[i])
	{
		if (str[i] == c)
			rows++;
		i++;
	}
	if (str[i - 1] != '\n')
		rows++;
	i = 0;
	count = get_longest(str, c);
	(*to_return) = (char **)malloc(sizeof(char *) * (rows + 2));
	while (i < rows)
	{
		(*to_return)[i] = (char *)malloc(sizeof(char *) * (count + 1));
		i++;
	}
}

char	**split_cub3d(char *str, char c)
{
	int		i;
	int		k;
	int		j;
	char	**to_return;

	i = 0;
	k = 0;
	j = 0;
	init_array(str, c, &to_return);
	while (str[i])
	{
		while (str[i] != c && str[i])
			to_return[k][j++] = str[i++];
		if (str[i] == c || str[i] == '\0')
		{
			to_return[k++][j] = '\0';
			j = 0;
			if (str[i] == '\0')
				break ;
		}
		if (str[i] != '\0')
			i++;
	}
	to_return[k] = NULL;
	return (to_return);
}
