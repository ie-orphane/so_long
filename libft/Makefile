NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

SOURCES_DIR = sources
SOURCES_FILE = ft_toupper.c ft_tolower.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
		ft_isascii.c ft_isprint.c ft_strlen.c ft_strchr.c ft_strrchr.c \
		ft_strlcpy.c ft_strlcat.c ft_strncmp.c ft_strnstr.c ft_strdup.c \
		ft_memset.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memchr.c \
		ft_bzero.c ft_calloc.c ft_atoi.c ft_substr.c ft_strjoin.c \
		ft_strtrim.c ft_strmapi.c ft_striteri.c ft_split.c ft_itoa.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
		ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_ultimate_strjoin.c
SOURCES = $(addprefix $(SOURCES_DIR)/,$(SOURCES_FILE))

OBJECTS_DIR = objects
OBJECTS = $(addprefix $(OBJECTS_DIR)/,$(SOURCES_FILE:.c=.o))

all : $(NAME)

$(NAME) : $(OBJECTS)
	@ar -rcs $(NAME) $(OBJECTS)

$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJECTS_DIR)
	@$(CC) $(CFLAGS) -I. -c $< -o $@

clean :
	@rm -f $(OBJECTS) $(OBJECTS_BONUS)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
