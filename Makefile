NAME=so_long

# Compiler and flags
CC = cc
CFLAGS = -fsanitize=address -g

# Source and object files
SOURCES = so_long.c
OBJECTS = $(SOURCES:.c=.o)

# Library directories and its dependencies
LIB_DIRS = mlx_linux ft_printf
LIB_DEPENDENCIES = mlx_linux/libmlx_Linux.a ft_printf/libftprintf.a

# Library flags
LIB_PATHS = -Lmlx_linux -Lft_printf
LIBS = -lmlx_Linux -lftprintf
INCLUDE_PATHS = -Imlx_linux -Ift_printf

LIB_FLAGS = $(LIB_PATHS) $(LIBS) $(INCLUDE_PATHS)


all : $(NAME)

$(NAME): $(LIB_FILES) $(OBJECTS)
	@$(CC) $(OBJECTS) $(LIB_FLAGS) -lXext -lX11 -lm -lz $(CFLAGS) -o $(NAME)

$(LIB_FILES):
	@for dir in $(LIB_DIRS); do \
		echo "Building library in $$dir..."; \
		$(MAKE) -C $$dir 1> /dev/null; \
	done

%.o: %.c
	@$(CC) -Wall -Wextra -Werror -Imlx_linux -O3 -c $< -o $@

clean :
	@rm -f $(OBJECTS)
	@for dir in $(LIB_DIRS); do \
		echo "Cleaning library in $$dir..."; \
		$(MAKE) -C $$dir clean 1> /dev/null; \
	done

fclean : clean
	@rm -f $(NAME)

re : fclean all

run : $(NAME)
	@./$(NAME)

.PHONY : all clean fclean re run
