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

# include "cub3d.h"

void cub3d(void)
{
    t_vars vars;

    char map[9][9] = {
    "11111111",
    "1N100001",
    "10100001",
    "10000001",
    "10011111",
    "10010001",
    "10010101",
    "10000001",
    "11111111",
    };

    (&vars)->map = map;
    (&vars)->posx = 1.5;
    (&vars)->posy = 1.5;
    (&vars)->dirx = SCALE;
    (&vars)->diry = 0;

    (&vars)->mlx = mlx_init();
    (&vars)->buf_img = mlx_new_image((&vars)->mlx, SCREEN_HEIGHT, SCREEN_WIDTH);
    (&vars)->win = mlx_new_window((&vars)->mlx, SCREEN_HEIGHT, SCREEN_WIDTH, "cub3d");
    draw_line(&vars, vars.posx * BOX_SIZE, vars.posy * BOX_SIZE, vars.posx * BOX_SIZE+vars.dirx, vars.posy * BOX_SIZE+vars.diry, RED);
    mlx_hook(vars.win, 2, (1L << 0), key_control, &vars);
    mlx_loop(vars.mlx);
}

int main(void)
{
    cub3d();
    return (0);
}
