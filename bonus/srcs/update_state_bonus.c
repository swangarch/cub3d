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

# include "../includes/cub3d_bonus.h"

void    life(t_vars *vars)
{
    if ((vars->key_state[W] || vars->key_state[A] || vars->key_state[S] || \
        vars->key_state[D]) && !vars->touch_wall)
    {
        if (vars->hp < 1.0)
            vars->hp += 0.001;
        return;
    }
    if (vars->hp > 0)
        vars->hp -= 0.0005;
    else
    {
        destroy_vars(vars);
        ft_putstr_fd("Game over!\n", 1);
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
        destroy_vars(vars);
        ft_putstr_fd("Congratulations, You win!\n", 1);
        exit(0);
    }
}

void    update_animation_frame(t_vars *vars)
{
    if (get_current_time() % 4000000 < 2000000)
    {
        vars->tex_s = vars->tex_s_1;
        vars->tex_w = vars->tex_w_1;
        vars->tex_object = vars->tex_object_1;
    }
    else
    {
        vars->tex_s = vars->tex_s_2;
        vars->tex_w = vars->tex_w_2;
        vars->tex_object = vars->tex_object_2;
    }
}

void    update_state(t_vars *vars)
{
    life(vars);
    update_animation_frame(vars);
}
