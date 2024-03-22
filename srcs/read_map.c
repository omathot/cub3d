/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omathot <omathot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 18:51:12 by oscarmathot       #+#    #+#             */
/*   Updated: 2024/03/22 10:40:37 by omathot          ###   ########.fr       */
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
		{
			free(content);
			exit(write(2, "Error while reading\n", 20));
		}
		ft_memcpy(content + content_size, buffer, bytes_read);
		content_size += bytes_read;
	}
	close(fd);
	content[content_size] = '\0';
	return (content);
}

char    **split_cub3d(char *str, char c);

void	input_n_file_checks(int argc, char **argv, t_map *map)
{
	int		len;
	char	*content;

	if (argc != 2)
		exit(write(2, "wrong number of arguments\n", 26));
	if (access(argv[1], F_OK) == -1)
		exit(write(2, "File does not exist\n", 20));
	len = ft_strlen(argv[1]);
	if (len < 5)
		exit(write(2, "Invalid filename\n", 17));
	if (argv[1][len - 4] != '.' || argv[1][len - 3] != 'c'
		|| argv[1][len - 2] != 'u' || argv[1][len - 1] != 'b')
		exit(write(2, "Not a .cub file\n", 16));
	content = get_map(argv);
	(*map).content = split_cub3d(content, '\n');
	free(content);
}
