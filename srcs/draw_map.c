#include "../includes/cub3d.h"

void draw_visibility(t_vars *vars, double size)
{
    t_vector *ray;
    ray = vars->ray;
    int i = 0;

    t_vector startpt_scaled;
    t_vector endpt_added;
    t_vector endpt_scaled;
    while (i < (int)SAMPLE)///////////////////////////////
    {
        cpy_scale_vector(&startpt_scaled, &(vars->posv), size);
        add_vector(&endpt_added, &(vars->posv), &ray[i]);
        cpy_scale_vector(&endpt_scaled, &endpt_added, size);
        draw_line(vars, &startpt_scaled, &endpt_scaled, YELLOW);
        i++;
    }
}

void draw_map_shadow(t_vars *vars, double x, double y)
{
    int i;
    int j;

    j = 0;
    while (vars->map[j])  //map issue map 14
    {
        i = 0;
        while (vars->map[j][i])
        {
            if ( vars->map[j][i] == '0' || vars->map[j][i] == '1' || vars->map[j][i] == 'N' || vars->map[j][i] == 'S' || vars->map[j][i] == 'E' || vars->map[j][i] == 'W' ||  vars->map[j][i] == 'C')
                draw_box(vars, x + i * vars->map_size *1 + vars->map_size / 2.0, y + j * vars->map_size + vars->map_size / 2.0, vars->map_size, GREY_L);
            i++;
        }
        j++;
    }
}

void draw_map_element(t_vars *vars, double x, double y)
{
    int i;
    int j;

    j = 0;
    while (vars->map[j])
    {
        i = 0;
        while (vars->map[j][i])
        {
            if (vars->map[j][i] == '1')
                 draw_box(vars, x + i * vars->map_size *1 + vars->map_size / 2.0 + vars->map_size * MAP_SHADOW_SIZE, y + j * vars->map_size + vars->map_size / 2.0 + vars->map_size * MAP_SHADOW_SIZE, vars->map_size, GREY_M);
            if (vars->map[j][i] == '1')
                 draw_box(vars, x + i * vars->map_size *1 + vars->map_size / 2.0, y + j * vars->map_size + vars->map_size / 2.0, vars->map_size, WHITE);
            if (vars->map[j][i] == 'N' || vars->map[j][i] == 'S' || vars->map[j][i] == 'E' || vars->map[j][i] == 'W')
                 draw_box(vars, x + i * vars->map_size *1 + vars->map_size / 2.0, y + j * vars->map_size + vars->map_size / 2.0, vars->map_size, CYAN);
            i++;
        }
        j++;
    }
    draw_visibility(vars, vars->map_size);
}

void draw_map_obj(t_vars *vars, double x, double y)
{
    int i;
    int j;

    j = 0;
    while (vars->map[j])
    {
        i = 0;
        while (vars->map[j][i])
        {
            if (vars->map[j][i] == 'C')
                 draw_box(vars, x + i * vars->map_size *1 + vars->map_size / 2.0, y + j * vars->map_size + vars->map_size / 2.0, vars->map_size, RED);
            i++;
        }
        j++;
    }
    draw_obj_visibility(vars, vars->map_size);
}

void draw_map(t_vars *vars, double x, double y)
{
    if (!vars->key_state[M])
        return ;
    if (vars->key_state[NUM_0])
        vars->map_size += 0.1;
    if (vars->key_state[NUM_9] && vars->map_size >= 7.0)
        vars->map_size -= 0.1;
    if ((vars->game->map_col - 1) * vars->map_size > SCREEN_WIDTH)
        vars->map_size = SCREEN_WIDTH / (double)(vars->game->map_col - 1);
    if ((vars->game->map_row) * vars->map_size > SCREEN_HEIGHT)
        vars->map_size = SCREEN_HEIGHT / (double)(vars->game->map_row);
    draw_map_shadow(vars, x, y);
    draw_map_element(vars, x, y);
    //draw_map_obj(vars, x, y);
}