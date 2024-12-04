/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:37:17 by shuwang           #+#    #+#             */
/*   Updated: 2024/11/25 16:37:18 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d_bonus.h"

int get_texcolor(void *tex, t_vector *pos, int color)
{
    void *tex_ptr;
    int bits_per_pixel;
    int size_line;
    int endian;
    int pixel_index;
    
    tex_ptr = mlx_get_data_addr(tex, &bits_per_pixel, &size_line, &endian);
    pixel_index =  round(pos->y) * size_line + round(pos->x) * bits_per_pixel / 8;
    if (pixel_index >= 0 && pixel_index < SCREEN_HEIGHT * size_line) // 防止越界
    {
        color = *(int *)(tex_ptr + pixel_index); // 写入颜色
        return (color);
    }
    return (-1);
}

void *get_texture(t_vars *vars, int i)
{
    void *texture;

    texture = NULL;
    if (vars->ray_color[i] == EAST)
        texture = vars->tex_e;
    else if (vars->ray_color[i] == WEST)
        texture = vars->tex_w;
    else if (vars->ray_color[i] == NORTH)
        texture = vars->tex_n;  
    else if (vars->ray_color[i] == SOUTH)
        texture = vars->tex_s;
    return(texture);
}

static void render_texture_pixel(t_vars *vars, int *pos_screen, int pixel_color, int i)
{
    int x;
    int y;
    
    if (get_t(pixel_color) >= 1)
        return ;
    x = pos_screen[0];
    y = pos_screen[1];
    if (vars->key_state[P])
    {
        if (vars->ray_color[i] % 2)
            pixel_color = put_vertical_shadow(pixel_color);
    }
    if (vars->key_state[O])
        pixel_color = fade_color(pixel_color, vars->ray_dist[i]);
    put_pixel_to_buf(vars, x, y, pixel_color);
}

void draw_texture(t_vars *vars)
{
    int i;
    int j;
    t_vector postex;
    double wall_height;
    int pos_screen[2];
    
    i = -1;
    while (++i < (int)SAMPLE)
    {
        wall_height = DISPLAY_H / vars->ray_dist[i] * HEIGHT_RATIO;
        postex.x = vars->ray_poswall[i] * TEXTURE_SIZE;
        pos_screen[0] = POSITION_X + i * (DISPLAY_W / SAMPLE);
        j = 0;
        if (DISPLAY_H / 2.0 - wall_height / 2 + j < 0)
            j = wall_height / 2 - DISPLAY_H / 2.0;
        while (j < (int)(wall_height))
        {
            pos_screen[1] = DISPLAY_H / 2.0 - wall_height / 2 + j;
            if (pos_screen[1] > DISPLAY_H)
                break;
            postex.y = j / wall_height * TEXTURE_SIZE;
            render_texture_pixel(vars, pos_screen, get_texcolor(get_texture(vars, i), &postex, -1), i);
            j++;
        }
    }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
}

