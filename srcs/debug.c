#include "../cub3d.h"

char	**debug_copy(char **board)
{
	char	**to_return;
	int	i;
	int	j;
	int	len;

	len = 0;
	i = 0;
	while (board[i])
		i++;
	to_return = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (board[i])
	{
		len = ft_strlen(board[i]);
		to_return[i] = (char *)malloc(len + 1);
		i++;
	}
	i = 0;
	while (board[i])
	{
		j = 0;
		while (board[i][j])
		{
			if (ft_isspace(board[i][j]))
				to_return[i][j] = ' ';
			else
				to_return[i][j] = '0';
			j++;
		}
		to_return[i][j] = '\0';
		i++;
	}
	to_return[i] = NULL;
	return (to_return);
}