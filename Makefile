NAME=so_long

# Compiler and flags
CC = cc
CFLAGS = -O3 -Wall -Wextra -Werror

# Source and object files
SOURCES_DIR = sources
SOURCES_FILE = so_long.c events.c map.c utils.c dict.c image.c frames.c
SOURCES = $(addprefix $(SOURCES_DIR)/,$(SOURCES_FILE))

OBJECTS_DIR = objects
OBJECTS = $(addprefix $(OBJECTS_DIR)/,$(SOURCES_FILE:.c=.o))

INCLUDES_DIR = includes
INCLUDES_FILE = so_long.h image.h dict.h
INCLUDES = $(addprefix $(INCLUDES_DIR)/,$(INCLUDES_FILE))

# Library directories and its files
LIB_DIRS = ft_printf libft
LIB_FILES = ft_printf/libftprintf.a libft/libft.a

# Library flags
LIB_PATHS =  -Lft_printf -Llibft -L/usr/local/lib
LIBS =  -lftprintf -lft -lmlx_Linux
INCLUDE_PATHS := -I$(INCLUDES_DIR) -I/usr/local/include -Ift_printf -Ilibft

LIB_FLAGS = $(LIB_PATHS) $(LIBS) -lXext -lX11 -lm $(INCLUDE_PATHS)


all : $(NAME)

$(LIB_FILES):
	@for dir in $(LIB_DIRS); do \
		echo "Building library in $$dir..."; \
		$(MAKE) -C $$dir 1> /dev/null; \
	done

$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.c
	@mkdir -p $(OBJECTS_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE_PATHS) -O3 -c $< -o $@

$(NAME): $(LIB_FILES) $(OBJECTS)
	@echo "new compile"
	@$(CC) $(OBJECTS) $(LIB_FLAGS)  -fsanitize=address -g3 -o $(NAME) 

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

TEST = test
TEST_SOURCES = test.c
TEST_OBJECTS = $(TEST_SOURCES:.c=.o)

$(TEST): $(LIB_FILES) $(TEST_OBJECTS)
	@$(CC) $(TEST_OBJECTS) $(LIB_FLAGS) -lXext -lX11 -lm -lz -o $(TEST)

trun: $(TEST)
	@./$(TEST)

.PHONY : all clean fclean re run test
