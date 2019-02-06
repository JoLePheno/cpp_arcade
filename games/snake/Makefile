##
## EPITECH PROJECT, 2018
## makefile
## File description:
## 
##

NAME		= ../lib_arcade_nibbler.so

SRC		=  	Snake.cpp	\

OBJ		=	$(SRC:.cpp=.o)

CXXFLAGS	+= 	-fPIC -g

LDFLAGS	=	-shared

$(NAME)	: $(OBJ)
	g++  $(LDFLAGS) -o $(NAME) $(OBJ)

all	: $(NAME)

clean	:
	rm -rf $(OBJ)

fclean	: clean
	rm -rf $(NAME)

re	:	fclean all
