/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:26:13 by shuwang           #+#    #+#             */
/*   Updated: 2024/11/28 16:26:14 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d.h"

// void    damage()

void    life(t_vars *vars)
{
    if ((vars->key_state[W] || vars->key_state[A] || vars->key_state[S] || vars->key_state[D]) && !vars->touch_wall)
    {
        if (vars->hp < 1.0)
            vars->hp += 0.002;
        return;
    }
    if (vars->hp > 0)
        vars->hp -= 0.001;
    else
    {
        //destroy vars
        ft_putstr_fd("Game over\n", 1);
        exit(0);
    }
}

void    eat(t_vars *vars, int i, int j)
{
    if (vars->key_state[E])
    {
        vars->map[j][i] = '0';
        vars->pos_obj.x = -1;
        vars->pos_obj.y = -1;
        if (vars->hp += 0.5 > 1.0)
            vars->hp = 1;
        else
            vars->hp += 0.5;
        ft_putstr_fd("Get one object\n", 1);
    }
}

void    update_state(t_vars *vars)
{
    life(vars);
}
