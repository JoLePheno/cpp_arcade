CC	= g++

RM	= rm -f

DIRS	= snake

all:
	for dir in $(DIRS); do \
	$(MAKE) -C $$dir; \
	done

clean:

fclean: clean
	$(RM) *.so

re: fclean all