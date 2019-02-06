CC	= g++

RM	= rm -f

DIRS	= NCurses SDL SFML

all:
	for dir in $(DIRS); do \
	$(MAKE) -C $$dir; \
	done

clean:
	$(RM) *.so

fclean: clean

re: fclean all