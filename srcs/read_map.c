/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omathot <omathot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 18:51:12 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/02/08 15:09:04 by omathot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*get_map(char **argv)
{
	int		fd;
	int		bytes_read;
	int		content_size;
	char	*content;
	char	*buffer[BUFFER_SIZE];

	bytes_read = 1;
	content_size = 0;
	content = (char *)malloc(BUFFER_SIZE);
	if (!content)
		exit(write(2, "failed content malloc\n", 22));
	fd = open(argv[1], O_RDONLY);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			exit(write(2, "Error while reading\n", 20));
		ft_memcpy(content + content_size, buffer, bytes_read);
		content_size += bytes_read;
	}
	close(fd);
	content[content_size] = '\0';
	return(content);
}

// int	check_prev_line(char *content, int start)
// {
// 	int	i;

// 	i = 1;
// 	while (content[start - i] != '\n')
// 		i++;
// 	while (ft_isspace(content[start - i]))
// 		i--;
// 	if (content[start - i] == 'S' || content[start - i] == 'N' || content[start - i] == 'W' || content[start - i] == 'E' || content[start - i] == 'C' || content[start - i] == 'F')
// 		return (1);
// 	else if (content[start - i] == ' ' || ft_isdigit(content[start - i]))
// 		return (0);
// }

void	input_n_file_checks(int argc, char **argv, t_map *map)
{
	int	len;
	char	*content;

	if (argc != 2)
		exit(write(2, "wrong number of arguments\n", 26));
	if (access(argv[1], F_OK) == -1)
		exit(write(2, "File does not exist\n", 20));
	len = ft_strlen(argv[1]);
	if (len < 5)
		exit(write(2, "Invalid filename\n", 17));
	if (argv[1][len - 4] != '.' || argv[1][len - 3] != 'c' || argv[1][len - 2] != 'u' || argv[1][len - 1] != 'b')
		exit(write(2, "Not a .cub file\n", 16));
	content = get_map(argv);
	// len = ft_strlen(content);
	// len--;
	// while (len > 0)
	// {
	// 	while (ft_isdigit(content[len]) || content[len] == 'N' || content[len] == 'S' || content[len] == 'W' || content[len] == 'E' || content[len] == ' ' || content[len] == '\n')
	// 	{
	// 		if (content[len] == '\n')
	// 		{
	// 			if (content[len - 1] == '\n' || check_prev_line(content, len))
	// 				break ; // found start of map
	// 		}
	// 		len--;
	// 	}
	// 	if (!(ft_isdigit(content[len]) && content[len] != 'N' && content[len] != 'S'
	// 		&& content[len] != 'W' && content[len] != 'E' && content[len] != ' ' && content[len] != '\n'))
	// 		// {
	// 		// 	free(content);
	// 		// 	exit(write(2, "Invalid map\n", 12));

	// 		// }
	// 		break ; // err404
	// 	if (len >= 2)
	// 		if (content[len] == '\n' && content[len - 1] == '\n')
	// 		{
	// 			free(content);
	// 			exit(write(2, "Invalid map\n", 12));
	// 		}
	// 	len--;
	// }
	(*map).content = ft_split(content, '\n');
	free(content);
	// return (content);
}