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


int check_spaces(char **map);

int handle_uneven_lines(char **board)
{
  int i;
  int diff;
  size_t len;

  i = 0;
  diff = 0;
  printf("Handling uneven lines\n");
  while (board[i])
  {
    len = ft_strlen(board[i]) - 1;
    if (board[i + 1] != NULL)
    {
      if (ft_strlen(board[i + 1]) - 1 != len && ft_strlen(board[i + 1]) != 0)
      {
        if (len > ft_strlen(board[i + 1]) - 1)
        {
          diff = (len - ft_strlen(board[i + 1]) - 1);
          while (diff != 0)
          {
            if (board[i][ft_strlen(board[i + 1]) - 1 + diff] != '1')
              return (1);
            diff--;
          }
        }
        if (len < ft_strlen(board[i + 1]) - 1)
        {
          diff = ft_strlen(board[i + 1]) - 1 - len;
          while (diff != 0)
          {
            if (board[i + 1][ft_strlen(board[i]) - 1 + diff] != '1')
            return (1);
          diff--;
          }
        }
      }
    }
    i++;
  }
  return (0);
}

int check_map_walls(char **board)
{
  int i;
  int j;
  int rows;
  int length;
  int decrement;

  i = 0;
  rows = 0;
  while (board[rows])
    rows++;
  rows--;
  while (board[i])
  {
    j = 0;
    length = ft_strlen(board[i]) - 1;
    printf("j = (%i), length = (%i)\n", j, length);
    decrement = ft_strlen(board[i]) - 1;
    while (board[i][j])
    {
      while (ft_isspace(board[i][j]))
        j++;
      if (j == 0 || i == 0 || i == rows)
      {
        if (board[i][j] != '1' && board[i][j] != ' ')
          return (1);
      }
      if (j == length)
      {
        if (board[i][j] != '1' && board[i][j] != ' ')
          return (1);
        while (ft_isspace(board[i][decrement]))
          decrement--;
        if (board[i][decrement] != '1')
          return (1);
      }
      j++;
    }
    i++;
  }
  if (handle_uneven_lines(board) == 1)
    return (1);
  if (check_spaces(board) == 1)
    return (1);
  return (0);
}

int check_spaces(char **map)
{
  int i;
  int j;
  int rows;

  i = 1;
  rows = 1;
  while (map[rows])
    rows++;
  rows -= 2;
  printf("Checking spaces\n");
  while (i <= rows)
  {
    j = 0;
    while (map[i][j])
    {
      while (ft_isspace(map[i][j]))
        j++;
      while (map[i][j] && map[i][j] != ' ')
        j++;
      if (map[i][j] == ' ')
      {
        if (map[i][j - 1] != '1')
          return (1);
        // if (map[i - 1] && (i - 1) > 0)
        // {
        //   if (map[i - 1][j] != '1' || map[i - 1][j] != ' ')
        //     return (1);
        // }
        while (ft_isspace(map[i][j]))
        {
          if (map[i - 1] && (i - 1) > 0)
          {
            if (map[i - 1][j] != '1' && map[i - 1][j] != ' ')
              return (1);
          }
          if (map[i + 1] && (i + 1) <= rows)
          {
            if (map[i + 1][j] != '1' && map[i + 1][j] != ' ')
              return (1);
          }
          j++;
        }
        if (map[i][j] != '1')
          return (1);
      }
    }
    i++;
  }
  return (0);
}

int check_map(char **map, int pos)
{
  int i;
  int j;
  int count;

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
      if (!(ft_isdigit(map[i][j])) && map[i][j] != 'N' && map[i][j] != 'S' &&
          map[i][j] != 'W' && map[i][j] != 'E' && map[i][j] != ' ')
        return (1);
      if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' ||
          map[i][j] == 'E')
      {
        j++;
        count++;
      }
      if (count > 1)
        return (1);
      j++;
    }
    i++;
  }
  return (0);
}
