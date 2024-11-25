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
    return (0);
}

int load_all_texture(t_vars *vars)  //protect
{
    int success;

    success = 0;
    success = load_texture(vars, &(vars->tex_w), "./textures/w.xpm");
    success = load_texture(vars, &(vars->tex_e), "./textures/e.xpm");
    success = load_texture(vars, &(vars->tex_n), "./textures/n.xpm");
    success = load_texture(vars, &(vars->tex_s), "./textures/s.xpm");

    return (success);
}


