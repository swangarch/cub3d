#include "../includes/cub3d.h"

void	print_game_info(t_game game)
{
	int	color_r;
	int	color_g;
	int	color_b;

	// printf("floor: %d\n", game.color_f);
	// printf("ceiling: %d\n", game.color_c);
	color_r = (game.color_f >> 16) & 0xFF;
	color_g = (game.color_f >> 8) & 0xFF;
	color_b = game.color_f & 0xFF;
	printf("map_col == %d\n", game.map_col);
	printf("map_row == %d\n", game.map_row);
	printf("number of player == %d\n", game.num_player);
	int	i = 0;
	printf("This is the map!!\n");
	while (game.map[i])
	{
		printf("%s\n", game.map[i]);
		++i;
	}
	printf("This is the path of tex of wall!!\n");
	printf("Tex north: %s\n", game.tex_path[T_NORTH]);
	printf("Tex south: %s\n", game.tex_path[T_SOUTH]);
	printf("Tex west: %s\n", game.tex_path[T_WEST]);
	printf("Tex east: %s\n", game.tex_path[T_EAST]);
	printf("Color of floor: %d,%d,%d\n", color_r, color_g, color_b);
	color_r = (game.color_c >> 16) & 0xFF;
	color_g = (game.color_c >> 8) & 0xFF;
	color_b = game.color_c & 0xFF;
	printf("Color of ceiling: %d,%d,%d\n", color_r, color_g, color_b);
	printf("player_x = %lf\n", game.player_x);
	printf("player_y = %lf\n", game.player_y);
}

void	print_map_list(t_list *map_buffer)
{
	printf("print the content of map buffer\n");
	while (map_buffer)
	{
		printf("%s\n", (char *)map_buffer->content);
		map_buffer = map_buffer->next;
	}
}
