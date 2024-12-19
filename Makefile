NAME=so_long

# Compiler and flags
CC = cc

# Source and object files
SOURCES = so_long.c so_long_events.c map.c utils.c dict.c
OBJECTS = $(SOURCES:.c=.o)

# Library directories and its files
LIB_DIRS = mlx_linux ft_printf libft
LIB_FILES = mlx_linux/libmlx_Linux.a ft_printf/libftprintf.a libft/libft.a

# Library flags
LIB_PATHS = -Lmlx_linux -Lft_printf -Llibft
LIBS = -lmlx_Linux -lftprintf -lft
INCLUDE_PATHS = -Imlx_linux -Ift_printf -Ilibft

LIB_FLAGS = $(LIB_PATHS) $(LIBS) $(INCLUDE_PATHS)


all : $(NAME)

$(NAME): $(LIB_FILES) $(OBJECTS)
	@$(CC) $(OBJECTS) $(LIB_FLAGS) -lXext -lX11 -lm -lz -o $(NAME)

$(LIB_FILES):
	@for dir in $(LIB_DIRS); do \
		echo "Building library in $$dir..."; \
		$(MAKE) -C $$dir 1> /dev/null; \
	done

%.o: %.c
	@$(CC) -Wall -Wextra -Werror $(INCLUDE_PATHS) -O3 -c $< -o $@

clean :
	@rm -f $(OBJECTS)
	@for dir in $(LIB_DIRS); do \
		echo "Cleaning library in $$dir..."; \
		$(MAKE) -C $$dir clean 1> /dev/null; \
	done

fclean : clean
	@rm -f $(NAME) $(LIB_FILES)

re : fclean all

run : $(NAME)
	@./$(NAME)

.PHONY : all clean fclean re run
