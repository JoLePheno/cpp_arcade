##
## EPITECH PROJECT, 2018
## makefile
## File description:
## 
##

NAME		= ../lib_arcade_ncurses.so

SRC		=  NCursesLib.cpp

OBJ		= $(SRC:.cpp=.o)

CXXFLAGS	+=  -fPIC -g

LDFLAGS	= -shared

$(NAME)	: $(OBJ)
	g++  $(LDFLAGS) -o $(NAME) $(OBJ) -lncurses

all	: $(NAME)

clean	:
	rm -rf $(OBJ)

fclean	: clean
	rm -rf $(NAME)

re	: fclean all

debug	:	all

redebug	:	fclean debug
