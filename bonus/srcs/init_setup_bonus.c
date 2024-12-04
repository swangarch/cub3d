#include "../includes/cub3d_bonus.h"

void	init_game(t_game *game)
{
	int	i;

	if (!game)
		return ;
	i = 0;
	game->color_c = 0;
	game->color_f = 0;
	game->num_player = 0;
	game->map = NULL;
	while (i < LEN_TEX)
		game->tex_path[i++] = NULL;
	i = 0;
	while (i < LEN_TYPE)
		game->set[i++] = 0;
}
