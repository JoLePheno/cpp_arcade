##
## EPITECH PROJECT, 2018
## makefile
## File description:
## 
##

NAME		= ../lib_arcade_sfml.so

SRC		=  SFML.cpp

OBJ		= $(SRC:.cpp=.o)

CXXFLAGS	+=  -fPIC -g

LDFLAGS	= -shared -lsfml-graphics

$(NAME)	: $(OBJ)
	g++ $(LDFLAGS) -o $(NAME) $(OBJ)

all	: $(NAME)

clean	:
	rm -rf $(OBJ)

fclean	: clean
	rm -rf $(NAME)

re	:	fclean all

debug	:	all

redebug	:	fclean debug
