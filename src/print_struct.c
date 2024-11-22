#include "../includes/cub3d.h"

void	print_game_info(t_game game)
{
	printf("win_w == %d\n", game.win_w);
	printf("win_h == %d\n", game.win_h);
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
	printf("Color of floor: %d,%d,%d\n")//
}
