
OS =		$(shell uname -s)
EXEC =		rt
SRC_NAME =	main parse mlx_init parse_obj parse_error parse_tools check_key \
			opencl filters filters2 export_bmp cel_shading hooks init_keys \
			opencl_buffers_args parse_cam parse_light parse_ambient \
			parse_plane parse_cylinder parse_sphere parse_cone parse_ellipsoid \
			parse_obj2 parse_error2 obj_error set_to_zero filters3 filters4 \
			utils
SRC =  		$(addprefix src/, $(SRC_NAME:=.c))
OBJ =		$(SRC:%.c=%.o)
LIB_PATH =	./lib/libft/
INC =		include/rt.h
CC =		gcc
FLAGS =		-Wall -Werror -Wextra -I ./include

ifeq ($(OS), Darwin)
LIB =	./lib/libft/libft.a ./lib/lib_vec/lib_vec.a ./lib/minilibx_macos/libmlx.a ./lib/libbmp/libbmp.a \
		-framework OpenGL -framework AppKit -framework OpenCL -lm
else
LIB =	./lib/libft/libft.a ./lib/lib_vec/lib_vec.a ./lib/minilibx/libmlx.a ./lib/libbmp/libbmp.a \
		-lX11 -lXext -lOpenCL -lm
endif

all: $(EXEC)

msg:
	@echo "\033[0;29m⌛  Making Project : \c"

ifeq ($(OS), Darwin)
$(EXEC): msg $(OBJ)
	@echo "\n\033[0;29m⌛  Making Libft : \c"
	@make -C lib/libft/ -j 8
	@echo "\033[0;29m⌛  Making Lib_vec : \c"
	@make -C lib/lib_vec/ -j 8
	@make -C lib/minilibx_macos/ -j 8
	@make -C lib/libbmp
	@$(CC) -o $(EXEC) $(OBJ) $(LIB)
	@echo "\033[0;34m✅  Executable created !\033[0;29m"
else
$(EXEC): msg $(OBJ)
	@echo "\n\033[0;29m⌛  Making Libft : \c"
	@make -C lib/libft/ -j 8
	@echo "\033[0;29m⌛  Making Lib_vec : \c"
	@make -C lib/lib_vec/ -j 8
	@make -C lib/minilibx/ -j 8
	@make -C lib/libbmp
	@$(CC) -o $(EXEC) $(OBJ) $(LIB)
	@echo "\033[0;34m✅  Executable created !\033[0;29m"
endif

src/%.o: src/%.c $(INC)
	@$(CC) $(FLAGS) -o $@ -c $<
	@echo "\033[0;32m.\c\033[0;29m"

clean:
	@make $@ -C $(LIB_PATH)
	@make $@ -C ./lib/lib_vec/
	@make -C ./lib/libbmp clean
	@rm -rf ./lib/minilibx/*.[ao]
	@rm -rf ./lib/minilibx_macos/*.[ao]
	@echo "\033[0;31m🔥  Cleaning Project Objects...\033[0;29m"
	@rm -rf $(OBJ)

fclean: clean
	@make $@ -C $(LIB_PATH)
	@make $@ -C ./lib/lib_vec/
	@make -C ./lib/libbmp fclean
	@echo "\033[0;31m🔥  Cleaning Project Executable...\033[0;29m"
	@rm -rf $(EXEC)

re: fclean all

.PHONY: all clean fclean re msg
