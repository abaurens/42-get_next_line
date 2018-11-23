/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaurens <abaurens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 16:56:42 by abaurens          #+#    #+#             */
/*   Updated: 2018/11/23 02:12:24 by abaurens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

static int			ft_idxof(const char *str, char c)
{
	int				i;

	i = 0;
	while (str && str[i] && str[i] != c)
		i++;
	return (i);
}

static char			*ft_gnlcat(const char *s1, const char *s2, int n)
{
	int				i;
	int				len;
	char			*res;

	i = 0;
	if ((len = ft_idxof(s1, 0) + ft_idxof(s2, 0)) > n && n >= 0)
		len = n;
	if (!(res = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	res[len] = 0;
	while (s1 && *s1 && i < len)
		res[i++] = *s1++;
	while (s2 && *s2 && i < len)
		res[i++] = *s2++;
	return (res);
}

static int			ft_fd_line(const int fd, char **line, char **save)
{
	char			buff[BUFF_SIZE + 1];
	char			*tmp;
	int				l;
	int				n;

	while ((l = ft_idxof(*save, '\n')) == ft_idxof(*save, 0))
	{
		if ((n = read(fd, buff, BUFF_SIZE)) < 0)
			return (-1);
		if (n == 0)
			break ;
		buff[n] = 0;
		if (!(tmp = ft_gnlcat(*save, buff, -1)))
			return (-1);
		free(*save);
		*save = tmp;
	}
	tmp = *save;
	if (tmp && !(*line = ft_gnlcat(NULL, tmp, l)))
		return (-1);
	n = (tmp && tmp[l] == '\n' && ++l);
	*save = ((tmp && tmp[l]) ? ft_gnlcat(0x0, tmp + l, -1) : 0x0);
	free(tmp);
	return (n || *save != NULL);
}

static void			ft_gnl_del(t_gnl **lst, t_gnl *to_rm)
{
	t_gnl			*cur;

	if (*lst == to_rm)
		*lst = (*lst)->next;
	else
	{
		cur = *lst;
		while (cur && cur->next && cur->next != to_rm)
			cur = cur->next;
		if (cur->next == to_rm)
		{
			cur->next = to_rm->next;
			free(to_rm);
		}
	}
}

int					get_next_line(const int fd, char **line)
{
	static t_gnl	*lst = NULL;
	t_gnl			*cur;
	int				ret;

	cur = lst;
	while (cur && cur->fd != fd)
		cur = cur->next;
	if (!cur)
	{
		if (!(cur = malloc(sizeof(t_gnl))))
			return (-1);
		cur->fd = fd;
		cur->sv = NULL;
		cur->next = lst;
		lst = cur;
	}
	if ((ret = ft_fd_line(cur->fd, line, &cur->sv)) == 0)
		ft_gnl_del(&lst, cur);
	return (ret);
}
