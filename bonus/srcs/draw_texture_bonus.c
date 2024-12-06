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
    int bits_pr_pix;
    int sz_ln;
    int endian;
    int pixel_index;
    tex_ptr = mlx_get_data_addr(tex, &bits_pr_pix, &sz_ln, &endian);
    pixel_index =  floor(pos->y) * sz_ln + floor(pos->x) * bits_pr_pix / 8;
    if (pixel_index >= 0 && pixel_index < SCREEN_HEIGHT * sz_ln) // 防止越界
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

static void render_tex_pix(t_vars *vars, int *p_screen, int color, int i)
{
    int x;
    int y;
    
    if (get_t(color) >= 1)
        return ;
    x = p_screen[0];
    y = p_screen[1];
    if (vars->key_state[P])
    {
        if (vars->ray_color[i] % 2)
            color = put_vertical_shadow(color);
    }
    if (vars->key_state[O])
        color = fade_color(color, vars->ray_dist[i]);
    put_pixel_to_buf(vars, x, y, color);
}

void draw_texture(t_vars *vars, int i, int j)
{
    t_vector postex;
    double wall_height;
    int pos_screen[2];
    
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
            render_tex_pix(vars, pos_screen, get_texcolor(get_texture(vars, i), \
                &postex, -1), i);
            j++;
        }
    }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
}

