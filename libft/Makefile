NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

FUNCTIONS = toupper tolower isalpha isdigit isalnum isascii isprint \
		strlen strchr strrchr strlcpy strlcat strncmp strnstr strdup \
		memset memcmp memcpy memmove memchr bzero calloc atoi \
		substr strjoin strtrim strmapi striteri split itoa \
		putchar_fd putstr_fd putendl_fd putnbr_fd

SOURCES = $(shell printf "ft_%s.c\n" ${FUNCTIONS})

OBJECTS = $(SOURCES:.c=.o)

FUNCTIONS_BONUS = new add_front size last add_back delone clear iter map

SOURCES_BONUS = $(shell printf "ft_lst%s_bonus.c\n" ${FUNCTIONS_BONUS})

OBJECTS_BONUS = $(SOURCES_BONUS:.c=.o)


all : $(NAME)

$(NAME) : $(OBJECTS)
	@ar -rcs $(NAME) $(OBJECTS)

bonus : $(OBJECTS_BONUS)
	@ar -rcs $(NAME) $(OBJECTS_BONUS)

clean :
	@rm -f $(OBJECTS) $(OBJECTS_BONUS)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY : all bonus clean fclean re
