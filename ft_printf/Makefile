NAME=libftprintf.a
LIBRARY=ftprintf

CC = cc
CFLAGS = -Wall -Wextra -Werror

FILES = printf put utils

SOURCES = $(shell printf "ft_%s.c\n" ${FILES})

OBJECTS = $(SOURCES:.c=.o)

all : $(NAME)

$(NAME) : $(OBJECTS)
	@ar -rcs $(NAME) $(OBJECTS)

clean :
	@rm -f $(OBJECTS)

fclean : clean
	@rm -f $(NAME)

re : fclean all

run : $(NAME)
	@$(CC)  main.c -L. -l$(LIBRARY) -o $(LIBRARY) && ./$(LIBRARY)
	@rm -f $(LIBRARY)

.PHONY : all clean fclean re run
