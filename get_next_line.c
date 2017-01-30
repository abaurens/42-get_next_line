/*
** get_next_line.c for gnl in /home/baurens/Work/Tek1/Projects/CPE/CPE_2016_getnextline/
**
** Made by Arthur Baurens
** Login   <arthur.baurens@epitech.eu>
**
** Started on  Mon Jan  2 10:17:21 2017 Arthur Baurens
** Last update Sun Jan 15 17:27:53 2017 John Doe
*/

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static int	gnl_strlen(const char *str, char c)
{
  int		i;

  i = -1;
  while (str != NULL && str[++i] && str[i] != c);
  return ((str != NULL) * i);
}

static char	*gnl_strncat(const char *s1, const char *s2, int l, char n)
{
  int		i;
  int		j;
  int		ln;
  char		*res;

  if ((ln = gnl_strlen(s1, '\0') + gnl_strlen(s2, '\0')) > l && l >= 0)
    ln = l;
  if (ln == 0 && n)
    return (NULL);
  if ((res = malloc(sizeof(char) * (ln + 1))) == NULL)
    return (NULL);
  res[ln] = '\0';
  i = 0;
  while (s1 && i < ln && s1[i])
    {
      res[i] = s1[i];
      i++;
    }
  j = -1;
  while (s2 && s2[++j] && i + j < ln)
    res[i + j] = s2[j];
  return (res);
}

char		*get_next_line(const int fd)
{
  int		ln;
  char		eof;
  char		*line;
  char		*tmp;
  char		buff[READ_SIZE + 1];
  static char	*sv = NULL;

  eof = 0;
  while ((ln = gnl_strlen(sv, '\n')) == gnl_strlen(sv, '\0') && !eof)
    {
      if ((ln = read(fd, buff, READ_SIZE)) < 0)
	return (NULL);
      else if (ln == 0)
	eof = 1;
      else
	{
	  buff[ln] = '\0';
	  sv = gnl_strncat(tmp = sv, buff, -1, 0);
	  free(tmp);
	}
    }
  line = gnl_strncat(NULL, tmp = sv, ln, eof);
  sv = (sv && sv[ln] ? gnl_strncat(NULL, &sv[ln + 1], -1, 0) : NULL);
  free(tmp);
  return (line);
}
