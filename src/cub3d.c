#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	// static const char *map[] =
	// {
    // 	"111111",
    // 	"100001",
    // 	"100P01",
    // 	"100001",
    // 	"111111",
	// };
	if (argc == 1)
		map_error(MES_NO_MAP_ERR);
	else if (argc > 2)
		map_error(MES_TOO_MANY_ARG_ERR);
	else if (argc == 2 && check_map_name(argv[1]))
		map_error(MES_WRONG_NAME_ERR);
	init_game(&game);
	if (parse_map(&game, argv[1]))
		map_error(MES_INVALD_MAP_ERR);
	// init_game(&game, (char **)map);
	start_game(&game);
	// mlx_hook(game.win, KEY_PRESS_CHECK, 1L << 0, key_handler, (void *)&game);
	// mlx_hook(game.win, DESTROY_CLICK, 1L << 0, end_program, (void *)&game);
	mlx_loop_hook(game.mlx, update, (void *)&game);
	mlx_loop(game.mlx);
	return (0);
}
