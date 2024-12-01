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

void draw_colored_wall_line(t_vars *vars, int i)  ////no need
{
    int color_final = WHITE;
    double distance = vars->ray_dist[i];
    double wall_height = DISPLAY_H / distance;
    double wall_height_top = (vars->height_ratio) * wall_height;
    double wall_height_bottom = (1.0 - vars->height_ratio) * wall_height;

    if (vars->ray_color[i] == WEST)
        color_final = create_trgb(255, (int)((vars->ray_poswall[i]) * 255), 0, 0);
    else if (vars->ray_color[i] == EAST)
        color_final = create_trgb(255, 0, (int)((vars->ray_poswall[i]) * 255), 0);
    else if (vars->ray_color[i] == NORTH)
        color_final = create_trgb(255, 0, 0, (int)((vars->ray_poswall[i]) * 255));
    else if (vars->ray_color[i] == SOUTH)
        color_final = create_trgb(255, (int)((vars->ray_poswall[i]) * 255), 0, (int)((vars->ray_poswall[i]) * 255));

    t_vector    base_pt;
    t_vector    top_pt;
    t_vector    bottom_pt;

    base_pt.x = POSITION_X + i * (DISPLAY_W / SAMPLE);
    base_pt.y = DISPLAY_H / 2.0;
    top_pt.x = base_pt.x;
    top_pt.y = DISPLAY_H / 2.0 + wall_height_top;
    bottom_pt.x = base_pt.x;
    bottom_pt.y = DISPLAY_H / 2.0 - wall_height_bottom;

    draw_line(vars, &base_pt, &top_pt, color_final);
    draw_line(vars, &base_pt, &bottom_pt, color_final);
}

void    draw_colored_wall(t_vars *vars)
{
    int i;

    i = 0;
    while (i < (int)SAMPLE)
    {
        draw_colored_wall_line(vars, i);
        i++;
    }
}

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

void    render_game(t_vars *vars)
{
    mlx_clear_window(vars->mlx, vars->win);
    clear_image_buf(vars);
    draw_sky(vars, vars->game->color_c);
    draw_ground(vars, vars->game->color_f);
    move_character(vars);
    rotate_when_mouse_move(vars);
    update_state(vars);
    cal_render(vars);
    cal_render_obj(vars);
    //draw_colored_wall(vars);
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
    {
        return (0);
    }
    render_game(vars);
    if (vars->key_state[F])
    {
        fps = 1000000.0 / time_passed;
        ft_printf("FPS: %d\n", fps);
    }
    vars->last_frame_t = now_time;
    return (1);
}
