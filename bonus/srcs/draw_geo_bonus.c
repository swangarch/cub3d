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

# include "../includes/cub3d_bonus.h"

static int get_unit(int num1, int num2)
{
    if (num1 < num2)
        return (1);
    else
        return (-1);
}

void draw_line(t_vars *vars, t_vector *v0, t_vector *v1, int color)
{
    int x0 = v0->x;
    int y0 = v0->y;
    int x1 = v1->x;
    int y1 = v1->y;
    int dx = ft_abs(x1 - x0);
    int dy = ft_abs(y1 - y0);
    int sx = get_unit(x0, x1); // x方向的步进
    int sy = get_unit(y0, y1); // y方向的步进
    int err = dx - dy;           // 初始误差
    int e2;

    while (1) 
    {
        if (x0 >= 0 && x0 < SCREEN_WIDTH && y0 >= 0 && y0 < SCREEN_HEIGHT)
            put_pixel_to_buf(vars, x0, y0, color);
        else
            break;
        if (x0 == x1 && y0 == y1)
            break; // 到达终点
        e2 = 2 * err; // 误差两倍，用于判断步进方向
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

void draw_box(t_vars *vars, t_vector *pos, double size, int color)
{
    t_vector NW;
    t_vector NE;
    t_vector SW;
    t_vector SE;
    int i;

    NW.x = pos->x - size / 2;
    NW.y = pos->y - size / 2;
    NE.x = pos->x + size / 2;
    NE.y = pos->y - size / 2;
    SW.x = pos->x - size / 2;
    SW.y = pos->y + size / 2;
    SE.x = pos->x + size / 2;
    SE.y = pos->y + size / 2;
    i = 0;
    while (++i < size)
    {
        draw_line(vars, &NW, &NE, color);
        NW.y++;
        NE.y++;
    }
    draw_line(vars, &NW, &NE, color);
    draw_line(vars, &NE, &SE, color);
    draw_line(vars, &SE, &SW, color);
    draw_line(vars, &SW, &NW, color);
}

void draw_rec(t_vars *vars, t_vector *pt1, t_vector *pt2, int color)
{
    t_vector NW;
    t_vector NE;
    t_vector SW;
    t_vector SE;

    NW.x = pt1->x;
    NW.y = pt1->y;
    NE.x = pt2->x;
    NE.y = pt1->y;
    SW.x = pt1->x;
    SW.y = pt2->y;
    SE.x = pt2->x;
    SE.y = pt2->y;
    draw_line(vars, &NW, &NE, color);
    draw_line(vars, &NE, &SE, color);
    draw_line(vars, &SE, &SW, color);
    draw_line(vars, &SW, &NW, color);
}

void fill_rec(t_vars *vars, t_vector *pt1, t_vector *pt2, int color)
{
    t_vector NW;
    t_vector NE;
    t_vector SW;
    t_vector SE;
    int i;

    NW.x = pt1->x;
    NW.y = pt1->y;
    NE.x = pt2->x;
    NE.y = pt1->y;
    SW.x = pt1->x;
    SW.y = pt2->y;
    SE.x = pt2->x;
    SE.y = pt2->y;
    i = 0;
    while (i < pt2->y - pt1->y)
    {
        draw_line(vars, &NW, &NE, color);
        NW.y++;
        NE.y++;
        i++;
    }
}

// void fill_circle(t_vars *vars, t_vector *pt1, double size, int color)
// {
//     t_vector NW;
//     t_vector NE;
//     t_vector SW;
//     t_vector SE;
//     int i;
//     int j;
//     t_vector pos;

//     i = vars->posv.x - size / 2.0;
//     j = vars->posv.y - size / 2.0;
//     while (i < vars->posv.x + size / 2.0)
//     {
//         j = vars->posv.y - size / 2.0;
//         {
//             pos.x = i * ;
//             pos.y = j;
//             if (len_2pt() <= size / 2.0)
//                 put_pixel_to_buf(vars, i, j, color);
//         }
//     }
// }
