##
## Makefile for gnl in /home/baurens/Work/Tek1/Projects/CPE/CPE_2016_getnextline/bonus/
##
## Made by John Doe
## Login   <login_x@epitech.eu>
##
## Started on  Wed Jan  4 07:39:29 2017 John Doe
## Last update Wed Jan  4 07:40:54 2017 John Doe
##

CC		=	gcc

NAME	=	gnl_test

SRC		=	main.c get_next_line.c

OBJ		=	$(SRC:.c=.o)

INCLUDE	=	-I./include

CFLAGS	+=	$(INCLUDE) -g -W -Wall -Wextra -Werror -ansi -pedantic

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ)

all:	$(NAME)

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
