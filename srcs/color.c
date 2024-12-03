/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:32:48 by shuwang           #+#    #+#             */
/*   Updated: 2024/11/22 15:32:48 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d.h"

int create_trgb(int t, int r, int g, int b)
{
    return (t << 24 | r << 16 | g << 8 | b);
}

int get_r(int color) {
    return (color >> 16) & 0xFF;
}

int get_g(int color) {
    return (color >> 8) & 0xFF;
}

int get_b(int color) {
    return color & 0xFF;
}

int get_t(int color) {
    return (color >> 24) & 0xFF;
}

