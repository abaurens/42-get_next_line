/*
** get_next_line.h for gnl in /home/baurens/Work/Tek1/Projects/CPE/CPE_2016_getnextline/
**
** Made by Arthur Baurens
** Login   <arthur.baurens@epitech.eu>
**
** Started on  Mon Jan  2 10:15:26 2017 Arthur Baurens
** Last update Wed Jan  4 07:39:07 2017 John Doe
*/

#ifndef GET_NEXT_LINE_H_
# define GET_NEXT_LINE_H_

typedef struct	s_gnl
{
  int		fd;
  char		*sv;
  struct s_gnl	*next;
}		t_gnl;

char	*get_next_line(const int);

#endif /* !GET_NEXT_LINE_H_ */

#ifndef READ_SIZE
# define READ_SIZE (5)
#endif /* !READ_SIZE */
