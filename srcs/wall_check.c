/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_detection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:25:49 by shuwang           #+#    #+#             */
/*   Updated: 2024/11/22 15:25:51 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d.h"

int on_box(t_vars *vars, t_vector* center, t_vector *intersect, int index)
{
    double x = intersect->x;
    double y = intersect->y;
    double top_y = center->y + GRID_SIZE / 2.0;
    double bottom_y = center->y - GRID_SIZE / 2.0;
    double left_x = center->x - GRID_SIZE / 2.0;
    double right_x = center->x + GRID_SIZE / 2.0;

    if (double_eql(x, left_x) && y >= bottom_y + MIN_ERR2 && y <= top_y - MIN_ERR2)
    {
        vars->ray_color[index] = WEST;
        vars->ray_poswall[index] = top_y - y;
        return (WEST);
    }
    else if (double_eql(x, right_x) && y >= bottom_y + MIN_ERR2 && y <= top_y - MIN_ERR2)
    {
        vars->ray_color[index] = EAST;
        vars->ray_poswall[index] = y - bottom_y;
        return (EAST);
    }
    else if (double_eql(y, top_y) && x >= left_x + MIN_ERR2 && x <= right_x - MIN_ERR2)
    {
        vars->ray_color[index] = NORTH;
        vars->ray_poswall[index] = right_x - x;
        return (NORTH);
    }
    else if (double_eql(y, bottom_y) && x >= left_x + MIN_ERR2 && x <= right_x - MIN_ERR2)
    {
        vars->ray_color[index] = SOUTH;
        vars->ray_poswall[index] = x - left_x;
        return (SOUTH);
    }
    return (NOT_ONBOX);
}

double hit_wall(t_vars *vars, t_vector *intersect, int index)
{
    int i;
    int j;

    i = 0;
    j = 0;
    t_vector box_pos;
    while (vars->map[j])
    {
        i = 0;
        while (vars->map[j][i])
        {
            if (vars->map[j][i] == '1')
            {
                box_pos.x = (double)i + GRID_SIZE / 2.0;
                box_pos.y = (double)j + GRID_SIZE / 2.0;
                if (on_box(vars, &box_pos, intersect, index) != NOT_ONBOX)
                    return (len_2pt(&(vars->posv), intersect));
            }
            i++;
        }
        j++;
    }
    return (-1);
}

#define S_SIZE 50

double wall_distance(t_vars *vars, t_vector *vector, int index)
{
    double x = vars->posv.x;  // 出发点 x 坐标
    double y = vars->posv.y;  // 出发点 y 坐标
    double dx = vector->x;  // 已归一化的方向向量 x 分量
    double dy = vector->y;  // 已归一化的方向向量 y 分量

    int step_x = (dx > 0) ? 1 : -1;  // x 方向步长（+1 或 -1）
    int step_y = (dy > 0) ? 1 : -1;  // y 方向步长（+1 或 -1）

    double t_max_x = (step_x > 0) ? ceil(x) - x : x - floor(x);  // 到达下一个 x 网格线的时间
    double t_max_y = (step_y > 0) ? ceil(y) - y : y - floor(y);  // 到达下一个 y 网格线的时间
    t_max_x /= ft_abs(dx);  // 归一化时间
    t_max_y /= ft_abs(dy);  // 归一化时间

    double t_delta_x = 1.0 / ft_abs(dx);  // 每次跨越一个 x 网格的时间增量
    double t_delta_y = 1.0 / ft_abs(dy);  // 每次跨越一个 y 网格的时间增    // double intersect_x = x;
    // double intersect_y = y;量

    // 初始网格坐标
    int map_x = (int)floor(x);
    int map_y = (int)floor(y);

    t_vector intersect;
    intersect.x = x;
    intersect.y = y;
    double distance_towall;

    // 运行 DDA 算法
    while (1) {
        if (t_max_x < t_max_y) {
            map_x += step_x;  // 前进到下一个 x 网格线
            intersect.x = x + t_max_x * dx;
            intersect.y = y + t_max_x * dy;
            t_max_x += t_delta_x;  // 更新 t_max_x
        } else {
            map_y += step_y;  // 前进到下一个 y 网格线
            intersect.x = x + t_max_y * dx;
            intersect.y = y + t_max_y * dy;
            t_max_y += t_delta_y;  // 更新 t_max_y
        }
        // 可根据需要在此处添加条件判断（例如检测碰撞或其他逻辑）
        distance_towall = hit_wall(vars, &intersect, index);
        if (distance_towall >= 0)
            return (distance_towall);
        if (len_2pt(&(vars->posv), &intersect) > 1000.0) 
            return(1000.0);
    }
    return 0;
}