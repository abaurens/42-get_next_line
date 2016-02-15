/*
** get_next_line.c for gnl in /home/bauren_a/Work/tek-1/CPE/get_next_line
**
** Made by Arthur
** Login   <bauren_a@epitech.net>
**
** Started on  Tue Jan 12 15:12:31 2016 Arthur
** Last update Mon Feb 15 14:27:21 2016 Arthur
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"

int     sl(char *str, char c)
{
  int   i;

  i = -1;
  if (str == NULL)
    return (0);
  while (str[++i])
    if (str[i] == c)
      return (i);
  return (c == '\0' ? i : -1);
}

char    *mstc(char *str1, char *str2, int n)
{
  int	i;
  int	j;
  int	s;
  int	len;
  int	len2;
  char	*ret;

  len = sl(str1, '\0');
  len2 = sl(str2, '\0');
  s = len + len2;
  if (n < size && n != -1)
    size = n;
  if (str2 == NULL || (ret = malloc(sizeof(char) * (size + 1))) == NULL)
    return (NULL);
  i = 0;
  while (str1 != NULL && str1[i] && (n == -1 ? (1 == 1) : (i < n)))
    ret[i] = str1[i++];
  j = 0;
  while (str2[j] && (n == -1 ? (1 == 1) : (i < n)))
    ret[i++] = str2[j++];
  ret[i] = 0;
  return (ret);
}

void	*fan(void *ptr)
{
  free(ptr);
  return (NULL);
}

char	*rl(char *sv, char *buff, int s)
{
  char	*tmp;

  buffer[s] = 0;
  tmp = sv;
  sv = mstc(sv, buffer, -1);
  free(tmp);
  return (sv);
}

char		*get_next_line(const int fd)
{
  static char	*sv = NULL;
  char		*tmp;
  char		*line;
  int		l;
  int		s;
  char		buffer[READ_SIZE + 1];

  s = 0;
  l = sl(sv, '\n');
  while (l <= 0 && (s = read(fd, buffer, READ_SIZE)) > 0)
    sv = rl(sv, buffer, s);
  if (s < 0)
    return (NULL);
  if (sl(sv, '\0') == 0 && s == 0)
    return (line = fan(sv));
  else if (sv != NULL && sl(sv, '\0') != 0)
    {
      line = mstc(NULL, save, ((l == -1) ? l : l++));
      tmp = save;
      save = mstc(NULL, ((l == -1) ? NULL : &save[l]), -1);
      free(tmp);
    }
  return (line);
}
