
LIB =		libft.a
SRC_NAME =	ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
			ft_isdigit.c ft_isprint.c ft_memccpy.c ft_memchr.c ft_memcmp.c \
			ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar.c ft_putstr.c \
			ft_strcat.c ft_strcpy.c ft_strchr.c ft_strdup.c ft_strlcat.c \
			ft_strlen.c ft_strncat.c ft_strcmp.c ft_strncmp.c ft_strncpy.c \
			ft_strnstr.c ft_strrchr.c ft_strstr.c ft_toupper.c ft_tolower.c \
			ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c \
			ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c \
			ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c \
			ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c \
			ft_lstmap.c ft_islower.c ft_isupper.c ft_swap.c ft_tabnew.c \
			ft_tabzero.c ft_bsort.c ft_qsort.c ft_display_file.c ft_abs.c \
			get_next_line.c ft_mapping.c ft_cpytocc.c ft_sqrt.c ft_atoi_base.c \
			ft_atof.c ft_isnumber.c ft_isspace.c ft_isequal.c
SRC =		$(addprefix src/, $(SRC_NAME))
OBJ =		$(SRC:.c=.o)
INC =		./include/libft.h
CC =		gcc
FLAGS = 	-Wall -Werror -Wextra -I ./include

all: $(LIB)

$(LIB): $(OBJ)
	@ar rcs $(LIB) $(OBJ)
	@ranlib $(LIB)
	@echo "\n\033[0;34m✅  Libft Created !\033[0;29m"

%.o: %.c $(INC)
	@$(CC) $(FLAGS) -o $@ -c $<
	@echo "\033[0;32m.\c"

clean:
	@rm -f $(OBJ)

fclean: clean
	@echo "\033[0;31m🔥  Cleaning Libft Objects..."
	@echo "\033[0;31m🔥  Cleaning Libft Library...\033[0;29m"
	@rm -f $(LIB)

re: fclean all

.PHONY: all clean fclean re
