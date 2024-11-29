/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:22:36 by shuwang           #+#    #+#             */
/*   Updated: 2024/11/25 16:22:36 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d.h"

/*++++++++++++++++++++++++++++++++++++*/
static void set_init_dir(t_vars *vars, int dir_player)
{
    if (dir_player == NORTH)
    {
        vars->dirv.x = 0;
        vars->dirv.y = -SCALE;
    }
    else if (dir_player == SOUTH)
    {
        vars->dirv.x = 0;
        vars->dirv.y = SCALE;
    }
    else if (dir_player == WEST)
    {
        vars->dirv.x = -SCALE;
        vars->dirv.y = 0;
    }
    else if (dir_player == EAST)
    {
        vars->dirv.x = SCALE;
        vars->dirv.y = 0;
    }
}
/*++++++++++++++++++++++++++++++++++++*/

void init_vars(t_vars *vars, t_game *game)
{
    vars->posv.x = game->player_x;
    vars->posv.y = game->player_y;
    set_init_dir(vars, game->dir_player);//++++++++++
    normalize_vector(&(vars->dirv), 1.0);
    vars->height_ratio = 0.5;

    vars->last_frame_t = 0;
    
    vars->last_mouse_pos.x = -1;//
    vars->last_mouse_pos.y = -1;//
    vars->mouse_move_dir = 0;
    vars->hp = 1.0;
    vars->touch_wall = 0;
    vars->show_map = 1;
    vars->show_fps = 0;
    vars->map_size = MAP_SIZE;

    vars->game = game;

    vars->map = game->map;
    vars->map[15][15] = 'C';
    ft_memset(&(vars->key_state), 0, 256 * sizeof(int));

    vars->mlx = mlx_init();//protect
    load_all_texture(vars);
    vars->buf_img = mlx_new_image(vars->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);//protect
    vars->buf_img_ptr = mlx_get_data_addr(vars->buf_img, &vars->bits_per_pixel, &vars->size_line, &vars->endian);
    vars->win = mlx_new_window(vars->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");//protect
}

int load_texture(t_vars *vars, void **img, char *path) //protect
{
    int img_width;
    int img_height;
    *img = mlx_xpm_file_to_image(vars->mlx, path, &img_width, &img_height);
    if (!*img)
    {
        ft_putstr_fd("Error: load image failed\n", 2);
        return (-1);
    }
    if (img_height != TEXTURE_SIZE || img_width != TEXTURE_SIZE)
    {
        ft_putstr_fd("Error: wrong image size\n", 2);
        mlx_destroy_image(vars->mlx, *img);
        return (-1);
    }
    return (0);
}

int load_all_texture(t_vars *vars)  //protect
{
    int success;

    success = 0;
    success += load_texture(vars, &(vars->tex_w), vars->game->tex_path[T_WEST]);
    success += load_texture(vars, &(vars->tex_e), vars->game->tex_path[T_EAST]);
    success += load_texture(vars, &(vars->tex_n), vars->game->tex_path[T_NORTH]);
    success += load_texture(vars, &(vars->tex_s), vars->game->tex_path[T_SOUTH]);
    success += load_texture(vars, &(vars->tex_object), "textures/object.xpm");

    return (success);
}


