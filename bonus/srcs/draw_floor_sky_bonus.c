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

# include "../includes/cub3d_bonus.h"

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

void render_sky_texture(t_vars *vars)
{
    t_vector ray_dir_left;      // 左边射线
    t_vector ray_dir_right;     // 右边射线
    t_vector    tex_sky;
    t_vector    camera;
    int pixel_color;
    double row_distances_sky[SCREEN_HEIGHT]; // 预计算行的距离
    for (int y = SCREEN_HEIGHT / 2 - 1; y >= 0; y--) {
        row_distances_sky[y] = (SCREEN_HEIGHT / 2.0) / (SCREEN_HEIGHT / 2.0 - y);
    }
    rotate_vector(&camera, &(vars->dirv), to_radians(90));
    normalize_vector(&camera, tan(to_radians(FOV / 2)));
    ray_dir_left.x = vars->dirv.x - camera.x;
    ray_dir_left.y = vars->dirv.y - camera.y;
    ray_dir_right.x = vars->dirv.x + camera.x;
    ray_dir_right.y = vars->dirv.y + camera.y;

    double floor_x;
    double floor_y;

    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        if (y < SCREEN_HEIGHT / 2) {
            // 渲染天空
            for (int x = 0; x < SCREEN_WIDTH; x++) {
                floor_x = row_distances_sky[y] * HEIGHT_RATIO * (ray_dir_left.x + (x / (double)SCREEN_WIDTH) * (ray_dir_right.x - ray_dir_left.x));
                floor_y = row_distances_sky[y] * HEIGHT_RATIO * (ray_dir_left.y + (x / (double)SCREEN_WIDTH) * (ray_dir_right.y - ray_dir_left.y));
                tex_sky.x = (int)(floor_x * TEXTURE_SIZE / 3.0) % TEXTURE_SIZE;
                tex_sky.y = (int)(floor_y * TEXTURE_SIZE / 3.0) % TEXTURE_SIZE;
                if (tex_sky.x < 0) tex_sky.x += TEXTURE_SIZE;
                if (tex_sky.y < 0) tex_sky.y += TEXTURE_SIZE;
                pixel_color = get_texcolor(vars->tex_c, &tex_sky, -1);
                put_pixel_to_buf(vars, x, y, pixel_color);
            }
        }
    }
}

void render_floor_texture(t_vars *vars)
{
    t_vector ray_dir_left;      // 左边射线
    t_vector ray_dir_right;     // 右边射线
    t_vector    camera;
    t_vector    tex_floor;
    int pixel_color;
    double row_distances[SCREEN_HEIGHT]; // 预计算行的距离

    for (int y = SCREEN_HEIGHT / 2; y < SCREEN_HEIGHT; y++) {
        row_distances[y] = (SCREEN_HEIGHT / 2.0) / (y - SCREEN_HEIGHT / 2.0);
    }
    rotate_vector(&camera, &(vars->dirv), to_radians(90));
    normalize_vector(&camera, tan(to_radians(FOV / 2)));
    ray_dir_left.x = vars->dirv.x - camera.x;
    ray_dir_left.y = vars->dirv.y - camera.y;
    ray_dir_right.x = vars->dirv.x + camera.x;
    ray_dir_right.y = vars->dirv.y + camera.y;

    double floor_x;
    double floor_y;

    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        if (y >= SCREEN_HEIGHT / 2) {
            // 渲染地板
            for (int x = 0; x < SCREEN_WIDTH; x++) {
                floor_x = vars->posv.x + row_distances[y] * HEIGHT_RATIO * (ray_dir_left.x + (x / (double)SCREEN_WIDTH) * (ray_dir_right.x - ray_dir_left.x));
                floor_y = vars->posv.y + row_distances[y] * HEIGHT_RATIO * (ray_dir_left.y + (x / (double)SCREEN_WIDTH) * (ray_dir_right.y - ray_dir_left.y));
                tex_floor.x = (int)(floor_x * TEXTURE_SIZE / 1.0) % TEXTURE_SIZE;
                tex_floor.y = (int)(floor_y * TEXTURE_SIZE / 1.0) % TEXTURE_SIZE;
                if (tex_floor.x < 0) tex_floor.x += TEXTURE_SIZE;
                if (tex_floor.y < 0) tex_floor.y += TEXTURE_SIZE;
                pixel_color = get_texcolor(vars->tex_f, &tex_floor, -1);
                put_pixel_to_buf(vars, x, y, pixel_color);
            }
        }
    }
}

void render_floor_sky(t_vars *vars)
{
    if (vars->tex_f)
        render_floor_texture(vars);
    else
        draw_ground(vars, vars->game->color_f);
    if (vars->tex_c)
        render_sky_texture(vars);
    else
        draw_sky(vars, vars->game->color_c);
}
