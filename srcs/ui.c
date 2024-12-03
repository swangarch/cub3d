/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:59:01 by shuwang           #+#    #+#             */
/*   Updated: 2024/11/28 15:59:03 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d.h"

void draw_hp_bar(t_vars *vars)
{
    t_vector pt1;
    t_vector pt2;
    t_vector ptv;

    pt1.x = SCREEN_WIDTH * 0.05;
    pt1.y = SCREEN_HEIGHT * 0.9;
    pt2.x = SCREEN_WIDTH * 0.05 + HP_W;
    pt2.y = SCREEN_HEIGHT * 0.9 + HP_H;
    ptv.x = (pt2.x - pt1.x) * vars->hp + pt1.x;
    ptv.y = pt2.y; 
    
    fill_rec(vars, &pt1, &ptv, RED);
    draw_rec(vars, &pt1, &pt2, WHITE);
}

void draw_sight(t_vars *vars)
{
    t_vector v1a;
    t_vector v1b;
    t_vector v2a;
    t_vector v2b;
    
    v1a.x = SCREEN_WIDTH / 2.0;
    v1b.x = SCREEN_WIDTH / 2.0;
    v1a.y = SCREEN_HEIGHT / 2.0 - 20.0;
    v1b.y = SCREEN_HEIGHT / 2.0 + 20.0;
    v2a.y = SCREEN_HEIGHT / 2.0;
    v2b.y = SCREEN_HEIGHT / 2.0;
    v2a.x = SCREEN_WIDTH / 2.0 - 20.0;
    v2b.x = SCREEN_WIDTH / 2.0 + 20.0;
    draw_line(vars, &v1a, &v1b, WHITE);
    draw_line(vars, &v2a, &v2b, WHITE);
}

void draw_ui(t_vars *vars)
{
    draw_hp_bar(vars);
    draw_sight(vars);
}

