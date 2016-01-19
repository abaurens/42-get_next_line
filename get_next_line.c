/*
** get_next_line.c for gnl in /home/bauren_a/Work/tek-1/CPE/get_next_line
**
** Made by Arthur
** Login   <bauren_a@epitech.net>
**
** Started on  Tue Jan 12 15:12:31 2016 Arthur
** Last update Fri Jan 15 15:58:57 2016 Arthur
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"

int     str_len(char *str)
{
  int   i;

  i = -1;
  if (str == NULL)
    return (0);
  while (str[++i] != '\0');
  return (i);
}

char    *my_strcat(char *str1, char *str2)
{
  int	i;
  int	j;
  int	len;
  int	len2;
  char	*ret;

  len = str_len(str1);
  len2 = str_len(str2);
  if (str2 == NULL || (ret = malloc(sizeof(char) * (len + len2 + 1))) == NULL)
    return (NULL);
  i = 0;
  while (str1 != NULL && str1[i] != '\0')
    ret[i] = str1[i++];
  j = 0;
  while (str2[j] != '\0')
    ret[i++] = str2[j++];
  ret[i] = 0;
  return (ret);
}

void	*free_and_null(void *ptr)
{
  free(ptr);
  return (NULL);
}

char	*load_file(const int fd)
{
  int	size[2];
  char	*result;
  char	*tmp;
  char	buffer[READ_SIZE + 1];

  result = NULL;
  size[1] = 0;
  while ((size[0] = read(fd, buffer, READ_SIZE)) > 0)
    {
      buffer[size[0]] = 0;
      tmp = result;
      if ((result = my_strcat(result, buffer)) == NULL)
	return (free_and_null(tmp));
      free(tmp);
      size[1] += size[0];
    }
  if (result != NULL)
    result[size[1]] = '\0';
  return (result);
}

char		*get_next_line(const int fd)
{
  int		i;
  char		*tmp;
  char		*line;
  static int	old_fd = -1;
  static char	*file = NULL;

  i = -1;
  if (file == NULL)
    file = load_file(fd);
  if (file == NULL)
    return (NULL);
  while (file[++i] != '\n' && file[i] != '\0');
  if ((line = malloc(sizeof(char) * i + 1)) == NULL)
    return (NULL);
  i = 0;
  while (file[i] != '\n' && file[i] != '\0')
    line[i] = file[i++];
  line[file[i] == '\0' ? i : i++] = 0;
  tmp = file;
  file = my_strcat(NULL, &file[i]);
  free(tmp);
  if (str_len(file) == 0)
    file = free_and_null(file);
  return (line);
}
