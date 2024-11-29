/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 20:27:22 by shuwang           #+#    #+#             */
/*   Updated: 2024/11/29 20:27:23 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d.h"

double point_to_line_distance(double x1, double y1, double xv, double yv, double x2, double y2) {
    // 分子部分
    double numerator = ft_abs(xv * (y2 - y1) - yv * (x2 - x1));
    // 分母部分
    double denominator = sqrt(xv * xv + yv * yv);
    // 距离
    return numerator / denominator;
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
    double d_to_obj;
    t_vector obj_pos;
    obj_pos.x = 15.5;
    obj_pos.y = 15.5;
    while (++i < (int)SAMPLE)///////////////////////////////
    {
        add_vector(&ray_obj[i], &vars->dirv, &start_vector);
        normalize_vector(&ray_obj[i], 1000.0);
        radians = atan(vector_magnitude(&start_vector) / vector_magnitude(&vars->dirv));
        d_to_obj = point_to_line_distance(vars->posv.x, vars->posv.y, ray_obj[i].x, ray_obj[i].y, obj_pos.x, obj_pos.y);  //position of obj
        if (d_to_obj <= 0.5)
            vars->ray_obj_dist[i] = len_2pt(&vars->posv, &obj_pos);
        else
            vars->ray_obj_dist[i] = 0;
        normalize_vector(&ray_obj[i], vars->ray_obj_dist[i]);
        vars->ray_obj_dist[i] = vars->ray_obj_dist[i] * cos(radians);
    }
}

void draw_obj(t_vars *vars)
{
    int i;
    int j;
    t_vector pos_on_obj;
    double obj_distance;
    double wall_height;
    int x;
    int y;
    void *texture;
    int pixel_color;
    
    i = 0;
    double i_start;
    double i_end;
    double i_range;
    i_start = -1;
    i_end = -1;

    int k = 0;

    while (k < (int)SAMPLE)
    {
        if (vars->ray_obj_dist[k] > 0 && i_start == -1)
            i_start = k;
        if (k < (int)SAMPLE - 1)
        {
            if (vars->ray_obj_dist[k] > 0 && vars->ray_obj_dist[k + 1] <= MIN_ERR)
                i_end = k + 1;
        }
        if (k == (int)SAMPLE - 1)
        {
            if (vars->ray_obj_dist[k] > 0)
                i_end = k;
        }
        k++;
    }
    i_range = i_end - i_start + 1;

    while (i < (int)SAMPLE)
    {
        obj_distance = vars->ray_obj_dist[i];
        wall_height = DISPLAY_H / obj_distance;
        pos_on_obj.x = (i - i_start) / i_range * TEXTURE_SIZE;
        x = POSITION_X + i * (DISPLAY_W / SAMPLE);

        j = 0;
        texture = vars->tex_object; 

        if (DISPLAY_H / 2.0 - wall_height / 2 + j < 0)
            j = wall_height / 2 - DISPLAY_H / 2.0;
        while (j < (int)(wall_height))
        {
            y = DISPLAY_H / 2.0 - wall_height / 2 + j;
            if (y > DISPLAY_H)
                break;
            pos_on_obj.y = j / wall_height * TEXTURE_SIZE / obj_distance;
            pixel_color = get_texture_pixel_color(texture, &pos_on_obj);
            if (get_t(pixel_color) >= 1)
            {
                j++;
                continue;
            }
            if (vars->key_state[O] && vars->key_state[P])
                put_pixel_to_buf(vars, x, y, fade_color(put_shadow(pixel_color, pos_on_obj.y, TEXTURE_SIZE), obj_distance));
            else if (vars->key_state[O])
                put_pixel_to_buf(vars, x, y, fade_color(pixel_color, obj_distance));
            else if (vars->key_state[P])
                put_pixel_to_buf(vars, x, y, put_shadow(pixel_color, pos_on_obj.y, TEXTURE_SIZE));
            else
                put_pixel_to_buf(vars, x, y, pixel_color);
            j++;
        }
        i++;
    }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
}

