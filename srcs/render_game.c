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

# include "../includes/cub3d.h"

/*Vector version*/
void cal_render(t_vars *vars)
{
    t_vector    *ray;
    t_vector    camera;
    t_vector    sample_vector;
    t_vector    start_vector;
    double  radians;
    int i;

    rotate_vector(&camera, &(vars->dirv), to_radians(90));
    normalize_vector(&camera, tan(to_radians(FOV / 2)));
    ray = vars->ray;
    cpy_scale_vector(&sample_vector, &camera, 2.0 / SAMPLE);
    cpy_scale_vector(&start_vector, &sample_vector, - SAMPLE / 2.0);
    i = -1;
    while (++i < (int)SAMPLE)///////////////////////////////
    {
        add_vector(&ray[i], &vars->dirv, &start_vector);
        radians = atan(vector_magnitude(&start_vector) / vector_magnitude(&vars->dirv));
        vars->ray_dist[i] = wall_distance(vars, &ray[i], i);
        normalize_vector(&ray[i], vars->ray_dist[i]);
        vars->ray_dist[i] = vars->ray_dist[i] * cos(radians);
        add_vector(&start_vector, &start_vector, &sample_vector);
    }
}

static void render_floor_sky(t_vars *vars)
{
    t_vector ray_dir_left;      // 左边射线
    t_vector ray_dir_right;     // 右边射线
    t_vector    tex_sky;
    t_vector    camera;

    int pixel_color;
    double row_distances[SCREEN_HEIGHT]; // 预计算行的距离
    for (int y = SCREEN_HEIGHT / 2; y < SCREEN_HEIGHT; y++) {
        row_distances[y] = (SCREEN_HEIGHT / 2.0) / (y - SCREEN_HEIGHT / 2.0);
    }
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
                pixel_color = get_texture_pixel_color(vars->tex_c, &tex_sky);
                put_pixel_to_buf(vars, x, y, pixel_color);
            }
        } else {
            // 渲染地板
            for (int x = 0; x < SCREEN_WIDTH; x++) {
                double floor_x = vars->posv.x + row_distances[y] * HEIGHT_RATIO * (ray_dir_left.x + (x / (double)SCREEN_WIDTH) * (ray_dir_right.x - ray_dir_left.x));
                double floor_y = vars->posv.y + row_distances[y] * HEIGHT_RATIO * (ray_dir_left.y + (x / (double)SCREEN_WIDTH) * (ray_dir_right.y - ray_dir_left.y));
                tex_sky.x = (int)(floor_x * TEXTURE_SIZE / 1.0) % TEXTURE_SIZE;
                tex_sky.y = (int)(floor_y * TEXTURE_SIZE / 1.0) % TEXTURE_SIZE;
                if (tex_sky.x < 0) tex_sky.x += TEXTURE_SIZE;
                if (tex_sky.y < 0) tex_sky.y += TEXTURE_SIZE;
                pixel_color = get_texture_pixel_color(vars->tex_f, &tex_sky);
                put_pixel_to_buf(vars, x, y, pixel_color);
            }
        }
    }
}


void    render_game(t_vars *vars)
{
    mlx_clear_window(vars->mlx, vars->win);
    clear_image_buf(vars);
    move_character(vars);
    rotate_when_mouse_move(vars);
    update_state(vars);
    cal_render(vars);
    cal_render_obj(vars);
    render_floor_sky(vars);
    // draw_sky(vars, vars->game->color_c);
    // draw_ground(vars, vars->game->color_f);
    draw_texture(vars);
    draw_obj(vars);
    draw_map(vars, 0, 0);
    draw_ui(vars);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->buf_img, 0, 0);
}

int    update_frame(t_vars *vars)
{
    time_t now_time;
    time_t time_passed;
    int fps;

    now_time = get_current_time();
    if (vars->last_frame_t == 0)
    {
        vars->last_frame_t = now_time;
        return (0);
    }
    time_passed = now_time - vars->last_frame_t;
    if (time_passed < 1000000 / FPS)
        return (0);
    render_game(vars);
    if (vars->key_state[F])
    {
        fps = 1000000.0 / time_passed;
        ft_printf("FPS: %d\n", fps);
    }
    vars->last_frame_t = now_time;
    return (1);
}
