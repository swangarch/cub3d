NAME = cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = cub3d.c ft_math.c ft_vector.c draw_geo.c game_control.c \
	render_game.c wall_check.c color.c util.c

LIBFT = ./libft

MINILIBX = ./mlx_linux

INCLUDE = -I./libft -I./header -I/usr/include -Imlx_linux

LIBS = -L./libft -lft -L./mlx_linux -lmlx -lX11 -lXext -lm

all: $(NAME)

$(NAME): $(SRCS)
	make -C $(LIBFT)
	make -C $(MINILIBX)
	$(CC) $(SRCS) $(CFLAGS) $(INCLUDE) $(LIBS) -o $(NAME)

clean:
	make clean -C $(LIBFT)

fclean:
	rm -f $(NAME)
	rm -f $(NAME_BONUS)
	make fclean -C $(LIBFT)
	make clean -C $(MINILIBX)

re:	fclean all

.PHONY: all clean fclean re
