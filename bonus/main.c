/*
** main.c for gnl in /home/baurens/Work/Tek1/Projects/CPE/CPE_2016_getnextline/bonus/
**
** Made by John Doe
** Login   <login_x@epitech.eu>
**
** Started on  Wed Jan  4 07:33:59 2017 John Doe
** Last update Fri Jan 20 13:55:49 2017 John Doe
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int	main(int ac, char **av)
{
  int	i;
  int	j;
  int	*fd;
  char	loop;
  char	*line;

  loop = 1;
  if ((fd = malloc(sizeof(int) * ac)) == NULL)
    return (1);
  fd[ac] = 0;
  i = 0;
  while (++i < ac)
    fd[i - 1] = open(av[i], O_RDONLY);
  while (loop)
    {
      j = 0;
      loop = 0;
      while ((ac == 1 && j == 0) || fd[j] != 0)
	{
	  if ((line = get_next_line(fd[j])) != NULL)
	    {
	      loop = 1;
              printf("> %s\n", line);
              free(line);
	    }
	  j++;
	}
    }
  i = 0;
  while (fd[i] != 0)
    close(fd[i++]);
  free(fd);
  return (0);
}
