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

# include "cub3d.h"



int on_box(double x_center, double y_center, double x, double y)
{
    double top_y = y_center + GRID_SIZE / 2.0;
    double bottom_y = y_center - GRID_SIZE / 2.0;
    double left_x = x_center - GRID_SIZE / 2.0;
    double right_x = x_center + GRID_SIZE / 2.0;

    if (double_eql(x, left_x) && y >= bottom_y + MIN_ERR2 && y <= top_y - MIN_ERR2)
            return (WEST);
    else if (double_eql(x, right_x) && y >= bottom_y + MIN_ERR2 && y <= top_y - MIN_ERR2)
            return (EAST);
    else if (double_eql(y, top_y) && x >= left_x + MIN_ERR2 && x <= right_x - MIN_ERR2)
            return (NORTH);
    else if (double_eql(y, bottom_y) && x >= left_x + MIN_ERR2 && x <= right_x - MIN_ERR2)
            return (SOUTH);
    return (NOT_ONBOX);
}

double hit_wall(t_vars *vars, double x, double y, int *color)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < 9)
    {
        j = 0;
        while (j < 9)
        {
            if (vars->map[i][j] == '1')
                if (on_box((double)j + GRID_SIZE / 2.0, (double)i + GRID_SIZE / 2.0, x, y) != NOT_ONBOX)
                {
                    *color = on_box((double)j + GRID_SIZE / 2.0, (double)i + GRID_SIZE / 2.0, x, y);
                    return (len_2pt(vars->posv.x, vars->posv.y, x, y));
                }
            j++;
        }
        i++;
    }
    return (-1);
}

#define S_SIZE 50

double wall_distance(t_vars *vars, t_vector *vector, int *color, int i)
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
    double t_delta_y = 1.0 / ft_abs(dy);  // 每次跨越一个 y 网格的时间增量

    // 初始网格坐标
    int map_x = (int)floor(x);
    int map_y = (int)floor(y);

    double intersect_x = x;
    double intersect_y = y;
    double distance_towall;

    // 运行 DDA 算法
    while (1) {
        if (t_max_x < t_max_y) {
            map_x += step_x;  // 前进到下一个 x 网格线
            intersect_x = x + t_max_x * dx;
            intersect_y = y + t_max_x * dy;
            t_max_x += t_delta_x;  // 更新 t_max_x
        } else {
            map_y += step_y;  // 前进到下一个 y 网格线
            intersect_x = x + t_max_y * dx;
            intersect_y = y + t_max_y * dy;
            t_max_y += t_delta_y;  // 更新 t_max_y
        }
        // 可根据需要在此处添加条件判断（例如检测碰撞或其他逻辑）
        distance_towall = hit_wall(vars, intersect_x, intersect_y, &color[i]);
        if (distance_towall >= 0)
        {
            return (distance_towall);
        }
        if (len_2pt(x, y, intersect_x, intersect_y) > 1000.0) 
        {
            return(1000.0);
        }
    }
    return 0;
}
