##
## EPITECH PROJECT, 2021
## CPP_theplazza_2020
## File description:
## makefile
##

MAKE		=	make
RM			=	-@rm -rf
CC			=	clang++
PREFIX		=	src/

FILES		=	main.cpp					\
				trade.cpp

SRC			=	$(addprefix $(PREFIX), $(FILES))

OBJ			=	$(SRC:.cpp=.o)

CPPFLAGS	=	-I./include/
CFLAGS		=	-Wextra -W -Wall

NAME		=	trade

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CPPFLAGS) $(CFLAGS)

vg:	CFLAGS += -g3
vg:	all

clean:
	$(RM) $(OBJ) vg*

fclean:	clean
	$(RM) $(NAME) vg*

re:	fclean all

.PHONY:	all clean fclean vg re
