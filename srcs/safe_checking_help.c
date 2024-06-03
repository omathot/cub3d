/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_checking_help.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omathot <omathot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:00:36 by omathot           #+#    #+#             */
/*   Updated: 2024/05/01 14:07:07 by omathot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	validate_no(char *line, int cursor);
int	validate_so(char *line, int cursor);
int	validate_we(char *line, int cursor);
int	validate_ea(char *line, int cursor);

int	nothing_after_file(int *i, char *line, char *tmp)
{
	while (line[(*i)])
	{
		if (!(ft_isspace(line[(*i)])))
		{
			free(tmp);
			return (1);
		}
		(*i)++;
	}
	return (0);
}

int	validate_line(char *line)
{
	int	i;
	int	ok;

	ok = 0;
	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (i == (int)ft_strlen(line))
		return (0);
	if (ft_strlen(&(line[i])) < 8)
		return (1);
	if (line[i] == 'N')
		if (validate_no(line, i) == 1)
			ok = 1;
	if (line[i] == 'S')
		if (validate_so(line, i) == 1)
			ok = 1;
	if (line[i] == 'W')
		if (validate_we(line, i) == 1)
			ok = 1;
	if (line[i] == 'E')
		if (validate_ea(line, i) == 1)
			ok = 1;
	return (ok);
}
