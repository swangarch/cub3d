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
    {   
        vars->touch_wall = 1;
        return (1);
    }
    if (vars->map[j][i] == 'C')
    {   
        vars->touch_wall = 1;
        eat(vars, i , j);
        return (1);
    }
    vars->touch_wall = 0;
    return (0);
}

void set_next_pos(t_vars *vars, t_vector *next_pos, t_vector *check_pos, int case_dir)
{
    if (case_dir == W)
    {
        next_pos->x = vars->posv.x + STEP * vars->dirv.x;
        next_pos->y = vars->posv.y + STEP * vars->dirv.y;
        check_pos->x = vars->posv.x + STEP * CHECK_STEP * vars->dirv.x;
        check_pos->y = vars->posv.y + STEP * CHECK_STEP * vars->dirv.y;
    }
    if (case_dir == S)
    {
        next_pos->x = vars->posv.x - STEP * vars->dirv.x;
        next_pos->y = vars->posv.y - STEP * vars->dirv.y;
        check_pos->x = vars->posv.x - STEP * CHECK_STEP * vars->dirv.x;
        check_pos->y = vars->posv.y - STEP * CHECK_STEP * vars->dirv.y;
    }
    if (case_dir == A)
        return (next_pos->x = vars->posv.x + STEP * vars->dirv.y, \
            next_pos->y = vars->posv.y - STEP * vars->dirv.x, \
            check_pos->x = vars->posv.x + STEP * CHECK_STEP * vars->dirv.y, \
            check_pos->y = vars->posv.y - STEP * CHECK_STEP * vars->dirv.x, (void)0);
    if (case_dir == D)
        return (next_pos->x = vars->posv.x - STEP * vars->dirv.y, \
            next_pos->y = vars->posv.y + STEP * vars->dirv.x, \
            check_pos->x = vars->posv.x - STEP * CHECK_STEP * vars->dirv.y, \
            check_pos->y = vars->posv.y + STEP * CHECK_STEP * vars->dirv.x, (void)0);
}

// void set_next_pos_perp(t_vars *vars, t_vector *next_pos, t_vector *check_pos, int case_dir)
// {
//     if (case_dir == A)
// }

int	move_character(t_vars *vars)
{
    t_vector next_pos;
    t_vector check_pos;

    if (vars->key_state[A] == 1)  //move left
	{
        set_next_pos(vars, &next_pos, &check_pos, A);
        if (box_collision(vars, &check_pos))
            return (0);
        cpy_scale_vector(&(vars->posv), &next_pos, 1.0);
	}
    if (vars->key_state[S] == 1) //move forward
	{
        set_next_pos(vars, &next_pos, &check_pos, S);
        if (box_collision(vars, &check_pos))
            return (0);
        cpy_scale_vector(&(vars->posv), &next_pos, 1.0);
	}
    if (vars->key_state[D] == 1)  //move right
	{
        set_next_pos(vars, &next_pos, &check_pos, D);
        if (box_collision(vars, &check_pos))
            return (0);
        cpy_scale_vector(&(vars->posv), &next_pos, 1.0);
	}
	if (vars->key_state[W] == 1) //move back
	{
        set_next_pos(vars, &next_pos, &check_pos, W);
        if (box_collision(vars, &check_pos))
            return (0);
        cpy_scale_vector(&(vars->posv), &next_pos, 1.0);
	}
    if (vars->key_state[LEFT_INT] == 1) //rotate left
        rotate_vector(&(vars->dirv), &(vars->dirv), -to_radians(STEP_ANGLE));
    if (vars->key_state[RIGHT_INT] == 1) //rotate left
        rotate_vector(&(vars->dirv), &(vars->dirv), to_radians(STEP_ANGLE));
	return (0);
}

int cross_press(t_vars *vars)
{
    destroy_vars(vars);
    exit(0);
}

int	key_press(int keycode, t_vars *vars)
{
	if (keycode == 65307)//esc
	{
		destroy_vars(vars);
		exit(0);
	}
    if (keycode == M && vars->key_state[M] == 1)
        return (vars->key_state[M] = 0, 1);
    if (keycode == O && vars->key_state[O] == 1)
        return (vars->key_state[O] = 0, 1);
    if (keycode == P && vars->key_state[P] == 1)
        return (vars->key_state[P] = 0, 1);
    if (keycode < 128)
        vars->key_state[keycode] = 1;
    else if (keycode == LEFT)
        vars->key_state[LEFT_INT] = 1;
    else if (keycode == RIGHT)
        vars->key_state[RIGHT_INT] = 1;
	return (0);
}

int	key_release(int keycode, t_vars *vars)
{
    if (keycode == M || keycode == P || keycode == O)
        return (1);
    if (keycode < 128)
        vars->key_state[keycode] = 0;
    else if (keycode == LEFT)
        vars->key_state[LEFT_INT] = 0;
    else if (keycode == RIGHT)
        vars->key_state[RIGHT_INT] = 0;
	return (0);
}

int mouse_move(int x, int y, t_vars *vars)
{
    int     dx;
    double  radians;
    (void)y;

    if (x < SCREEN_WIDTH / 5.0 * 1.5)
        vars->mouse_move_dir = 1 * (SCREEN_WIDTH / 5.0 * 1.5 - x);
    else if (x > SCREEN_WIDTH / 5.0 * 3.5)
        vars->mouse_move_dir = -1 * (x - SCREEN_WIDTH / 5.0 * 3.5);
    else
        vars->mouse_move_dir = 0;
    return (0);
}

void rotate_when_mouse_move(t_vars *vars)
{
    double radians;
    radians = to_radians(STEP_ANGLE_MOUSE);
    if (vars->mouse_move_dir != 0)
    {
        rotate_vector(&(vars->dirv), &(vars->dirv), -radians * vars->mouse_move_dir);
    }
}