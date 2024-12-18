NAME = libdict.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

FUNCTIONS = add find clear

SOURCES = $(shell printf "dict_%s.c\n" ${FUNCTIONS})

OBJECTS = $(SOURCES:.c=.o)


all : $(NAME)

$(NAME) : $(OBJECTS)
	@ar -rcs $(NAME) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -I../libft -c $< -o $@

clean :
	@rm -f $(OBJECTS) $(OBJECTS_BONUS)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
