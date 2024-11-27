/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:51:45 by shuwang           #+#    #+#             */
/*   Updated: 2024/11/22 14:51:46 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d.h"



void cub3d(t_game *game)
{
    t_vars vars;

    // char **map = game->map;
    init_vars(&vars, game);
    // vars.map = map;
    // load_all_texture(&vars);
    //render_game(&vars);

    mlx_hook(vars.win, 6, (1L << 6), mouse_move, &vars);
    mlx_hook(vars.win, 2, (1L << 0), key_press, &vars);
    mlx_hook(vars.win, 3, (1L << 1), key_release, &vars);
    mlx_hook(vars.win, 17, 0, cross_press, &vars);
    mlx_loop_hook(vars.mlx, update_frame, &vars);
    mlx_loop(vars.mlx);
    //free()
}

int main(int argc, char **argv)
{
    t_game	game;

	if (argc == 1)
		map_error(MES_NO_MAP_ERR);
	else if (argc > 2)
		map_error(MES_TOO_MANY_ARG_ERR);
	else if (argc == 2 && check_map_name(argv[1]))
		map_error(MES_WRONG_NAME_ERR);
	init_game(&game);
	if (parse_map(&game, argv[1]))
		map_error(MES_INVALD_MAP_ERR);//free game!!!
    //errorchecking
    //parsing
    cub3d(&game);
    return (0);
}
