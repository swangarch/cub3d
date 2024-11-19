#include "../includes/cub3d.h"

void	start_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		//free
		map_error(MES_MLX_INIT_ERR);
	}
	game->win = mlx_new_window(game->mlx, game->win_w, \
		game->win_h, "Cub3d");
	if (!game->win)
	{
		//free
		free(game->mlx);
		map_error(MES_NEW_WIN_ERR);
	}
}
