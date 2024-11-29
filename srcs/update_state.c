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
        vars->hp -= 0.0005;
    else
    {
        //destroy vars
        ft_putstr_fd("Game over\n", 1);
        exit(0);
    }
}

void    update_state(t_vars *vars)
{
    life(vars);
}

