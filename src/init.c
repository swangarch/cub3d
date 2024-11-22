#include "../includes/cub3d.h"

void	init_game(t_game *game)
{
	int	i;

	i = 0;
	game->win_h = 1920;
	game->win_w = 1080;
	game->mlx = NULL;
	game->win = NULL;
	game->num_player = 0;
	game->map = NULL;
	while (i < LEN_TEX)
		game->tex_path[i++] = NULL;
	i = 0;
	while (i < LEN_TYPE)
		game->set[i++] = 0;
}
