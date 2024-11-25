/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:07:51 by shuwang           #+#    #+#             */
/*   Updated: 2024/11/22 15:07:52 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void normalize_vector(t_vector *vector, double scale)
{
    double magnitude;

    magnitude = sqrt(vector->x * vector->x + vector->y * vector->y);
    vector->x /= magnitude;
    vector->y /= magnitude;
    vector->x *= scale;
    vector->y *= scale;
}

void rotate_vector(t_vector *v, t_vector *vo, double radians)
{
    double x;
    double y;
    
    x = vo->x;
    y = vo->y;
    v->x = x * cos(radians) - y * sin(radians);
    v->y = x * sin(radians) + y * cos(radians);
    normalize_vector(v, 1.0);
    return ;
}