/*
** main.c for gnl in /home/baurens/Work/Tek1/Projects/CPE/CPE_2016_getnextline/bonus/
**
** Made by John Doe
** Login   <login_x@epitech.eu>
**
** Started on  Wed Jan  4 07:33:59 2017 John Doe
** Last update Wed Jan  4 07:54:36 2017 John Doe
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
  int	fd;
  char	*line;

  i = 0;
  while (++i < ac || (ac == 1 && i == 1))
    {
      fd = ac < 2 ? 0 : open(av[i], O_RDONLY);
      while ((line = get_next_line(fd)))
	{
	  printf("%s\n", line);
	  free(line);
	}
      if (fd > 2)
	close(fd);
  }
  return (0);
}
