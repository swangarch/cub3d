/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_distance_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:04:03 by yfan              #+#    #+#             */
/*   Updated: 2024/12/06 19:04:05 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	in_range(double number, double bottom, double top)
{
	if (number >= bottom + MIN_ERR2 && number <= top - MIN_ERR2)
		return (1);
	else
		return (0);
}

int	on_box(t_vars *vars, t_vector *center, t_vector *ist, int index)
{
	double	t_y;
	double	b_y;
	double	l_x;
	double	r_x;

	t_y = center->y + GRID_SIZE / 2.0;
	b_y = center->y - GRID_SIZE / 2.0;
	l_x = center->x - GRID_SIZE / 2.0;
	r_x = center->x + GRID_SIZE / 2.0;
	if (double_eql(ist->x, l_x) && in_range(ist->y, b_y, t_y))
		return (vars->ray_color[index] = WEST,
			vars->ray_poswall[index] = t_y - ist->y, WEST);
	else if (double_eql(ist->x, r_x) && in_range(ist->y, b_y, t_y))
		return (vars->ray_color[index] = EAST,
			vars->ray_poswall[index] = ist->y - b_y, EAST);
	else if (double_eql(ist->y, t_y) && in_range(ist->x, l_x, r_x))
		return (vars->ray_color[index] = NORTH,
			vars->ray_poswall[index] = r_x - ist->x, NORTH);
	else if (double_eql(ist->y, b_y) && in_range(ist->x, l_x, r_x))
		return (vars->ray_color[index] = SOUTH,
			vars->ray_poswall[index] = ist->x - l_x, SOUTH);
	return (NOT_ONBOX);
}

int	get_unit(double num1, double num2)
{
	if (num1 > num2)
		return (1);
	else
		return (-1);
}

double	next_dir_int_dist(double dir, double comp)
{
	if (dir > 0)
		return (ceil(comp) - comp);
	else
		return (comp - floor(comp));
}

void	update_time(t_vector *t_max, t_vector *t_delta)
{
	if (t_max->x < t_max->y)
		t_max->x += t_delta->x;
	else
		t_max->y += t_delta->y;
}
