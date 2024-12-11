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

#include "../includes/cub3d.h"

static int	get_unit(int num1, int num2)
{
	if (num1 < num2)
		return (1);
	else
		return (-1);
}

static void	init_drawline(t_drawl *dl, t_vector *v0, t_vector *v1)
{
	dl->x0 = v0->x;
	dl->y0 = v0->y;
	dl->x1 = v1->x;
	dl->y1 = v1->y;
	dl->dx = ft_abs(dl->x1 - dl->x0);
	dl->dy = ft_abs(dl->y1 - dl->y0);
	dl->sx = get_unit(dl->x0, dl->x1);
	dl->sy = get_unit(dl->y0, dl->y1);
	dl->err = dl->dx - dl->dy;
}

void	draw_line(t_vars *vars, t_vector *v0, t_vector *v1, int color)
{
	t_drawl	dl;

	init_drawline(&dl, v0, v1);
	while (1)
	{
		if (dl.x0 >= 0 && dl.x0 < SCREEN_WIDTH && dl.y0 >= 0 && \
			dl.y0 < SCREEN_HEIGHT)
			put_pixel_to_buf(vars, dl.x0, dl.y0, color);
		else
			break ;
		if (dl.x0 == dl.x1 && dl.y0 == dl.y1)
			break ;
		dl.e2 = 2 * dl.err;
		if (dl.e2 > -dl.dy)
		{
			dl.err -= dl.dy;
			dl.x0 += dl.sx;
		}
		if (dl.e2 < dl.dx)
		{
			dl.err += dl.dx;
			dl.y0 += dl.sy;
		}
	}
}

void	draw_box(t_vars *vars, t_vector *pos, double size, int color)
{
	t_vector	nw;
	t_vector	ne;
	t_vector	sw;
	t_vector	se;
	int			i;

	nw.x = pos->x - size / 2;
	nw.y = pos->y - size / 2;
	ne.x = pos->x + size / 2;
	ne.y = pos->y - size / 2;
	sw.x = pos->x - size / 2;
	sw.y = pos->y + size / 2;
	se.x = pos->x + size / 2;
	se.y = pos->y + size / 2;
	i = 0;
	while (++i < size)
	{
		draw_line(vars, &nw, &ne, color);
		nw.y++;
		ne.y++;
	}
	draw_line(vars, &nw, &ne, color);
	draw_line(vars, &ne, &se, color);
	draw_line(vars, &se, &sw, color);
	draw_line(vars, &sw, &nw, color);
}

void	draw_rec(t_vars *vars, t_vector *pt1, t_vector *pt2, int color)
{
	t_vector	nw;
	t_vector	ne;
	t_vector	sw;
	t_vector	se;

	nw.x = pt1->x;
	nw.y = pt1->y;
	ne.x = pt2->x;
	ne.y = pt1->y;
	sw.x = pt1->x;
	sw.y = pt2->y;
	se.x = pt2->x;
	se.y = pt2->y;
	draw_line(vars, &nw, &ne, color);
	draw_line(vars, &ne, &se, color);
	draw_line(vars, &se, &sw, color);
	draw_line(vars, &sw, &nw, color);
}
