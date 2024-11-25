/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry_draw.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:56:27 by shuwang           #+#    #+#             */
/*   Updated: 2024/11/22 14:56:27 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void put_pixel_to_buf(t_vars *vars, int x, int y, int color)
{
    int pixel_index;

    if (!(x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT))
        return ;

    pixel_index = y * vars->size_line + x * vars->bits_per_pixel / 8;
    if (pixel_index >= 0 && pixel_index < SCREEN_HEIGHT * vars->size_line) // 防止越界
    {
        *(int *)(vars->buf_img_ptr + pixel_index) = color; // 写入颜色
    }
}

void clear_image_buf(t_vars *vars)
{
    int total_pixels = SCREEN_WIDTH * SCREEN_HEIGHT;
    int *buffer = (int *)vars->buf_img_ptr;

    int i = 0;
    while (i < total_pixels)
    {
        buffer[i] = 0x000000; // 设置为黑色
        i++;
    }
}


// void draw_line(t_vars *vars, int x0, int y0, int x1, int y1, int color)
// {
//     int dx = ft_abs(x1 - x0);
//     int dy = ft_abs(y1 - y0);
//     int sx = (x0 < x1) ? 1 : -1; // x方向的步进
//     int sy = (y0 < y1) ? 1 : -1; // y方向的步进
//     int err = dx - dy;           // 初始误差

//     while (1) 
//     {
//         if (x0 >= 0 && x0 < SCREEN_WIDTH && y0 >= 0 && y0 < SCREEN_HEIGHT)
//             put_pixel_to_buf(vars, x0, y0, color);
//         else
//             break;
//         // mlx_pixel_put((vars)->mlx, (vars)->win, x0, y0, color); // 绘制当前点
//         if (x0 == x1 && y0 == y1) {
//             break; // 到达终点
//         }
//         int e2 = 2 * err; // 误差两倍，用于判断步进方向
//         if (e2 > -dy) {
//             err -= dy; // 减去y的增量
//             x0 += sx;  // x向前一步
//         }
//         if (e2 < dx) {
//             err += dx; // 增加x的增量
//             y0 += sy;  // y向前一步
//         }
//     }
// }

void draw_line(t_vars *vars, int x0, int y0, int x1, int y1, int color)
{
    int dx = ft_abs(x1 - x0);
    int dy = ft_abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1; // x方向的步进
    int sy = (y0 < y1) ? 1 : -1; // y方向的步进
    int err = dx - dy;           // 初始误差

    while (1) 
    {
        if (x0 >= 0 && x0 < SCREEN_WIDTH && y0 >= 0 && y0 < SCREEN_HEIGHT)
            put_pixel_to_buf(vars, x0, y0, color);
        else
            break;
        // mlx_pixel_put((vars)->mlx, (vars)->win, x0, y0, color); // 绘制当前点
        if (x0 == x1 && y0 == y1) {
            break; // 到达终点
        }
        int e2 = 2 * err; // 误差两倍，用于判断步进方向
        if (e2 > -dy) {
            err -= dy; // 减去y的增量
            x0 += sx;  // x向前一步
        }
        if (e2 < dx) {
            err += dx; // 增加x的增量
            y0 += sy;  // y向前一步
        }
    }
}

void draw_box(t_vars *vars, double x, double y, double size)
{
    draw_line(vars, x - size / 2, y - size / 2, x + size / 2, y - size / 2, YELLOW);
    draw_line(vars, x - size / 2, y - size / 2, x - size / 2, y + size / 2, GREEN);
    draw_line(vars, x + size / 2, y + size / 2, x + size / 2, y - size / 2, MAGENTA);
    draw_line(vars, x + size / 2, y + size / 2, x - size / 2, y + size / 2, CYAN);
}
