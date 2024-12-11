/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_distance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:49:51 by yfan              #+#    #+#             */
/*   Updated: 2024/12/06 15:49:54 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	move_timeval(t_vector *intersect, t_vector *posv, \
	double timeval, t_vector *dv)
{
	intersect->x = posv->x + timeval * dv->x;
	intersect->y = posv->y + timeval * dv->y;
}

static void	update_time(t_vector *t_max, t_vector *t_delta)
{
	if (t_max->x < t_max->y)
		t_max->x += t_delta->x;
	else
		t_max->y += t_delta->y;
}

static int	get_unit(double num1, double num2)
{
	if (num1 > num2)
		return (1);
	else
		return (-1);
}

static void	update_map_loc(t_vector *t_max, t_vector *vector, t_vector *map_loc)
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
