NAME		=	cub3D

# Directories and libraries
LIBFT		=	libft/libft.a
INC			=	include/
SRC_DIR		=	srcs/
OBJ_DIR		=	obj/
MLX_DIR		=	mlx_linux/
MLX_LIB		=	$(MLX_DIR)libmlx.a

# Compiler and CFlags
CC			=	cc
# CFLAGS		=	-Wall -Wextra -Werror
INCLUDES	=	-Iincludes -I/usr/include -Imlx -I./libft
FLAGS		=	-Lmlx_linux -lmlx -L/usr/lib/X11 -lXext -lX11 -lm
RM			=	rm -f

# source files
SRCS		=	$(SRC_DIR)cub3d.c \
				$(SRC_DIR)error_free.c \
				$(SRC_DIR)parse.c \
				$(SRC_DIR)init_setup.c \
				$(SRC_DIR)utils.c \
				$(SRC_DIR)print_struct.c \
				$(SRC_DIR)ft_math.c \
				$(SRC_DIR)ft_vector.c \
				$(SRC_DIR)draw_geo.c \
				$(SRC_DIR)game_control.c \
				$(SRC_DIR)render_game.c \
				$(SRC_DIR)wall_check.c \
				$(SRC_DIR)color.c \
				$(SRC_DIR)util.c \
				$(SRC_DIR)init.c \
				$(SRC_DIR)draw_texture.c \
				$(SRC_DIR)ui.c \
				$(SRC_DIR)update_state.c \
				$(SRC_DIR)special_effect.c \
				$(SRC_DIR)sprite_animation.c \
				$(SRC_DIR)draw_map.c



OBJS		=	$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

# Build rules
all:		$(NAME)

$(LIBFT):
		@make -sC ./libft
		@echo "Libft compilation success!"

$(MLX_LIB):
		@make -sC $(MLX_DIR)

$(NAME):	$(OBJS) $(LIBFT) $(MLX_LIB)
		@$(CC) $(CFLAGS) $(OBJS) $(FLAGS) $(INCLUDES) \
		$(LIBFT) $(MLX_LIB) -o $(NAME)
		@echo "Compilation success!" 

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
		@mkdir -p $(@D)
		@$(CC) $(CFLAGS) -Iinclude -Imlx -c $< -o $@

clean:
		@$(RM) -r $(OBJ_DIR)
		@make clean -C ./libft
		@make clean -C $(MLX_DIR)

fclean:		clean
		@$(RM) $(NAME)
		@$(RM) $(LIBFT)
		@make clean -C $(MLX_DIR)

re:		fclean all

# Phony targets represent actions instead of files
.PHONY:		all clean fclean re
