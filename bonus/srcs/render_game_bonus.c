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

# include "../includes/cub3d_bonus.h"

void put_pixel_to_buf(t_vars *vars, int x, int y, int color)
{
    int pixel_index;

    if (!(x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT))
        return ;
    pixel_index = y * vars->size_line + x * vars->bits_per_pixel / 8;
    if (pixel_index >= 0 && pixel_index < SCREEN_HEIGHT * vars->size_line) // 防止越界
    {
        *(int *)(vars->buf_img_ptr + pixel_index) = color; // 写入颜色
    }
}

void clear_image_buf(t_vars *vars) // fill with all black pixel
{
    int total_pixels;
    int *buffer;
    int i;

    buffer = (int *)vars->buf_img_ptr;
    total_pixels = SCREEN_WIDTH * SCREEN_HEIGHT;
    i = 0;
    while (i < total_pixels)
    {
        buffer[i] = 0x000000; // 设置为黑色
        i++;
    }
}

/*Vector version*/
void cal_render(t_vars *vars)
{
    t_vector    camera;
    t_vector    sample_vector;
    t_vector    start_vector;
    double  radians;
    int i;

    rotate_vector(&camera, &(vars->dirv), to_radians(90));
    normalize_vector(&camera, tan(to_radians(FOV / 2)));
    cpy_scale_vector(&sample_vector, &camera, 2.0 / SAMPLE);
    cpy_scale_vector(&start_vector, &sample_vector, - SAMPLE / 2.0);
    i = -1;
    while (++i < (int)SAMPLE)///////////////////////////////
    {
        add_vector(&vars->ray[i], &vars->dirv, &start_vector);
        radians = atan(vector_magnitude(&start_vector) / \
            vector_magnitude(&vars->dirv));
        vars->ray_dist[i] = wall_distance(vars, &vars->ray[i], i);
        normalize_vector(&vars->ray[i], vars->ray_dist[i]);
        vars->ray_dist[i] = vars->ray_dist[i] * cos(radians);
        add_vector(&start_vector, &start_vector, &sample_vector);
    }
}

void    render_frame(t_vars *vars)
{
    mlx_clear_window(vars->mlx, vars->win);
    clear_image_buf(vars);
    move_character(vars);
    rotate_when_mouse_move(vars);  //bonus
    update_state(vars);
    cal_render(vars);
    cal_render_obj(vars, 0, -1); //bonus
    render_floor_sky(vars);  //bonus
    draw_texture(vars, -1, 0);
    draw_obj(vars, -1, -1); //bonus
    draw_map(vars, 0, 0); //bonus
    draw_ui(vars); //bonus
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
        render_frame(vars);
        return (0);
    }
    time_passed = now_time - vars->last_frame_t;
    if (time_passed < 1000000 / FPS)
        return (0);
    render_frame(vars);
    if (vars->key_state[F])
    {
        fps = 1000000.0 / time_passed;
        ft_printf("FPS: %d\n", fps);
    }
    vars->last_frame_t = now_time;
    return (1);
}
