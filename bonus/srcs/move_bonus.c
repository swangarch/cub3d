/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:33:53 by shuwang           #+#    #+#             */
/*   Updated: 2024/12/03 12:33:53 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d_bonus.h"

static int box_collision(t_vars *vars, t_vector *next_pos)
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

static void set_next_pos(t_vars *vars, t_vector *nx_pos, t_vector *ck_pos, int key)
{
    if (key == W)
        return (nx_pos->x = vars->posv.x + STEP * vars->dirv.x, \
            nx_pos->y = vars->posv.y + STEP * vars->dirv.y, \
            ck_pos->x = vars->posv.x + STEP * CK_STEP * vars->dirv.x, \
            ck_pos->y = vars->posv.y + STEP * CK_STEP * vars->dirv.y, (void)0);
    if (key == S)
        return (nx_pos->x = vars->posv.x - STEP * vars->dirv.x, \
            nx_pos->y = vars->posv.y - STEP * vars->dirv.y, \
            ck_pos->x = vars->posv.x - STEP * CK_STEP * vars->dirv.x, \
            ck_pos->y = vars->posv.y - STEP * CK_STEP * vars->dirv.y, (void)0);
    if (key == A)
        return (nx_pos->x = vars->posv.x + STEP * vars->dirv.y, \
            nx_pos->y = vars->posv.y - STEP * vars->dirv.x, \
            ck_pos->x = vars->posv.x + STEP * CK_STEP * vars->dirv.y, \
            ck_pos->y = vars->posv.y - STEP * CK_STEP * vars->dirv.x, (void)0);
    if (key == D)
        return (nx_pos->x = vars->posv.x - STEP * vars->dirv.y, \
            nx_pos->y = vars->posv.y + STEP * vars->dirv.x, \
            ck_pos->x = vars->posv.x - STEP * CK_STEP * vars->dirv.y, \
            ck_pos->y = vars->posv.y + STEP * CK_STEP * vars->dirv.x, (void)0);
}

static int move_step(t_vars *vars, t_vector *next_pos, t_vector *check_pos, int key)
{
    set_next_pos(vars, next_pos, check_pos, key);
    if (!box_collision(vars, check_pos))
        cpy_scale_vector(&(vars->posv), next_pos, 1.0);
    return (1);
}

int	move_character(t_vars *vars)
{
    t_vector next_pos;
    t_vector check_pos;
    double radians;

    if (vars->key_state[A] == PRESSED)
        move_step(vars, &next_pos, &check_pos, A);
    if (vars->key_state[S] == PRESSED)
        move_step(vars, &next_pos, &check_pos, S);
    if (vars->key_state[D] == PRESSED)
    {
        move_step(vars, &next_pos, &check_pos, D);
    }
	if (vars->key_state[W] == PRESSED)
    {
        move_step(vars, &next_pos, &check_pos, W);
    }
    radians = to_radians(STEP_ANGLE);
    if (vars->key_state[LEFT_INT] == PRESSED) //rotate left
        rotate_vector(&(vars->dirv), &(vars->dirv), -radians);
    if (vars->key_state[RIGHT_INT] == PRESSED) //rotate left
    {
        rotate_vector(&(vars->dirv), &(vars->dirv), radians);
    }
	return (0);
}
