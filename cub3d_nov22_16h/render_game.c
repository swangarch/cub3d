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

// void draw_line_in_buf(t_vars *vars, int idx, double distance, int *color, int *buf_data)
// {
//     int color_final = WHITE;
//     //double wall_height = DISPLAY_H / distance;

//     (void)vars;
//     (void)distance;
//     if (color[idx] == WEST)
//         color_final = RED;
//     else if (color[idx] == EAST)
//         color_final = BLUE;
//     else if (color[idx] == NORTH)
//         color_final = GREEN;
//     else if (color[idx] == SOUTH)
//         color_final = YELLOW;
//     // draw_line(vars, (POSITION_X + i * (DISPLAY_W / SAMPLE)), POSITION_Y, (POSITION_X + i * (DISPLAY_W / SAMPLE)), POSITION_Y + wall_height / 2, color_final);
//     // draw_line(vars, (POSITION_X + i * (DISPLAY_W / SAMPLE)), POSITION_Y, (POSITION_X + i * (DISPLAY_W / SAMPLE)), POSITION_Y - wall_height / 2, color_final);
//     int i = 0;
//     int j = 0;
//     while (j <SCREEN_HEIGHT)
//     {
//         i = 0;
//         while (i < SCREEN_WIDTH)
//         {
//             if (i == 100)   
//                 buf_data[j * SCREEN_WIDTH + i] = color_final;
//             i++;
//         }
//         j++;
//     }
// }


// void game_buf(t_vars *vars, double fov, int *buf_data)
// {
//     t_vector ray[(int)SAMPLE + 1]; 
//     int *ray_color = malloc(sizeof(int) * ((int)SAMPLE + 1));
//     if (!ray_color)
//         return;

//     double sample_angle = fov / SAMPLE;
//     double sample_radians = angle_radians(sample_angle);
//     double radians = angle_radians(-fov / 2.0); // 从视野左侧开始的角度
//     int i = 0;
//     double distance = 0;
//     while (i < (int)SAMPLE + 1)///////////////////////////////
//     {
//         ray[i].x = vars->dirx * cos(radians) - vars->diry * sin(radians);
//         ray[i].y = vars->dirx * sin(radians) + vars->diry * cos(radians);
//         normalize_vector(&ray[i], 1);
//         distance = check_close_wall(vars, &ray[i], ray_color, i);
//         ray[i].x *= distance;
//         ray[i].y *= distance;
//         distance = distance * cos(angle_radians(i * sample_angle - fov / 2.0));
//         draw_line_in_buf(vars, i, distance, ray_color, buf_data);
//         radians += sample_radians;
//         i++;
//     }
// }

// void    render_game_buf(t_vars *vars)
// {
//     //void *buf_img;
//     int  *buf_data;
//     int  bpp, size_line, endian;

//     //buf_img = mlx_new_image(vars->mlx, SCREEN_HEIGHT, SCREEN_WIDTH);
//     buf_data = (int *)mlx_get_data_addr(vars->buf_img, &bpp, &size_line, &endian);
//     ft_memset(vars->buf_img, 0, sizeof(int) * SCREEN_HEIGHT * size_line);

//     game_buf(vars, FOV, buf_data);
//     mlx_put_image_to_window(vars->mlx, vars->win, vars->buf_img, 0, 0);
// }

void draw_colored_wall(t_vars *vars, int i, double distance, int *color)
{
    int color_final = WHITE;
    double wall_height = DISPLAY_H / distance;

    if (color[i] == WEST)
        color_final = RED;
    else if (color[i] == EAST)
        color_final = BLUE;
    else if (color[i] == NORTH)
        color_final = GREEN;
    else if (color[i] == SOUTH)
        color_final = YELLOW;
    draw_line(vars, (POSITION_X + i * (DISPLAY_W / SAMPLE)), POSITION_Y, (POSITION_X + i * (DISPLAY_W / SAMPLE)), POSITION_Y + wall_height / 2, color_final);
    draw_line(vars, (POSITION_X + i * (DISPLAY_W / SAMPLE)), POSITION_Y, (POSITION_X + i * (DISPLAY_W / SAMPLE)), POSITION_Y - wall_height / 2, color_final);
}

void draw_visibility(t_vars *vars, double fov)
{
    t_vector ray[(int)SAMPLE + 1]; 
    int *ray_color = malloc(sizeof(int) * ((int)SAMPLE + 1));
    if (!ray_color)
        return;

    double sample_angle = fov / SAMPLE;
    double sample_radians = angle_radians(sample_angle);
    double radians = angle_radians(-fov / 2.0); // 从视野左侧开始的角度

    int i = 0;
    double distance = 0;
    while (i < (int)SAMPLE + 1)///////////////////////////////
    {
        ray[i].x = vars->dirx * cos(radians) - vars->diry * sin(radians);
        ray[i].y = vars->dirx * sin(radians) + vars->diry * cos(radians);
        normalize_vector(&ray[i], 1);
        distance = wall_distance(vars, &ray[i], ray_color, i);
        ray[i].x *= distance;
        ray[i].y *= distance;
        distance = distance * cos(angle_radians(i * sample_angle - fov / 2.0));
        draw_line(vars, vars->posx * BOX_SIZE, vars->posy * BOX_SIZE, vars->posx * BOX_SIZE + ray[i].x * BOX_SIZE, vars->posy * BOX_SIZE + ray[i].y * BOX_SIZE, WHITE);
        draw_colored_wall(vars, i, distance, ray_color);
        radians += sample_radians;
        i++;
    }
}

void draw_screen(t_vars *vars, double fov)
{
    t_vector ray[2];

    double radians = angle_radians(-fov / 2); // 从视野左侧开始的角度
    for (int i = 0; i < 2; i++)/////////////////////////////////////////
    {
        ray[i].x = vars->dirx * cos(radians) - vars->diry * sin(radians);
        ray[i].y = vars->dirx * sin(radians) + vars->diry * cos(radians);
        normalize_screen_vector(&ray[i]);
        draw_line(vars, vars->posx * BOX_SIZE, vars->posy * BOX_SIZE, vars->posx * BOX_SIZE + ray[i].x, vars->posy * BOX_SIZE + ray[i].y, BLUE);
        radians += angle_radians(FOV); // 每次累加固定的增量角度
    }
    draw_line(vars, vars->posx * BOX_SIZE + ray[0].x, vars->posy * BOX_SIZE + ray[0].y, vars->posx * BOX_SIZE + ray[1].x, vars->posy * BOX_SIZE + ray[1].y, BLUE);
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
    draw_visibility(vars, FOV);
    draw_line(vars, vars->posx * BOX_SIZE, vars->posy * BOX_SIZE, vars->posx * BOX_SIZE + vars->dirx, vars->posy * BOX_SIZE + vars->diry, RED);
    draw_screen(vars, FOV);
    draw_map(vars, BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE);
}
