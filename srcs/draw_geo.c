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

# include "../includes/cub3d.h"

static int get_unit(int num1, int num2)
{
    if (num1 < num2)
        return (1);
    else
        return (-1);
}

static void init_drawline(t_drawl *dl, t_vector *v0, t_vector *v1)
{
    dl->x0 = v0->x;
    dl->y0 = v0->y;
    dl->x1 = v1->x;
    dl->y1 = v1->y;
    dl->dx = ft_abs(dl->x1 - dl->x0);
    dl->dy = ft_abs(dl->y1 - dl->y0);
    dl->sx = get_unit(dl->x0, dl->x1); // x方向的步进
    dl->sy = get_unit(dl->y0, dl->y1); // y方向的步进
    dl->err = dl->dx - dl->dy;           // 初始误差
}

void draw_line(t_vars *vars, t_vector *v0, t_vector *v1, int color)
{
    t_drawl dl;
    init_drawline(&dl, v0, v1);

    while (1) 
    {
        if (dl.x0 >= 0 && dl.x0 < SCREEN_WIDTH && dl.y0 >= 0 && dl.y0 < \
            SCREEN_HEIGHT)
            put_pixel_to_buf(vars, dl.x0, dl.y0, color);
        else
            break;
        if (dl.x0 == dl.x1 && dl.y0 == dl.y1)
            break; // 到达终点
        dl.e2 = 2 * dl.err; // 误差两倍，用于判断步进方向
        if (dl.e2 > -dl.dy) {
            dl.err -= dl.dy; // 减去y的增量
            dl.x0 += dl.sx;  // x向前一步
        }
        if (dl.e2 < dl.dx) {
            dl.err += dl.dx; // 增加x的增量
            dl.y0 += dl.sy;  // y向前一步
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
