/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_effect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:35:14 by shuwang           #+#    #+#             */
/*   Updated: 2024/11/29 16:35:16 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	put_vertical_shadow(int color)
{
	int	r;
	int	g;
	int	b;
	int	increment;

	r = get_r(color);
	g = get_g(color);
	b = get_b(color);
	increment = -30;
	r = color_range(r + increment);
	g = color_range(g + increment);
	b = color_range(b + increment);
	return (create_trgb(0, r, g, b));
}

int	fade_color(int color, double distance)
{
	int		r;
	int		g;
	int		b;
	double	factor;

	r = get_r(color);
	g = get_g(color);
	b = get_b(color);
	factor = 1.0 / (1.0 + pow(distance, 0.35)) + 0.6;
	r = color_range((int)(r * factor) + 10);
	g = color_range((int)(g * factor) + 10);
	b = color_range((int)(b * factor) + 10);
	return ((r << 16) | (g << 8) | b);
}

double	dist_line_pt(t_vector *v1, t_vector *vdir, t_vector *v2)
{
	double	numerator;
	double	denominator;

	numerator = vdir->x * (v2->y - v1->y) - vdir->y * (v2->x - v1->x);
	denominator = sqrt(vdir->x * vdir->x + vdir->y * vdir->y);
	return (numerator / denominator);
}
