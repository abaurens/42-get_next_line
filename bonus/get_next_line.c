/*
** get_next_line.c for gnl in /home/baurens/Work/Tek1/Projects/CPE/CPE_2016_getnextline/
**
** Made by Arthur Baurens
** Login   <arthur.baurens@epitech.eu>
**
** Started on  Mon Jan  2 10:17:21 2017 Arthur Baurens
** Last update Sun Jan 15 17:28:44 2017 John Doe
*/

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

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

static char	*get_fd_line(const int fd, char **sv)
{
  int		ln;
  char		eof;
  char		*line;
  char		*tmp;
  char		buff[READ_SIZE + 1];

  eof = 0;
  while ((ln = gnl_strlen(*sv, '\n')) == gnl_strlen(*sv, '\0') && !eof)
    {
      if ((ln = read(fd, buff, READ_SIZE)) < 0)
	return (NULL);
      else if (ln == 0)
	eof = 1;
      else
	{
	  buff[ln] = '\0';
	  *sv = gnl_strncat(tmp = *sv, buff, -1, 0);
	  free(tmp);
	}
    }
  line = gnl_strncat(NULL, tmp = *sv, ln, eof);
  *sv = (*sv && (*sv)[ln] ? gnl_strncat(NULL, &(*sv)[ln + 1], -1, 0) : 0);
  free(tmp);
  return (line);
}

static void	gnl_rm_from_list(t_gnl **list, t_gnl *elem)
{
  t_gnl		*tmp;

  tmp = *list;
  if (elem == *list)
    {
      *list = (*list)->next;
      free(elem);
      return ;
    }
  while (tmp && tmp->next && tmp->next != elem)
    tmp = tmp->next;
  tmp->next = tmp->next->next;
  free(elem);
}

char		*get_next_line(const int fd)
{
  t_gnl		*elem;
  char		*ret;
  static t_gnl	*gnl = NULL;

  elem = gnl;
  while (elem && elem->fd != fd)
    elem = elem->next;
  if (elem == NULL)
    {
      if ((elem = malloc(sizeof(t_gnl))) == NULL)
	return (NULL);
      elem->fd = fd;
      elem->sv = NULL;
      elem->next = gnl;
      gnl = elem;
    }
  if ((ret = get_fd_line(elem->fd, &elem->sv)) == NULL)
    gnl_rm_from_list(&gnl, elem);
  return (ret);
}
