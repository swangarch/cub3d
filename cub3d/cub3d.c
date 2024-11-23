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

void init_vars(t_vars *vars)
{
    vars->posv.x = 1.5;
    vars->posv.y = 1.5;
    vars->dirv.x = SCALE;
    vars->dirv.y = 0;
    normalize_vector(&(vars->dirv), 1.0);
    vars->height_ratio = 0.5;

    vars->last_mouse_pos.x = -1;
    vars->last_mouse_pos.y = -1;
    vars->last_mouse_move_t = 0;

    vars->mlx = mlx_init();//protect
    vars->buf_img = mlx_new_image(vars->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);//protect
    vars->buf_img_ptr = mlx_get_data_addr(vars->buf_img, &vars->bits_per_pixel, &vars->size_line, &vars->endian);
    vars->win = mlx_new_window(vars->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");//protect
}

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

    //draw_line(&vars, vars.posv.x * BOX_SIZE, vars.posv.y * BOX_SIZE, vars.posv.x * BOX_SIZE+ vars.dirv.x, vars.posv.y * BOX_SIZE+vars.dirv.y, RED);
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
