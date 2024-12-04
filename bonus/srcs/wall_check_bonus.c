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

# include "../includes/cub3d_bonus.h"

int on_box(t_vars *vars, t_vector* center, t_vector *ist, int index)
{
    double top_y = center->y + GRID_SIZE / 2.0;
    double bottom_y = center->y - GRID_SIZE / 2.0;
    double left_x = center->x - GRID_SIZE / 2.0;
    double right_x = center->x + GRID_SIZE / 2.0;

    if (double_eql(ist->x, left_x) && ist->y >= bottom_y + MIN_ERR2 && ist->y <= top_y - MIN_ERR2)
        return (vars->ray_color[index] = WEST, vars->ray_poswall[index] = top_y - ist->y, WEST);
    else if (double_eql(ist->x, right_x) && ist->y >= bottom_y + MIN_ERR2 && ist->y <= top_y - MIN_ERR2)
        return (vars->ray_color[index] = EAST, vars->ray_poswall[index] = ist->y - bottom_y, EAST);
    else if (double_eql(ist->y, top_y) && ist->x >= left_x + MIN_ERR2 && ist->x <= right_x - MIN_ERR2)
        return (vars->ray_color[index] = NORTH, vars->ray_poswall[index] = right_x - ist->x, NORTH);
    else if (double_eql(ist->y, bottom_y) && ist->x >= left_x + MIN_ERR2 && ist->x <= right_x - MIN_ERR2)
        return (vars->ray_color[index] = SOUTH, vars->ray_poswall[index] = ist->x - left_x, SOUTH);
    return (NOT_ONBOX);
}

double hit_wall(t_vars *vars, t_vector *intersect, int index, t_vector map_loc)
{
    t_vector box_pos;

    // 确保坐标在地图范围内
    if  (map_loc.x >= vars->game->map_col - 1 || map_loc.y >= vars->game->map_row || map_loc.x < 0 || map_loc.y < 0)
        return (-1);
    // 检查当前网格是否是墙壁
    if (vars->map[(int)map_loc.y][(int)map_loc.x] == '1')
    {
        // 计算当前网格的中心坐标
        box_pos.x = map_loc.x + GRID_SIZE / 2.0;
        box_pos.y = map_loc.y + GRID_SIZE / 2.0;
        // 检查光线是否在墙壁的范围内
        if (on_box(vars, &box_pos, intersect, index) != NOT_ONBOX)
            return len_2pt(&(vars->posv), intersect);
    }
    return (-1);
}

static int get_dir_unit(double num1, double num2)
{
    if (num1 > num2)
        return (1);
    else 
        return (-1);
}

double wall_distance(t_vars *vars, t_vector *vector, int index)
{
    double x = vars->posv.x;  // 出发点 x 坐标
    double y = vars->posv.y;  // 出发点 y 坐标
    double dx = vector->x;  // 已归一化的方向向量 x 分量
    double dy = vector->y;  // 已归一化的方向向量 y 分量
    int step_x = get_dir_unit(dx, 0); // ? 1 : -1;  // x 方向步长（+1 或 -1）
    int step_y = get_dir_unit(dy, 0); // ? 1 : -1;  // y 方向步长（+1 或 -1）
    double t_max_x = (step_x > 0) ? ceil(x) - x : x - floor(x);  // 到达下一个 x 网格线的时间
    double t_max_y = (step_y > 0) ? ceil(y) - y : y - floor(y);  // 到达下一个 y 网格线的时间
    //------------------------------------------
    if (dx != 0)
        t_max_x /= ft_abs(dx);
    else
        t_max_x = VERY_LARGE_VALUE;
    if (dy != 0)
        t_max_y /= ft_abs(dy);
    else
        t_max_y = VERY_LARGE_VALUE;

    double t_delta_x;  // 每次跨越一个 x 网格的时间增量
    double t_delta_y;  // 每次跨越一个 y 网格的时间增
    if (dx != 0)
        t_delta_x = 1.0 / ft_abs(dx);
    else
        t_delta_x = VERY_LARGE_VALUE;
    if (dy != 0)
        t_delta_y = 1.0 / ft_abs(dy);
    else
        t_delta_y = VERY_LARGE_VALUE;
    //-------------------------------------------
    t_vector    map_loc;//++++++++++++++++
    map_loc.x = floor(x);//+++++++++++++++
    map_loc.y = floor(y);//+++++++++++++++

    t_vector intersect;
    intersect.x = x;
    intersect.y = y;
    double distance_towall;

    // 运行 DDA 算法
    while (1) {
        if (t_max_x < t_max_y) {
            map_loc.x += step_x;  // 前进到下一个 x 网格线
            intersect.x = x + t_max_x * dx;
            intersect.y = y + t_max_x * dy;
            t_max_x += t_delta_x;  // 更新 t_max_x
        } else {
            map_loc.y += step_y;  // 前进到下一个 y 网格线
            intersect.x = x + t_max_y * dx;
            intersect.y = y + t_max_y * dy;
            t_max_y += t_delta_y;  // 更新 t_max_y
        }
        // 可根据需要在此处添加条件判断（例如检测碰撞或其他逻辑）
        distance_towall = hit_wall(vars, &intersect, index, map_loc);
        if (distance_towall >= 0)
            return (distance_towall);
        if (len_2pt(&(vars->posv), &intersect) > MAX_VIEW_DISTANCE) 
            return(MAX_VIEW_DISTANCE);
    }
    return 0;
}



