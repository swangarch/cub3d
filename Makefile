NAME		=	cub3D

# Directories and libraries
LIBFT		=	lib/libft/libft.a
INC			=	include/
SRC_DIR		=	src/
OBJ_DIR		=	obj/
MLX_DIR		=	mlx/
MLX_LIB		=	$(MLX_DIR)libmlx.a

# Compiler and CFlags
CC			=	cc
# CFLAGS		=	-Wall -Wextra -Werror
INCLUDES	=	-Iincludes -I/usr/include -Imlx
MLX_FLAGS	=	-Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
RM			=	rm -f

# source files
SRCS		=	$(SRC_DIR)cub3d.c \
				$(SRC_DIR)error_free.c \
				$(SRC_DIR)parse.c \
				$(SRC_DIR)init.c \
				$(SRC_DIR)utils.c \
				$(SRC_DIR)print_struct.c

OBJS		=	$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

# Build rules
all:		$(NAME)

$(LIBFT):
		@make -sC ./lib/libft

$(MLX_LIB):
		@make -sC $(MLX_DIR)

$(NAME):	$(OBJS) $(LIBFT) $(MLX_LIB)
		@$(CC) $(CFLAGS) $(MLX_FLAGS) $(INCLUDES) $(OBJS) \
		$(LIBFT) $(MLX_LIB) -o $(NAME)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
		@mkdir -p $(@D)
		@$(CC) $(CFLAGS) -Iinclude -Imlx -c $< -o $@

clean:
		@$(RM) -r $(OBJ_DIR)
		@make clean -C ./lib/libft
		@make clean -C $(MLX_DIR)

fclean:		clean
		@$(RM) $(NAME)
		@$(RM) $(LIBFT)
		@make clean -C $(MLX_DIR)

re:		fclean all

# Phony targets represent actions instead of files
.PHONY:		all clean fclean re
