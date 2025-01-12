NAME = so_long

# Compiler and flags
CC = cc
CFLAGS = -O3 -Wall -Wextra -Werror

# Source and object files
SOURCES_DIR = sources

_SOURCES = main.c utils.c map.c events.c image.c
SOURCES = $(addprefix $(SOURCES_DIR)/,$(_SOURCES_BONUS))

_SOURCES_BONUS = main_bonus.c events_bonus.c map_bonus.c utils.c image.c \
			frames_bonus.c layers_bonus.c animate_bonus.c check_bonus.c ground_bonus.c \
			tiles_bonus.c
SOURCES_BONUS = $(addprefix $(SOURCES_DIR)/,$(_SOURCES_BONUS))

OBJECTS_DIR = objects
OBJECTS = $(addprefix $(OBJECTS_DIR)/,$(_SOURCES:.c=.o))
OBJECTS_BONUS = $(addprefix $(OBJECTS_DIR)/,$(_SOURCES_BONUS:.c=.o))

INCLUDES_DIR = includes
_INCLUDES = image.h utils.h libs.h sprite.h main.h \
		main_bonus.h sprite_bonus.h
INCLUDES = $(addprefix $(INCLUDES_DIR)/,$(_INCLUDES))

# Library directories and its files
LIB_DIRS = ft_printf libft
LIB_FILES = ft_printf/libftprintf.a libft/libft.a

# Library flags
LIB_PATHS =  -Lft_printf -Llibft -L/usr/local/lib
LIBS =  -lftprintf -lft -lmlx_Linux
INCLUDE_PATHS := -I$(INCLUDES_DIR) -I/usr/local/include -Ift_printf -Ilibft

LIB_FLAGS = $(LIB_PATHS) $(LIBS) -lXext -lX11 -lm $(INCLUDE_PATHS) -fsanitize=address -g3


all : $(NAME)

$(LIB_FILES):
	@for dir in $(LIB_DIRS); do \
		echo "Building library in $$dir..."; \
		$(MAKE) -C $$dir 1> /dev/null; \
	done

$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJECTS_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE_PATHS) -O3 -c $< -o $@

$(NAME): $(LIB_FILES) $(OBJECTS)
	@echo "Compiling mandatory"
	@$(CC) $(OBJECTS) $(LIB_FLAGS) -o $(NAME)
	@echo "Done"

bonus: $(LIB_FILES) $(OBJECTS_BONUS)
	@echo "Compiling bonus"
	@$(CC) $(OBJECTS_BONUS) $(LIB_FLAGS) -o $(NAME)
	@echo "Done"

clean :
	@rm -rf $(OBJECTS_DIR)
	@for dir in $(LIB_DIRS); do \
		echo "Cleaning library in $$dir..."; \
		$(MAKE) -C $$dir clean 1> /dev/null; \
	done

fclean : clean
	@rm -f $(NAME) $(LIB_FILES)

re : fclean all

.PHONY : all clean fclean re bonus 
