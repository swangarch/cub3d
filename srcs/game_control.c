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
    if (keycode == M && vars->key_state[M] == PRESSED)
        return (vars->key_state[M] = 0, 1);
    if (keycode == O && vars->key_state[O] == PRESSED)
        return (vars->key_state[O] = 0, 1);
    if (keycode == P && vars->key_state[P] == PRESSED)
        return (vars->key_state[P] = 0, 1);
    if (keycode < 128)
        vars->key_state[keycode] = PRESSED;
    else if (keycode == LEFT)
        vars->key_state[LEFT_INT] = PRESSED;
    else if (keycode == RIGHT)
        vars->key_state[RIGHT_INT] = PRESSED;
	return (0);
}

int	key_release(int keycode, t_vars *vars)
{
    if (keycode == M || keycode == P || keycode == O)
        return (1);
    if (keycode < 128)
        vars->key_state[keycode] = RELEASED;
    else if (keycode == LEFT)
        vars->key_state[LEFT_INT] = RELEASED;
    else if (keycode == RIGHT)
        vars->key_state[RIGHT_INT] = RELEASED;
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