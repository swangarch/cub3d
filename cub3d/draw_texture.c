/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:37:17 by shuwang           #+#    #+#             */
/*   Updated: 2024/11/25 16:37:18 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void draw_texture(t_vars *vars)
{
    if (!vars->tex_s)
        return (ft_putstr_fd("Error: texture doesn't exist\n", 2), (void)0);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->tex_s, 500, 500);
}

// int get_texture_pixel_color(void *tex_ptr, t_vector *v, )