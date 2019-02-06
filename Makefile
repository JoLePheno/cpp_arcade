NAME	= arcade

CC	= g++

RM	= rm -f

SRCS	= ./main.cpp \
	  ./src/Core.cpp \
	  ./src/TextBox.cpp	\
	  ./src/PixelBox.cpp \
	  ./src/Color.cpp

OBJS	= $(SRCS:.cpp=.o)

LDFLAGS = -ldl
CPPFLAGS = -I./include
CPPFLAGS += -W -Wall -Wextra -g

all: $(NAME)

$(NAME): core graphicals game

core:	$(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS) -rdynamic

graphicals:
	$(MAKE) -C lib

game:
	$(MAKE) -C games

clean:
	$(RM) $(OBJS)
	$(MAKE) -C games clean
	$(MAKE) -C lib clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C games fclean
	$(MAKE) -C lib fclean

re: fclean all

.PHONY: all clean fclean re core graphicals game