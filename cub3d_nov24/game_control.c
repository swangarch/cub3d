/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:00:44 by shuwang           #+#    #+#             */
/*   Updated: 2024/11/22 15:00:46 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int box_collision(t_vars *vars, double x, double y)
{
    (void)vars;
    (void)x;
    (void)y;
    return (0);
    // int i;
    // int j;

    // i = 0;
    // j = 0;
    // while (i < 9)
    // {
    //     j = 0;
    //     while (j < 9)
    //     {
    //         if (vars->map[i][j] == '1')
    //         {
    //             if (x <= (double)i + GRID_SIZE / 2.0 && x >= (double)i - GRID_SIZE / 2.0 && y <= (double)j + GRID_SIZE / 2.0 && y >= (double)j - GRID_SIZE / 2.0)
    //                 return (1);
    //         }
    //         j++;
    //     }
    //     i++;
    // }
    // return (0);
}

int	move_character(int keycode, t_vars *vars)
{
    double radians;
    double dirx;
    double diry;

    dirx = vars->dirv.x;
    diry = vars->dirv.y;

    radians = to_radians(STEP_ANGLE);
	if (keycode == A) //move left
	{
        vars->posv.x = vars->posv.x + STEP * diry;
        vars->posv.y = vars->posv.y - STEP * dirx;
		return (1);
	}
	else if (keycode == D) //move right
	{
        vars->posv.x = vars->posv.x - STEP * diry;
        vars->posv.y = vars->posv.y + STEP * dirx;
		return (1);
	}
	else if (keycode == W) //move forward
	{
        vars->posv.x = vars->posv.x - STEP * dirx;
        vars->posv.y = vars->posv.y - STEP * diry;
		return (1);
	}
	else if (keycode == S) //move back
	{
        vars->posv.x = vars->posv.x + STEP * dirx;
        vars->posv.y = vars->posv.y + STEP * diry;
		return (1);
	}
    else if (keycode == LEFT) //move top
	{
        rotate_vector(&(vars->dirv), &(vars->dirv), -radians);
		return (1);
	}
    else if (keycode == RIGHT) //
	{
        rotate_vector(&(vars->dirv), &(vars->dirv), radians);
		return (1);
	}
    else if (keycode == UP) //move top
	{
        if (vars->height_ratio + STEP_HEIGHT_RATIO > 0.0 && vars->height_ratio + STEP_HEIGHT_RATIO < 1.0)
            vars->height_ratio += STEP_HEIGHT_RATIO;
		return (1);
	}
    else if (keycode == DOWN) //move top
	{
        if (vars->height_ratio - STEP_HEIGHT_RATIO > 0.0 && vars->height_ratio - STEP_HEIGHT_RATIO < 1.0)
            vars->height_ratio -= STEP_HEIGHT_RATIO;
		return (1);
	}
	return (0);
}

int	key_control(int keycode, t_vars *vars)
{
	if (keycode == 65307)
	{
		//destroy_vars(vars);
		exit(0);
	}
	move_character(keycode, vars);
    // mlx_clear_window(vars->mlx, vars->win);
    render_game(vars);
    //render_game_buf(vars);
	return (0);
}

int mouse_move(int x, int y, t_vars *vars)
{
    double radians;
    int     dx;
    time_t now_time;
    (void)y;

    now_time = get_current_time();
    if (vars->last_mouse_move_t == 0)
    {
        vars->last_mouse_move_t = now_time;
        return (0);
    }
    if (now_time - vars->last_mouse_move_t < TIME_ITVAL_MOUSE)
    {
        vars->last_mouse_move_t = now_time;
        return (0);
    } 
    if (vars->last_mouse_pos.x == -1)
    {
        vars->last_mouse_pos.x = x;
        vars->last_mouse_move_t = now_time;
        return (0);
    }
    dx = x - vars->last_mouse_pos.x;
    vars->last_mouse_pos.x = x;
    radians = to_radians(STEP_ANGLE_MOUSE);
    if (dx < 0)
	{
        rotate_vector(&(vars->dirv), &(vars->dirv), -radians);
	}
    else if (dx > 0)
	{
        rotate_vector(&(vars->dirv), &(vars->dirv), radians);
    }
    render_game(vars);
    vars->last_mouse_move_t = now_time;
    return (0);
}