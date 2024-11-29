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

void draw_visibility(t_vars *vars, double size)
{
    t_vector *ray;
    ray = vars->ray;
    int i = 0;

    t_vector startpt_scaled;
    t_vector endpt_added;
    t_vector endpt_scaled;
    while (i < (int)SAMPLE)///////////////////////////////
    {
        cpy_scale_vector(&startpt_scaled, &(vars->posv), size);
        add_vector(&endpt_added, &(vars->posv), &ray[i]);
        cpy_scale_vector(&endpt_scaled, &endpt_added, size);
        draw_line(vars, &startpt_scaled, &endpt_scaled, YELLOW);
        i++;
    }
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

void draw_obj_visibility(t_vars *vars, double size)
{
    t_vector *ray_obj;
    ray_obj = vars->ray_obj;
    int i = 0;

    t_vector startpt_scaled;
    t_vector endpt_added;
    t_vector endpt_scaled;
    while (i < (int)SAMPLE)///////////////////////////////
    {
        cpy_scale_vector(&startpt_scaled, &(vars->posv), size);
        add_vector(&endpt_added, &(vars->posv), &ray_obj[i]);
        cpy_scale_vector(&endpt_scaled, &endpt_added, size);
        draw_line(vars, &startpt_scaled, &endpt_scaled, RED);
        i++;
    }
}

void draw_map(t_vars *vars, double x, double y)
{
    int i;
    int j;

    i = 0;
    j = 0;

    if (!vars->key_state[M])
        return ;

    if (vars->key_state[NUM_0])
    {
        //ft_putstr_fd("plus\n", 1);
        vars->map_size += 0.1;
    }
    if (vars->key_state[NUM_9] && vars->map_size >= 7.0)
    {
        //ft_putstr_fd("minus\n", 1);
        vars->map_size -= 0.1;
    }
    
   // double size = vars->map_size;

    if ((vars->game->map_col - 1) * vars->map_size > SCREEN_WIDTH)
        vars->map_size = SCREEN_WIDTH / (double)(vars->game->map_col - 1);
    if ((vars->game->map_row) * vars->map_size > SCREEN_HEIGHT)
        vars->map_size = SCREEN_HEIGHT / (double)(vars->game->map_row);
    while (vars->map[j])
    {
        i = 0;
        while (vars->map[j][i])
        {
            if (vars->map[j][i] == '1')
                 draw_box(vars, x + i * vars->map_size *1 + vars->map_size / 2.0, y + j * vars->map_size + vars->map_size / 2.0, vars->map_size, WHITE);
            if (vars->map[j][i] == 'C')
                 draw_box(vars, x + i * vars->map_size *1 + vars->map_size / 2.0, y + j * vars->map_size + vars->map_size / 2.0, vars->map_size, RED);
            i++;
        }
        j++;
    }
    draw_visibility(vars, vars->map_size);
    draw_obj_visibility(vars, vars->map_size);
}



void cal_render_obj(t_vars *vars)
{
    t_vector    *ray_obj;
    t_vector    camera;
    t_vector    sample_vector;
    t_vector    start_vector;
    double  radians;
    int i;

    rotate_vector(&camera, &(vars->dirv), to_radians(90));
    normalize_vector(&camera, tan(to_radians(FOV / 2)));
    ray_obj = vars->ray_obj;
    cpy_scale_vector(&sample_vector, &camera, 2.0 / SAMPLE);
    cpy_scale_vector(&start_vector, &sample_vector, - SAMPLE / 2.0);
    i = -1;
    while (++i < (int)SAMPLE)///////////////////////////////
    {
        add_vector(&ray_obj[i], &vars->dirv, &start_vector);
        radians = atan(vector_magnitude(&start_vector) / vector_magnitude(&vars->dirv));
        vars->ray_obj_dist[i] = obj_distance(vars, &ray_obj[i], i);
        normalize_vector(&ray_obj[i], vars->ray_obj_dist[i]);
        vars->ray_obj_dist[i] = vars->ray_obj_dist[i] * cos(radians);
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
    
    // mlx_string_put(vars->mlx, vars->win, 0, SCREEN_HEIGHT - 50, WHITE, fps);
    vars->last_frame_t = now_time;
    return (1);
}
