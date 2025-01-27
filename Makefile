BLACK = \033[30m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
WHITE = \033[37m
RESET = \033[0m

NAME = so_long
BONUS = bonus


CC = cc
CFLAGS = -O3 -Wall -Wextra -Werror


SOURCES_DIR = sources

_SOURCES = main.c utils.c map.c image.c \
			hooks.c tiles.c check.c read.c
SOURCES = $(addprefix $(SOURCES_DIR)/,$(_SOURCES_BONUS))

_SOURCES_BONUS = main_bonus.c events_bonus.c map_bonus.c utils.c image.c \
			frames_bonus.c layers_bonus.c animate_bonus.c check_bonus.c ground_bonus.c \
			tiles_bonus.c read.c random.c
SOURCES_BONUS = $(addprefix $(SOURCES_DIR)/,$(_SOURCES_BONUS))

OBJECTS_DIR = objects
OBJECTS = $(addprefix $(OBJECTS_DIR)/,$(_SOURCES:.c=.o))
OBJECTS_BONUS = $(addprefix $(OBJECTS_DIR)/,$(_SOURCES_BONUS:.c=.o))


INCLUDES_DIR = includes
_INCLUDES = image.h utils.h libs.h sprite.h main.h \
		main_bonus.h sprite_bonus.h random.h
INCLUDES = $(addprefix $(INCLUDES_DIR)/,$(_INCLUDES))


LIB_DIRS = ft_printf libft
LIB_FILES = ft_printf/libftprintf.a libft/libft.a

LIB_PATHS =  -Lft_printf -Llibft
LIBS =  -lftprintf -lft -lmlx_Linux -lXext -lX11 -lm
INCLUDE_PATHS := -I$(INCLUDES_DIR) -Ift_printf -Ilibft

LIB_FLAGS = $(LIB_PATHS) $(LIBS) $(INCLUDE_PATHS) # -fsanitize=address -g3


all : $(NAME)

$(LIB_FILES):
	@echo "🏗️  $(MAGENTA)$(LIB_DIRS)$(RESET)"
	@for dir in $(LIB_DIRS); do \
		$(MAKE) -C $$dir 1> /dev/null; \
	done

$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJECTS_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE_PATHS) -O3 -c $< -o $@
	@echo "🔨 $(BLUE)$(notdir $<) $(BLACK)=> $(CYAN)$(notdir $@)$(RESET)"

$(NAME): $(LIB_FILES) $(OBJECTS)
	@echo "🔗 $(CYAN)$(notdir $(OBJECTS)) $(BLACK)=> $(YELLOW)$(NAME)$(RESET)"
	@$(CC) $(OBJECTS) $(LIB_FLAGS) -o $(NAME)


$(BONUS): $(LIB_FILES) $(OBJECTS_BONUS)
	@echo "🔗 $(CYAN)$(notdir $(OBJECTS_BONUS)) $(BLACK)=> $(YELLOW)$(NAME)$(RESET)"
	@touch $(BONUS)
	@$(CC) $(OBJECTS_BONUS) $(LIB_FLAGS) -o $(NAME)

clean :
	@echo "🗑  $(BLACK)$(LIB_DIRS)$(RESET)"
	@for dir in $(LIB_DIRS); do \
		$(MAKE) -C $$dir clean 1> /dev/null; \
	done
	@echo "🧹 $(BLACK)$(OBJECTS_DIR)$(RESET)"
	@rm -rf $(OBJECTS_DIR)

fclean : clean
	@echo "🧹 $(BLACK)$(NAME)$(RESET)"
	@rm -f $(NAME) $(LIB_FILES) $(BONUS)

re : fclean all

.PHONY : all clean fclean re
