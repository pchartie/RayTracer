
LIB =		lib_vec.a
SRC_NAME =	normalize.c dot.c multiply_vec.c sub_vec.c add_vec.c div_vec.c \
			dot_div.c get_inters.c not_vec.c rot.c product_vec.c get_dist.c
SRC =		$(addprefix src/, $(SRC_NAME))
OBJ =		$(SRC:.c=.o)
INC =		./include/lib_vec.h
CC =		gcc
FLAGS = 	-Wall -Werror -Wextra -I ./include

all: $(LIB)

$(LIB): $(OBJ)
	@ar rcs $(LIB) $(OBJ)
	@ranlib $(LIB)
	@echo "\n\033[0;34m✅  Lib_vec Created !\033[0;29m"

%.o: %.c $(INC)
	@$(CC) $(FLAGS) -o $@ -c $<
	@echo "\033[0;32m.\c\033[0;29m"

clean:
	@rm -f $(OBJ)

fclean: clean
	@echo "\033[0;31m🔥  Cleaning Lib_vec Objects..."
	@echo "\033[0;31m🔥  Cleaning Lib_vec Library...\033[0;29m"
	@rm -f $(LIB)

re: fclean all

.PHONY: all clean fclean re
