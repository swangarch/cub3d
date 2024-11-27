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

# include "../includes/cub3d.h"

int box_collision(t_vars *vars, t_vector *next_pos)
{
    int i;
    int j;

    i = (int)floor(next_pos->x);
    j = (int)floor(next_pos->y);
    if (vars->map[j][i] == '1')
        return (1);
    return (0);
}

int	move_character(t_vars *vars)
{
    double radians;
    double dirx;
    double diry;
    time_t now_time;
    t_vector next_pos;

    now_time = get_current_time();
    dirx = vars->dirv.x;
    diry = vars->dirv.y;
    radians = to_radians(STEP_ANGLE);
    if (vars->key_state[A] == 1)  //move left
	{
        next_pos.x = vars->posv.x + STEP * diry;
        next_pos.y = vars->posv.y - STEP * dirx;
        if (box_collision(vars, &next_pos))
            return (0);
        cpy_scale_vector(&(vars->posv), &next_pos, 1.0);
		return (1);
	}
    else if (vars->key_state[D] == 1)  //move right
	{
        next_pos.x = vars->posv.x - STEP * diry;
        next_pos.y = vars->posv.y + STEP * dirx;
        if (box_collision(vars, &next_pos))
            return (0);
        cpy_scale_vector(&(vars->posv), &next_pos, 1.0);
		return (1);
	}
	else if (vars->key_state[S] == 1) //move forward
	{
        next_pos.x = vars->posv.x - STEP * dirx;
        next_pos.y = vars->posv.y - STEP * diry;
        if (box_collision(vars, &next_pos))
            return (0);
        cpy_scale_vector(&(vars->posv), &next_pos, 1.0);
		return (1);
	}
	else if (vars->key_state[W] == 1) //move back
	{
        next_pos.x = vars->posv.x + STEP * dirx;
        next_pos.y = vars->posv.y + STEP * diry;
        if (box_collision(vars, &next_pos))
            return (0);
        cpy_scale_vector(&(vars->posv), &next_pos, 1.0);
		return (1);
	}
    else if (vars->key_state[LEFT_INT] == 1) //move top
	{
        rotate_vector(&(vars->dirv), &(vars->dirv), -radians);
		return (1);
	}
    else if (vars->key_state[RIGHT_INT] == 1) //
	{
        rotate_vector(&(vars->dirv), &(vars->dirv), radians);
		return (1);
	}
    else if (vars->key_state[UP_INT] == 1) //move top
	{
        if (vars->height_ratio + STEP_HEIGHT_RATIO > 0.0 && vars->height_ratio + STEP_HEIGHT_RATIO < 1.0)
            vars->height_ratio += STEP_HEIGHT_RATIO;
		return (1);
	}
    else if (vars->key_state[DOWN_INT] == 1) //move top
	{
        if (vars->height_ratio - STEP_HEIGHT_RATIO > 0.0 && vars->height_ratio - STEP_HEIGHT_RATIO < 1.0)
            vars->height_ratio -= STEP_HEIGHT_RATIO;
		return (1);
	}
	return (0);
}

int cross_press(t_vars *vars)
{
    //destroy_vars(vars);
    exit(0);
}

int	key_press(int keycode, t_vars *vars)
{
	if (keycode == 65307)//esc
	{
		//destroy_vars(vars);
		exit(0);
	}
    if (keycode < 128)
        vars->key_state[keycode] = 1;
    else if (keycode == LEFT)
        vars->key_state[LEFT_INT] = 1;
    else if (keycode == RIGHT)
        vars->key_state[RIGHT_INT] = 1;
    else if (keycode == UP)
        vars->key_state[UP_INT] = 1;
    else if (keycode == DOWN)
        vars->key_state[DOWN_INT] = 1;
	return (0);
}

int	key_release(int keycode, t_vars *vars)
{
    if (keycode < 128)
        vars->key_state[keycode] = 0;
    else if (keycode == LEFT)
        vars->key_state[LEFT_INT] = 0;
    else if (keycode == RIGHT)
        vars->key_state[RIGHT_INT] = 0;
    else if (keycode == UP)
        vars->key_state[UP_INT] = 0;
    else if (keycode == DOWN)
        vars->key_state[DOWN_INT] = 0;
	return (0);
}

// int mouse_move(int x, int y, t_vars *vars)
// {
//     int     dx;
//     (void)y;

//     if (vars->last_mouse_pos.x == -1)
//     {
//         vars->last_mouse_pos.x = x;
//         // vars->last_mouse_move_t = now_time;
//         return (0);
//     }
//     dx = x - vars->last_mouse_pos.x;
//     vars->last_mouse_pos.x = x;
//     //radians = to_radians(STEP_ANGLE_MOUSE);
//     if (dx < 0)
// 	{
//         vars->mouse_move_dir = 1;
//         //rotate_vector(&(vars->dirv), &(vars->dirv), -radians);
// 	}
//     else if (dx > 0)
// 	{
//         vars->mouse_move_dir = -1;
//         //rotate_vector(&(vars->dirv), &(vars->dirv), radians);
//     }
//     else
//     {
//         vars->mouse_move_dir = 0;
//     }
//     return (0);
// }

int mouse_move(int x, int y, t_vars *vars)
{
    int     dx;
    (void)y;

    if (x < SCREEN_WIDTH / 5.0 * 1.5)
	{
        vars->mouse_move_dir = 1 * (SCREEN_WIDTH / 5.0 * 1.5 - x);
	}
    else if (x > SCREEN_WIDTH / 5.0 * 3.5)
	{
        vars->mouse_move_dir = -1 * (x - SCREEN_WIDTH / 5.0 * 3.5);
    }
    else
    {
        vars->mouse_move_dir = 0;
    }
    return (0);
}

void rotate_when_mouse_move(t_vars *vars)
{
    double radians;
    radians = to_radians(STEP_ANGLE_MOUSE);
    // if (vars->mouse_move_dir > 0)
    // {
    //     rotate_vector(&(vars->dirv), &(vars->dirv), - radians * vars->mouse_move_dir);
    // }
    // else if(vars->mouse_move_dir < 0)
    // {
    //     rotate_vector(&(vars->dirv), &(vars->dirv), radians * vars->mouse_move_dir);
    // }
    if (vars->mouse_move_dir != 0)
    {
        rotate_vector(&(vars->dirv), &(vars->dirv), - radians * vars->mouse_move_dir);
    }
}