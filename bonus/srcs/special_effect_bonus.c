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

// int put_shadow(int color, double height, double wall_height)
// {
//     double x;
//     int r, g, b;
//     double factor;

//     // 获取RGB颜色分量
//     r = get_r(color);
//     g = get_g(color);
//     b = get_b(color);

//     x = ft_abs(height - wall_height / 2.0);
//     factor = pow(M_E, - x / (wall_height / 2.0));
//     factor = log(factor + 1) + 0.6;  ///const
//     r = color_range(r * factor);
//     g = color_range(g * factor);
//     b = color_range(b * factor);
//     return (create_trgb(0, r, g, b));
// }

int put_vertical_shadow(int color)
{
    int r, g, b;
    // 获取RGB颜色分量
    r = get_r(color);
    g = get_g(color);
    b = get_b(color);

    int increment = -30;
    r = color_range(r + increment);
    g = color_range(g + increment);
    b = color_range(b + increment);
    return (create_trgb(0, r, g, b));
}

int fade_color(int color, double distance)
{
    int r, g, b;
    double factor;

    // 获取RGB颜色分量
    r = get_r(color);
    g = get_g(color);
    b = get_b(color);

    factor = 1.0 / (1.0 + pow(distance, 0.35)) + 0.6;
    // 调整颜色亮度
    r = color_range((int)(r * factor) + 10);
    g = color_range((int)(g * factor) + 10);
    b = color_range((int)(b * factor) + 10);
    return (r << 16) | (g << 8) | b;
}
