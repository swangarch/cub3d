NAME		=	cub3D
BONUS		=	cub3D_bonus

# Directories and libraries
LIBFT		=	libft/libft.a
INC			=	includes/
INC_B		=	bonus/includes/
SRC_DIR		=	srcs/
SRC_DIR_B	=	bonus/srcs/
OBJ_DIR		=	obj/
OBJ_DIR_B	=	bonus/obj/
MLX_DIR		=	mlx_linux/
MLX_LIB		=	$(MLX_DIR)libmlx.a

# Compiler and CFlags
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
INCLUDES	=	-Iincludes -I/usr/include -Imlx -I./libft
INCLUDES_B	=	-Ibonus/includes -I/usr/include -Imlx -I./libft
FLAGS		=	-Lmlx_linux -lmlx -L/usr/lib/X11 -lXext -lX11 -lm
RM			=	rm -f

# source files
SRCS		=	$(SRC_DIR)cub3d.c \
				$(SRC_DIR)error_free.c \
				$(SRC_DIR)parse.c \
				$(SRC_DIR)parse_check.c \
				$(SRC_DIR)parse_color.c \
				$(SRC_DIR)parse_set_map.c \
				$(SRC_DIR)init_setup.c \
				$(SRC_DIR)utils.c \
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
				$(SRC_DIR)special_effect.c \
				$(SRC_DIR)draw_floor_sky.c \
				$(SRC_DIR)move.c \
				$(SRC_DIR)wall_distance.c

SRCS_B		=	$(SRC_DIR_B)cub3d_bonus.c \
				$(SRC_DIR_B)error_free_bonus.c \
				$(SRC_DIR_B)parse_bonus.c \
				$(SRC_DIR_B)parse_check_bonus.c \
				$(SRC_DIR_B)parse_color_bonus.c \
				$(SRC_DIR_B)parse_set_map_bonus.c \
				$(SRC_DIR_B)init_setup_bonus.c \
				$(SRC_DIR_B)utils_bonus.c \
				$(SRC_DIR_B)ft_math_bonus.c \
				$(SRC_DIR_B)ft_vector_bonus.c \
				$(SRC_DIR_B)draw_geo_bonus.c \
				$(SRC_DIR_B)game_control_bonus.c \
				$(SRC_DIR_B)render_game_bonus.c \
				$(SRC_DIR_B)wall_check_bonus.c \
				$(SRC_DIR_B)wall_distance_bonus.c \
				$(SRC_DIR_B)color_bonus.c \
				$(SRC_DIR_B)util_bonus.c \
				$(SRC_DIR_B)init_bonus.c \
				$(SRC_DIR_B)draw_texture_bonus.c \
				$(SRC_DIR_B)ui_bonus.c \
				$(SRC_DIR_B)update_state_bonus.c \
				$(SRC_DIR_B)special_effect_bonus.c \
				$(SRC_DIR_B)sprite_animation_bonus.c \
				$(SRC_DIR_B)draw_map_bonus.c \
				$(SRC_DIR_B)draw_floor_bonus.c \
				$(SRC_DIR_B)draw_sky_bonus.c \
				$(SRC_DIR_B)move_bonus.c

OBJS		=	$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
OBJS_B		=	$(patsubst $(SRC_DIR_B)%.c,$(OBJ_DIR_B)%.o,$(SRCS_B))

# Build rules
all:		$(NAME)
bonus:		$(BONUS)

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

$(BONUS):	$(OBJS_B) $(LIBFT) $(MLX_LIB)
		@$(CC) $(CFLAGS) $(OBJS_B) $(FLAGS) $(INCLUDES_B) \
		$(LIBFT) $(MLX_LIB) -o $(BONUS)
		@echo "Bonus Compilation success!"

$(OBJ_DIR_B)%.o:	$(SRC_DIR_B)%.c
		@mkdir -p $(@D)
		@$(CC) $(CFLAGS) $(INCLUDES_B) -c $< -o $@

clean:
		@$(RM) -r $(OBJ_DIR) $(OBJ_DIR_B)
		@make clean -C ./libft
		@make clean -C $(MLX_DIR)

fclean:		clean
		@$(RM) $(NAME)
		@$(RM) $(BONUS)
		@$(RM) $(LIBFT)
		@make clean -C $(MLX_DIR)

re:		fclean all

# Phony targets represent actions instead of files
.PHONY:		all clean fclean re bonus
