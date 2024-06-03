/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_checking.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omathot <omathot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:26:33 by omathot           #+#    #+#             */
/*   Updated: 2024/05/01 14:00:59 by omathot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	nothing_after_file(int *i, char *line, char *tmp);

int	validate_tmp_string(char *tmp, int i)
{
	int	k;

	k = i;
	if (access(tmp, F_OK) == -1)
	{
		free(tmp);
		return (1);
	}
	if (ft_strlen(tmp) < 6)
	{
		free(tmp);
		return (1);
	}
	if (tmp[k - 1] == 'g' || tmp[k - 1] == 'G')
		if (tmp[k - 2] == 'n' || tmp[k - 2] == 'N')
			if (tmp[k - 3] == 'p' || tmp[k - 3] == 'P')
				if (tmp[k - 4] == '.')
					return (free(tmp), 0);
	return (1);
}

int	validate_no(char *line, int cursor)
{
	int		i;
	int		k;
	char	*tmp;

	i = cursor;
	k = 0;
	tmp = NULL;
	if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
	{
		tmp = (char *)malloc(ft_strlen(line) + 1);
		i += 2;
		while (ft_isspace(line[i]))
			i++;
		while (!(ft_isspace(line[i])) && line[i])
			tmp[k++] = line[i++];
		tmp[k] = '\0';
		if (nothing_after_file(&i, line, tmp) == 1)
			return (1);
		if (validate_tmp_string(tmp, k) == 0)
			return (0);
	}
	return (1);
}

int	validate_so(char *line, int cursor)
{
	int		i;
	int		k;
	char	*tmp;

	i = cursor;
	k = 0;
	tmp = NULL;
	if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
	{
		tmp = (char *)malloc(ft_strlen(line) + 1);
		i += 2;
		while (ft_isspace(line[i]))
			i++;
		while (!(ft_isspace(line[i])) && line[i])
			tmp[k++] = line[i++];
		tmp[k] = '\0';
		if (nothing_after_file(&i, line, tmp) == 1)
			return (1);
		if (validate_tmp_string(tmp, k) == 0)
			return (0);
	}
	return (1);
}

int	validate_we(char *line, int cursor)
{
	int		i;
	int		k;
	char	*tmp;

	i = cursor;
	k = 0;
	tmp = NULL;
	if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
	{
		tmp = (char *)malloc(ft_strlen(line) + 1);
		i += 2;
		while (ft_isspace(line[i]))
			i++;
		while (!(ft_isspace(line[i])) && line[i])
			tmp[k++] = line[i++];
		tmp[k] = '\0';
		if (nothing_after_file(&i, line, tmp) == 1)
			return (1);
		if (validate_tmp_string(tmp, k) == 0)
			return (0);
	}
	return (1);
}

int	validate_ea(char *line, int cursor)
{
	int		i;
	int		k;
	char	*tmp;

	i = cursor;
	k = 0;
	tmp = NULL;
	if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
	{
		tmp = (char *)malloc(ft_strlen(line) + 1);
		i += 2;
		while (ft_isspace(line[i]))
			i++;
		while (!(ft_isspace(line[i])) && line[i])
			tmp[k++] = line[i++];
		tmp[k] = '\0';
		if (nothing_after_file(&i, line, tmp) == 1)
			return (1);
		if (validate_tmp_string(tmp, k) == 0)
			return (0);
	}
	return (1);
}
