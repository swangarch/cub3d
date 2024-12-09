/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:25:49 by shuwang           #+#    #+#             */
/*   Updated: 2024/11/22 15:25:51 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	move_first(t_vars *vars, t_vector *t_max, t_vector *t_delta, int i)
{
	t_max->x = next_dir_int_dist(vars->ray[i].x, vars->posv.x);
	t_max->y = next_dir_int_dist(vars->ray[i].y, vars->posv.y);
	if (vars->ray[i].x != 0)
	{
		t_max->x /= ft_abs(vars->ray[i].x);
		t_delta->x = 1.0 / ft_abs(vars->ray[i].x);
	}
	else
	{
		t_max->x = VERY_LARGE_VALUE;
		t_delta->x = VERY_LARGE_VALUE;
	}
	if (vars->ray[i].y != 0)
	{
		t_max->y /= ft_abs(vars->ray[i].y);
		t_delta->y = 1.0 / ft_abs(vars->ray[i].y);
	}
	else
	{
		t_max->y = VERY_LARGE_VALUE;
		t_delta->x = VERY_LARGE_VALUE;
	}
}

void	move_timeval(t_vector *intersect, t_vector *posv, \
	double timeval, t_vector *dv)
{
	intersect->x = posv->x + timeval * dv->x;
	intersect->y = posv->y + timeval * dv->y;
}

void	update_map_loc(t_vector *t_max, t_vector *vector, t_vector *map_loc)
{
	if (t_max->x < t_max->y)
		map_loc->x += get_unit(vector->x, 0);
	else
		map_loc->y += get_unit(vector->y, 0);
}

double	wall_distance(t_vars *vars, t_vector *vector, int index)
{
	t_vector	t_max;
	t_vector	t_delta;
	t_vector	map_loc;
	t_vector	intersect;
	double		distance;

	move_first(vars, &t_max, &t_delta, index);
	first_pos(vars, &map_loc, &vars->posv, &intersect);
	while (1)
	{
		update_map_loc(&t_max, vector, &map_loc);
		if (t_max.x < t_max.y)
			move_timeval(&intersect, &vars->posv, t_max.x, vector);
		else
			move_timeval(&intersect, &vars->posv, t_max.y, vector);
		update_time(&t_max, &t_delta);
		distance = hit_wall(vars, &intersect, index, map_loc);
		if (distance >= 0)
			return (distance);
		if (len_2pt(&(vars->posv), &intersect) > MAX_VIEW_DISTANCE)
			return (MAX_VIEW_DISTANCE);
	}
	return (0);
}

double	hit_wall(t_vars *vars, t_vector *intersect, int index, \
	t_vector map_loc)
{
	t_vector	box_pos;
	double		distance;

	if (map_loc.x >= vars->game->map_col - 1 \
		|| map_loc.y >= vars->game->map_row || map_loc.x < 0 \
		|| map_loc.y < 0)
		return (-1);
	if (vars->map[(int)map_loc.y][(int)map_loc.x] == '1')
	{
		box_pos.x = map_loc.x + GRID_SIZE / 2.0;
		box_pos.y = map_loc.y + GRID_SIZE / 2.0;
		if (on_box(vars, &box_pos, intersect, index) != NOT_ONBOX)
		{
			distance = len_2pt(&(vars->posv), intersect);
			return (distance);
		}
	}
	return (-1);
}
