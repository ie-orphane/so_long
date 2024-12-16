NAME=so_long
LIBRARY = ./mlx_linux/libmlx_Linux.a

CC = cc
CFLAGS = -fsanitize=address -g

SOURCES = so_long.c

OBJECTS = $(SOURCES:.c=.o)

all : $(NAME)

$(NAME): $(LIBRARY) $(OBJECTS)
	$(CC) $(OBJECTS) -Lmlx_linux -lmlx_Linux -Imlx_linux -lXext -lX11 -lm -lz $(CFLAGS) -o $(NAME)

$(LIBRARY):
	@echo "making minilibx..."
	@make -C mlx_linux 1> /dev/null
	@echo "making minilibx done"

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx_linux -O3 -c $< -o $@

clean :
	@rm -f $(OBJECTS)

fclean : clean
	@rm -f $(NAME)

re : fclean all

run : $(NAME)
	@./$(NAME)

.PHONY : all clean fclean re run
