/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:17:27 by shuwang           #+#    #+#             */
/*   Updated: 2024/11/22 15:17:28 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void draw_colored_wall(t_vars *vars, int i, double distance, int *color)
{
    int color_final = WHITE;
    if (distance == 0)
        distance = 0.001;
    double wall_height = DISPLAY_H / distance;
    double wall_height_top = (vars->height_ratio) * wall_height;
    double wall_height_bottom = (1.0 - vars->height_ratio) * wall_height;

    if (color[i] == WEST)
        color_final = RED;
    else if (color[i] == EAST)
        color_final = BLUE;
    else if (color[i] == NORTH)
        color_final = GREEN;
    else if (color[i] == SOUTH)
        color_final = YELLOW;
    draw_line(vars, (POSITION_X + i * (DISPLAY_W / SAMPLE)), POSITION_Y, (POSITION_X + i * (DISPLAY_W / SAMPLE)), POSITION_Y + wall_height_top, color_final);
    draw_line(vars, (POSITION_X + i * (DISPLAY_W / SAMPLE)), POSITION_Y, (POSITION_X + i * (DISPLAY_W / SAMPLE)), POSITION_Y - wall_height_bottom, color_final);
}

void draw_visibility(t_vars *vars)
{
    t_vector *ray;
    ray = vars->ray;

    double sample_angle = FOV / SAMPLE;
    double sample_radians = to_radians(sample_angle);
    double radians = to_radians(-FOV / 2.0); // 从视野左侧开始的角度
    int i = 0;
    double distance;

    while (i < (int)SAMPLE + 1)///////////////////////////////
    {
        rotate_vector(&ray[i], &(vars->dirv), radians);
        distance = wall_distance(vars, &ray[i], vars->ray_color, i);
        normalize_vector(&ray[i], distance);
        draw_line(vars, vars->posv.x * BOX_SIZE, vars->posv.y * BOX_SIZE, vars->posv.x * BOX_SIZE + ray[i].x * BOX_SIZE, vars->posv.y * BOX_SIZE + ray[i].y * BOX_SIZE, WHITE);
        distance = distance * cos(to_radians(i * sample_angle - FOV / 2.0));
        draw_colored_wall(vars, i, distance, vars->ray_color);
        radians += sample_radians;
        i++;
    }
}

void draw_screen(t_vars *vars)
{
    t_vector ray[2];
    t_vector vo;
    vo.x = vars->dirv.x;
    vo.y = vars->dirv.y;

    double radians = to_radians(-FOV / 2); // 从视野左侧开始的角度
    for (int i = 0; i < 2; i++)/////////////////////////////////////////
    {
        rotate_vector(&ray[i], &vo, radians);
        draw_line(vars, vars->posv.x * BOX_SIZE, vars->posv.y * BOX_SIZE, vars->posv.x * BOX_SIZE + ray[i].x * SCALE, vars->posv.y * BOX_SIZE + ray[i].y * SCALE, BLUE);
        radians += to_radians(FOV); // 每次累加固定的增量角度
    }
    draw_line(vars, vars->posv.x * BOX_SIZE + ray[0].x * SCALE, vars->posv.y * BOX_SIZE + ray[0].y * SCALE, vars->posv.x * BOX_SIZE + ray[1].x * SCALE, vars->posv.y * BOX_SIZE + ray[1].y * SCALE, BLUE);
}

void draw_map(t_vars *vars, double x, double y, double size)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < 9)
    {
        j = 0;
        while (j < 9)
        {
            if (vars->map[j][i] == '1')
                draw_box(vars, x + i * size, y + j * size, size);
            j++;
        }
        i++;
    }
}

void    render_game(t_vars *vars)
{
    mlx_clear_window(vars->mlx, vars->win);
    clear_image_buf(vars);
    draw_visibility(vars);
    draw_line(vars, vars->posv.x * BOX_SIZE, vars->posv.y * BOX_SIZE, vars->posv.x * BOX_SIZE + vars->dirv.x * SCALE, vars->posv.y * BOX_SIZE + vars->dirv.y * SCALE, RED);
    draw_screen(vars);
    draw_map(vars, BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->buf_img, 0, 0);
}
