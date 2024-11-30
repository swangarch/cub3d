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

double point_to_line_distance(t_vector *v1, t_vector *vdir, t_vector *v2) {
    // 分子部分

    double x1;
    double y1;

    double x2;
    double y2;

    double xv;
    double yv;

    x1 = v1->x;
    y1 = v1->y;

    xv = vdir->x;
    yv = vdir->y;

    x2 = v2->x;
    y2 = v2->y;

    //double numerator = ft_abs(xv * (y2 - y1) - yv * (x2 - x1));
    double numerator = (xv * (y2 - y1) - yv * (x2 - x1));
    // 分母部分
    double denominator = sqrt(xv * xv + yv * yv);
    // 距离
    return numerator / denominator;
}

void cal_render_obj(t_vars *vars)
{
    if (vars->pos_obj.x <= 0 || vars->pos_obj.y <= 0)
        return ;
    t_vector    *ray_obj;
    t_vector    camera;
    t_vector    sample_vector;
    t_vector    start_vector;
    double  radians;
    int i;

    t_vector obj_pos = vars->pos_obj;
    t_vector player_to_obj;
    vector_2pt(&player_to_obj, &obj_pos, &vars->posv);

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
        vars->ray_obj_dist_pt_ln[i] = point_to_line_distance(&vars->posv, &ray_obj[i], &obj_pos);  //position of obj
        if (vars->ray_obj_dist_pt_ln[i] <= 0.5 && vars->ray_obj_dist_pt_ln[i] >= -0.5 && dot_product(&player_to_obj, &ray_obj[i]) > 0)
            vars->ray_obj_dist[i] = len_2pt(&vars->posv, &obj_pos);
        else
            vars->ray_obj_dist[i] = 0;
        normalize_vector(&ray_obj[i], vars->ray_obj_dist[i]);
        vars->ray_obj_dist[i] = vars->ray_obj_dist[i] * cos(radians);
        add_vector(&start_vector, &start_vector, &sample_vector);
    }
}

void draw_obj_visibility(t_vars *vars, double size)
{

    if (vars->pos_obj.x <= 0 || vars->pos_obj.y <= 0)
        return ;
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

void draw_obj(t_vars *vars)
{
    int i;
    int j;
    t_vector pos_on_obj;
    double obj_distance;
    double wall_height;
    int x;  ///pixel position
    int y;  ///pixel position
    void *texture;
    int pixel_color;
    texture = vars->tex_object;
    if (vars->pos_obj.x <= 0 || vars->pos_obj.y <= 0)
        return ;
    
    i = 0;
    while (i < (int)SAMPLE)
    {
        if (vars->ray_dist[i] < vars->ray_obj_dist[i])
        {
            i++;
            continue;
        } 
        obj_distance = vars->ray_obj_dist[i];
        wall_height = DISPLAY_H / obj_distance;
        pos_on_obj.x = (vars->ray_obj_dist_pt_ln[i] + 0.5) * TEXTURE_SIZE;
        x = POSITION_X + i * (DISPLAY_W / SAMPLE);
        j = 0;

        if (DISPLAY_H / 2.0 - wall_height / 2 + j < 0)  //优化性能
            j = wall_height / 2 - DISPLAY_H / 2.0;
        while (j < (int)(wall_height))
        {
            y = DISPLAY_H / 2.0 - wall_height / 2 + j;
            if (y > DISPLAY_H)  //优化性能
                break;
            pos_on_obj.y = j / wall_height * TEXTURE_SIZE;
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

