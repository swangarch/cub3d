/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_sky.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:37:13 by shuwang           #+#    #+#             */
/*   Updated: 2024/12/03 11:37:14 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_ground(t_vars *vars, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < SCREEN_WIDTH)
	{
		j = 0;
		while (j < SCREEN_HEIGHT)
		{
			if (j >= SCREEN_HEIGHT / 2)
				put_pixel_to_buf(vars, i, j, color);
			j++;
		}
		i++;
	}
}

void	draw_sky(t_vars *vars, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < SCREEN_WIDTH)
	{
		j = 0;
		while (j < SCREEN_HEIGHT)
		{
			if (j < SCREEN_HEIGHT / 2)
				put_pixel_to_buf(vars, i, j, color);
			j++;
		}
		i++;
	}
}

void	fill_rec(t_vars *vars, t_vector *pt1, t_vector *pt2, int color)
{
	t_vector	nw;
	t_vector	ne;
	t_vector	sw;
	t_vector	se;
	int			i;

	nw.x = pt1->x;
	nw.y = pt1->y;
	ne.x = pt2->x;
	ne.y = pt1->y;
	sw.x = pt1->x;
	sw.y = pt2->y;
	se.x = pt2->x;
	se.y = pt2->y;
	i = 0;
	while (i < pt2->y - pt1->y)
	{
		draw_line(vars, &nw, &ne, color);
		nw.y++;
		ne.y++;
		i++;
	}
}
