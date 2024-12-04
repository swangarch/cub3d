/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:16:48 by shuwang           #+#    #+#             */
/*   Updated: 2024/12/03 13:16:49 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void draw_visibility(t_vars *vars, double size)
{
    t_vector *ray;
    ray = vars->ray;
    int i = 0;

    t_vector startpt_scaled;
    t_vector endpt_added;
    t_vector endpt_scaled;
    while (i < (int)SAMPLE)
    {
        cpy_scale_vector(&startpt_scaled, &(vars->posv), size);
        add_vector(&endpt_added, &(vars->posv), &ray[i]);
        cpy_scale_vector(&endpt_scaled, &endpt_added, size);
        draw_line(vars, &startpt_scaled, &endpt_scaled, YELLOW);
        i++;
    }
}

static void draw_current_pos(t_vars *vars, t_vector *pos, int* index, int color)
{
    t_vector pos_pixel;

    pos_pixel.x = pos->x + index[0] * vars->map_size + vars->map_size / 2.0;
    pos_pixel.y = pos->y + index[1] * vars->map_size + vars->map_size / 2.0;
    draw_box(vars, &pos_pixel, vars->map_size, color);
}

void draw_map_background(t_vars *vars, t_vector *pos)
{
    int i;
    int j;
    int index[2];

    j = 0;
    while (vars->map[j])  //map issue map 14
    {
        i = 0;
        while (vars->map[j][i])
        {
            index[0] = i;
            index[1] = j;
            if ( vars->map[j][i] == '0' || vars->map[j][i] == '1' || vars->map[j][i] == 'N' || vars->map[j][i] == 'S' || vars->map[j][i] == 'E' || vars->map[j][i] == 'W' ||  vars->map[j][i] == 'C')
                draw_current_pos(vars, pos, index, GREY_L);
            i++;
        }
        j++;
    }
}

void draw_map_element(t_vars *vars, t_vector *pos, int i, int j)
{
    t_vector pos_pixel;
    int index[2];
    
    while (vars->map[++j])
    {
        i = -1;
        while (vars->map[j][++i])
        {
            index[0] = i;
            index[1] = j;
            if (vars->map[j][i] == '1')
            {
                pos_pixel.x = pos->x + vars->map_size * (i + 0.5 + SHADSIZ);
                pos_pixel.y = pos->y + vars->map_size * (j + 0.5 + SHADSIZ);
                draw_box(vars, &pos_pixel, vars->map_size, GREY_M);
            }
            if (vars->map[j][i] == '1')
                draw_current_pos(vars, pos, index, WHITE);
            if (vars->map[j][i] == 'N' || vars->map[j][i] == 'S' || vars->map[j][i] == 'E' || vars->map[j][i] == 'W')
                draw_current_pos(vars, pos, index, CYAN);
        }
    }
    draw_visibility(vars, vars->map_size);
}
// void draw_map_obj(t_vars *vars, double x, double y)
// {
//     int i;
//     int j;
//     t_vector pos_pixel;

//     j = 0;
//     while (vars->map[j])
//     {
//         i = 0;
//         while (vars->map[j][i])
//         {
//             if (vars->map[j][i] == 'C')
//             {
//                 pos_pixel.x = x + i * vars->map_size *1 + vars->map_size / 2.0;
//                 pos_pixel.y = y + j * vars->map_size + vars->map_size / 2.0;
//                 draw_box(vars, &pos_pixel, vars->map_size, RED);
//             }
//             i++;
//         }
//         j++;
//     }
//     draw_obj_visibility(vars, vars->map_size);
// }

void draw_map(t_vars *vars, double x, double y)
{
    t_vector pos;
    t_vector player_pos;

    if (!vars->key_state[M])
        return ;
    if (vars->key_state[NUM_0])
        vars->map_size += 0.11;
    if (vars->key_state[NUM_9] && vars->map_size >= 7.0)
        vars->map_size -= 0.11;
    if ((vars->game->map_col - 1) * vars->map_size > SCREEN_WIDTH)
        vars->map_size = SCREEN_WIDTH / (double)(vars->game->map_col - 1);
    if ((vars->game->map_row) * vars->map_size > SCREEN_HEIGHT)
        vars->map_size = SCREEN_HEIGHT / (double)(vars->game->map_row);
    pos.x = x;
    pos.y = y;
    draw_map_background(vars, &pos);
    draw_map_element(vars, &pos, -1, -1);
    cpy_scale_vector(&player_pos, &vars->posv, vars->map_size);
    draw_box(vars, &player_pos, vars->map_size / 2.0, RED);
    //draw_map_obj(vars, x, y);
}
