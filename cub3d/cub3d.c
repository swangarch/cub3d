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

    init_vars(&vars);
    vars.map = map;
    load_all_texture(&vars);

    mlx_hook(vars.win, 6, (1L << 6), mouse_move, &vars);
    mlx_hook(vars.win, 2, (1L << 0), key_control, &vars);
    mlx_loop(vars.mlx);
    //free()
}

int main(void)
{
    //errorchecking
    //parsing
    cub3d();
    return (0);
}
