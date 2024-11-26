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

void draw_colored_wall_line(t_vars *vars, int i)
{
    int color_final = WHITE;
    double distance = vars->ray_dist[i];
    if (distance == 0)
        distance = 0.001;
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
    base_pt.y = POSITION_Y;
    top_pt.x = base_pt.x;
    top_pt.y = POSITION_Y + wall_height_top;
    bottom_pt.x = base_pt.x;
    bottom_pt.y = POSITION_Y - wall_height_bottom;

    draw_line(vars, &base_pt, &top_pt, color_final);
    draw_line(vars, &base_pt, &bottom_pt, color_final);
}

void cal_render(t_vars *vars)
{
    t_vector *ray;

    ray = vars->ray;
    double sample_angle = FOV / SAMPLE;
    double sample_radians = to_radians(sample_angle);
    double radians = to_radians(-FOV / 2.0); // 从视野左侧开始的角度
    int i = 0;
    while (i < (int)SAMPLE + 1)///////////////////////////////
    {
        rotate_vector(&ray[i], &(vars->dirv), radians);
        vars->ray_dist[i] = wall_distance(vars, &ray[i], i);
        normalize_vector(&ray[i], vars->ray_dist[i]);
        vars->ray_dist[i] = vars->ray_dist[i] * cos(to_radians(i * sample_angle - FOV / 2.0));
        radians += sample_radians;
        i++;
    }
}

void draw_visibility(t_vars *vars)
{
    t_vector *ray;
    ray = vars->ray;
    int i = 0;

    t_vector startpt_scaled;
    t_vector endpt_added;
    t_vector endpt_scaled;
    while (i < (int)SAMPLE + 1)///////////////////////////////
    {
        cpy_scale_vector(&startpt_scaled, &(vars->posv), BOX_SIZE);
        add_vector(&endpt_added, &(vars->posv), &ray[i]);
        cpy_scale_vector(&endpt_scaled, &endpt_added, BOX_SIZE);
        draw_line(vars, &startpt_scaled, &endpt_scaled, YELLOW);
        i++;
    }
}

void    draw_colored_wall(t_vars *vars)
{
    int i;

    i = 0;
    while (i < (int)SAMPLE + 1)
    {
        draw_colored_wall_line(vars, i);
        i++;
    }
}

void draw_map(t_vars *vars, double x, double y, double size)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (vars->map[j])
    {
        i = 0;
        while (vars->map[j][i])
        {
            if (vars->map[j][i] == '1')
                draw_box(vars, x + i * size, y + j * size, size);
            i++;
        }
        j++;
    }
    draw_visibility(vars);
}

void    render_game(t_vars *vars)
{
    mlx_clear_window(vars->mlx, vars->win);
    clear_image_buf(vars);
    draw_sky(vars, vars->game->color_c);
    draw_ground(vars, vars->game->color_f);
    cal_render(vars);
    //draw_map(vars, BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE);
    //draw_colored_wall(vars);
    draw_texture(vars);
    draw_map(vars, BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->buf_img, 0, 0);
}

int    update_frame(t_vars *vars)
{
    time_t now_time;

    now_time = get_current_time();
    if (vars->last_frame_t == 0)
    {
        vars->last_frame_t = now_time;
        return (0);
    }
    if (now_time - vars->last_frame_t < 1000000 / FPS)
    {
        //vars->last_frame_t = now_time;
        return (0);
    }
    render_game(vars);
    now_time = get_current_time();
    vars->last_frame_t = now_time;
    return (1);
}
