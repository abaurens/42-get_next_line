/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_multifd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 16:19:23 by abaurens          #+#    #+#             */
/*   Updated: 2018/11/19 19:48:16 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "get_next_line.h"

int			main(const int ac, char **av)
{
	int		i;
	char	lp;
	int		fd[ac - 1];
	char	f_d[ac - 1];
	char	*line;

	i = 0;
	while (++i < ac)
	{
		f_d[i - 1] = 1;
		if (strcmp(av[i], "-") == 1)
			fd[i - 1] = 0;
		else
		{
			printf("file '%s'", av[i]);
			fd[i - 1] = open(av[i], O_RDONLY);
			printf(" is fd %d\n", fd[i - 1]);
		}
	}
	lp = 1;
	while (lp)
	{
		lp = 0;
		i = 0;
		while (++i < ac)
		{
			if (f_d[i - 1])
			{
				if (get_next_line(fd[i - 1], &line))
				{
					printf("> %s\n", line);
					free(line);
				}
				else
				{
					f_d[i - 1] = 0;
					if (fd[i - 1] > 3)
						close(fd[i - 1]);
				}
				lp = 1;
			}
		}
		printf("\n");
	}
	return (0);
}
