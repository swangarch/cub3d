/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:53:16 by shuwang           #+#    #+#             */
/*   Updated: 2024/11/22 14:53:17 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d.h"

int double_eql(double a, double b)
{
    if (ft_abs(b - a) < MIN_ERR)
        return (1);
    return (0);
}

double ft_abs(double num)
{
    if (num >= 0)
        return (num);
    else
        return (-num);
}

double to_radians(double angle)
{
    double radians;
    radians = angle * (M_PI / 180.0);
    return (radians);
}

double len_2pt(t_vector *v1, t_vector *v2)
{
    double  sqr;
    double x1;
    double y1;
    double x2;
    double y2;

    x1 = v1->x;
    y1 = v1->y;
    x2 = v2->x;
    y2 = v2->y;

    sqr = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    return (sqr);
}

double vector_magnitude(t_vector *v)
{
    return (sqrt(v->x * v->x + v->y * v->y)); 
}


