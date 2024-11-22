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

void normalize_direction(t_vars *vars)
{
    double magnitude;

    magnitude = sqrt(vars->dirx * vars->dirx + vars->diry * vars->diry);
    vars->dirx /= magnitude;
    vars->diry /= magnitude;
    vars->dirx *= SCALE;
    vars->diry *= SCALE;
}

void normalize_direction_vector(t_vector *vector)
{
    double magnitude;

    magnitude = sqrt(vector->x * vector->x + vector->y * vector->y);
    vector->x /= magnitude;
    vector->y /= magnitude;
    vector->x *= SCALE;
    vector->y *= SCALE;
}

void normalize_vector(t_vector *vector, double scale)
{
    double magnitude;

    magnitude = sqrt(vector->x * vector->x + vector->y * vector->y);
    vector->x /= magnitude;
    vector->y /= magnitude;
    vector->x *= scale;
    vector->y *= scale;
}

void normalize_screen_vector(t_vector *vector)
{
    double magnitude;

    magnitude = sqrt(vector->x * vector->x + vector->y * vector->y);
    vector->x /= magnitude;
    vector->y /= magnitude;
    vector->x *= SCALE_SCREEN;
    vector->y *= SCALE_SCREEN;
}

void rotate_vector(t_vars *vars, double radians)
{
    vars->dirx = vars->dirx * cos(radians) - vars->diry * sin(radians);
    vars->diry = vars->dirx * sin(radians) + vars->diry * cos(radians);
    normalize_direction(vars);
    return ;
}

double vector_projlen(double x1, double y1, double x2, double y2)
{
    double len;

    len = (x1 * x2 + y1 * y2) / sqrt(x2 * x2 + y2 * y2) / 100; 
    return (len);
}