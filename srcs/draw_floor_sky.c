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

# include "../includes/cub3d.h"

void draw_ground(t_vars *vars, int color)
{
    int i;
    int j;

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

void draw_sky(t_vars *vars, int color)
{
    int i;
    int j;

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
