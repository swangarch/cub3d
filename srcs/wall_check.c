/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:25:49 by shuwang           #+#    #+#             */
/*   Updated: 2024/11/22 15:25:51 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d.h"

static int in_range(double number, double bottom, double top)
{
    if (number >= bottom + MIN_ERR2 && number <= top - MIN_ERR2)
        return (1);
    else
        return (0);
}

int on_box(t_vars *vars, t_vector* center, t_vector *ist, int index)
{
    double t_y;
    double b_y;
    double l_x;
    double r_x;

    t_y = center->y + GRID_SIZE / 2.0;
    b_y = center->y - GRID_SIZE / 2.0;
    l_x = center->x - GRID_SIZE / 2.0;
    r_x = center->x + GRID_SIZE / 2.0;
    if (double_eql(ist->x, l_x) && in_range(ist->y, b_y, t_y))
        return (vars->ray_color[index] = WEST, \
            vars->ray_poswall[index] = t_y - ist->y, WEST);
    else if (double_eql(ist->x, r_x) && in_range(ist->y, b_y, t_y))
        return (vars->ray_color[index] = EAST, \
            vars->ray_poswall[index] = ist->y - b_y, EAST);
    else if (double_eql(ist->y, t_y) && in_range(ist->x, l_x, r_x))
        return (vars->ray_color[index] = NORTH, \
            vars->ray_poswall[index] = r_x - ist->x, NORTH);
    else if (double_eql(ist->y, b_y) && in_range(ist->x, l_x, r_x))
        return (vars->ray_color[index] = SOUTH, \
            vars->ray_poswall[index] = ist->x - l_x, SOUTH);
    return (NOT_ONBOX);
}

double hit_wall(t_vars *vars, t_vector *intersect, int index, t_vector map_loc)
{
    t_vector box_pos;
    double distance;

    // 确保坐标在地图范围内
    if  (map_loc.x >= vars->game->map_col - 1 || map_loc.y >= \
        vars->game->map_row || map_loc.x < 0 || map_loc.y < 0)
        return (-1);
    // 检查当前网格是否是墙壁
    if (vars->map[(int)map_loc.y][(int)map_loc.x] == '1')
    {
        // 计算当前网格的中心坐标
        box_pos.x = map_loc.x + GRID_SIZE / 2.0;
        box_pos.y = map_loc.y + GRID_SIZE / 2.0;
        // 检查光线是否在墙壁的范围内
        if (on_box(vars, &box_pos, intersect, index) != NOT_ONBOX)
        {
            distance = len_2pt(&(vars->posv), intersect);
            return (distance);
        }
    }
    return (-1);
}

static int get_unit(double num1, double num2)
{
    if (num1 > num2)
        return (1);
    else 
        return (-1);
}

static void first_pos(t_vars *vars, t_vector *result, t_vector *v, t_vector *ist)
{
    result->x = floor(v->x);
    result->y = floor(v->y);
    cpy_scale_vector(ist, &vars->posv, 1.0);
}

static double next_dir_int_dist(double dir, double comp)
{
    if (dir > 0)
        return (ceil(comp) - comp);
    else
        return (comp - floor(comp));
}

static void move_first(t_vars *vars, t_vector *t_max, t_vector *t_delta, int i)
{
    t_max->x = next_dir_int_dist(vars->ray[i].x, vars->posv.x); 
    t_max->y = next_dir_int_dist(vars->ray[i].y, vars->posv.y); 
    if (vars->ray[i].x != 0)
    {
        t_max->x /= ft_abs(vars->ray[i].x);
        t_delta->x = 1.0 / ft_abs(vars->ray[i].x);
    }
    else
    {
        t_max->x = VERY_LARGE_VALUE;
        t_delta->x = VERY_LARGE_VALUE;
    }
    if (vars->ray[i].y != 0)
    {
        t_max->y /= ft_abs(vars->ray[i].y);
        t_delta->y = 1.0 / ft_abs(vars->ray[i].y);
    }
    else
    {
        t_max->y = VERY_LARGE_VALUE;
        t_delta->x = VERY_LARGE_VALUE;
    }
}

static void move_timeval(t_vector *intersect, t_vector *posv, double timeval, t_vector *dv)
{
    intersect->x = posv->x + timeval * dv->x;
    intersect->y = posv->y + timeval * dv->y;
}

static void update_map_loc(t_vector *t_max, t_vector *vector, t_vector *map_loc)
{
    if (t_max->x < t_max->y)
        map_loc->x += get_unit(vector->x, 0);
    else 
        map_loc->y += get_unit(vector->y, 0);
}

static void update_time(t_vector *t_max, t_vector *t_delta)
{
    if (t_max->x < t_max->y)
        t_max->x += t_delta->x;
    else 
        t_max->y += t_delta->y;
}

double wall_distance(t_vars *vars, t_vector *vector, int index)
{
    t_vector    t_max;
    t_vector    t_delta;
    t_vector    map_loc;
    t_vector    intersect;
    double      distance;

    move_first(vars, &t_max, &t_delta, index);
    first_pos(vars, &map_loc, &vars->posv, &intersect); //找到当前位置对应的格子maplocation， 和当前和格子点相交的点
    while (1) 
    {
        update_map_loc(&t_max, vector, &map_loc);
        if (t_max.x < t_max.y) 
            move_timeval(&intersect, &vars->posv, t_max.x, vector); //前进到下一个 y 网格线
        else 
            move_timeval(&intersect, &vars->posv, t_max.y, vector); //前进到下一个 y 网格线
        update_time(&t_max, &t_delta);
        distance = hit_wall(vars, &intersect, index, map_loc);
        if (distance >= 0)
            return (distance);
        if (len_2pt(&(vars->posv), &intersect) > MAX_VIEW_DISTANCE) 
            return(MAX_VIEW_DISTANCE);
    }
    return (0);
}



