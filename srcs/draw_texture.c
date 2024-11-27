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

# include "../includes/cub3d.h"

int closest_int(double num)
{
    if (num - (int)num >= 0.5)
        return((int)ceil(num));
    else
        return ((int)floor(num));
}

int get_texture_pixel_color(void *tex, t_vector *pos)
{
    void *tex_ptr;
    int bits_per_pixel;
    int size_line;
    int endian;
    int pixel_index;
    int color;
    int x;
    int y;

    x = closest_int(pos->x);
    y = closest_int(pos->y);
    tex_ptr = mlx_get_data_addr(tex, &bits_per_pixel, &size_line, &endian);
    pixel_index =  y * size_line + x * bits_per_pixel / 8;
    if (pixel_index >= 0 && pixel_index < SCREEN_HEIGHT * size_line) // 防止越界
    {
        color = *(int *)(tex_ptr + pixel_index); // 写入颜色
        return (color);
    }
    return (-1);
}


int fade_color(int color, double distance)
{
    int r, g, b;
    double factor;

    // 获取RGB颜色分量
    r = get_r(color);
    g = get_g(color);
    b = get_b(color);

    factor = 1.0 / (1.0 + pow(distance, 1)); // 较强的衰减
    // 调整颜色亮度
    r = (int)(r * factor) + 100;
    g = (int)(g * factor) + 100;
    b = (int)(b * factor) + 100;

    // 确保RGB值在合法范围内
    if (r < 0) {
        r = 0;
    } else if (r > 255) {
        r = 255;
    }

    if (g < 0) {
        g = 0;
    } else if (g > 255) {
        g = 255;
    }

    if (b < 0) {
        b = 0;
    } else if (b > 255) {
        b = 255;
    }

    return (r << 16) | (g << 8) | b;
}

void draw_texture(t_vars *vars)
{
    int i;
    int j;
    t_vector pos_on_texture;
    double distance;
    double wall_height;
    int x;
    int y;
    void *texture;
    int pixel_color;
    
    i = 0;
    while (i < (int)SAMPLE + 1)
    {
        distance = vars->ray_dist[i];
        if (distance == 0)
            distance = 0.001;
        wall_height = DISPLAY_H / distance;
        pos_on_texture.x = vars->ray_poswall[i] * TEXTURE_SIZE;
        x = POSITION_X + i * (DISPLAY_W / SAMPLE);
        j = 0;
        if (vars->ray_color[i] == EAST)
            texture = vars->tex_e;
        else if (vars->ray_color[i] == WEST)
            texture = vars->tex_w;
        else if (vars->ray_color[i] == NORTH)
            texture = vars->tex_n;  
        else if (vars->ray_color[i] == SOUTH)
            texture = vars->tex_s;      
        while (j < (int)(wall_height))
        {
            y = POSITION_Y - wall_height / 2 + j;
            pos_on_texture.y = j / wall_height * TEXTURE_SIZE;
            pixel_color = get_texture_pixel_color(texture, &pos_on_texture);
            if (FADE)
                put_pixel_to_buf(vars, x, y, fade_color(pixel_color, distance));
            else
                put_pixel_to_buf(vars, x, y, pixel_color);
            j++;
        }
        i++;
    }
    // if (!vars->tex_s)
    //     return (ft_putstr_fd("Error: texture doesn't exist\n", 2), (void)0);
    // mlx_put_image_to_window(vars->mlx, vars->win, vars->tex_s, 500, 500);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
}