/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 12:29:37 by abaurens          #+#    #+#             */
/*   Updated: 2018/11/19 19:18:27 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "get_next_line.h"

int			main(int ac, char **av)
{
	int		i;
	int		j;
	int		fd;
	int		out;
	char	*line;

	while (++i < ac)
	{
		if (strcmp(av[i], "-") == 0)
			fd = 0;
		else if ((fd = open(av[i], O_RDONLY)) < 0)
		{
			dprintf(1, "ERROR: can't open file '%s'.\n", av[i]);
			continue;
		}
		j = 0;
		printf("File '%s'\n", av[i]);
		while ((out = get_next_line(fd, &line)) > 0)
		{
			printf("\t%3d|%s|%d\n", j++, line, out);
			free(line);
		}
		if (fd > 2)
			close(fd);
	}
	printf("============================================\nexit with %d\n", out);
}
