/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 20:27:22 by shuwang           #+#    #+#             */
/*   Updated: 2024/11/29 20:27:23 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	set_ray_obj_dist(t_vars *vars, t_vector *player_to_obj, int i)
{
	if (ft_abs(vars->ray_obj_dist_pt_ln[i]) <= 0.5 && \
		dot_product(player_to_obj, &vars->ray_obj[i]) > 0)
		vars->ray_obj_dist[i] = len_2pt(&vars->posv, &vars->pos_obj);
	else
		vars->ray_obj_dist[i] = 0;
}

void	cal_render_obj(t_vars *vars, double radians, int i)
{
	t_vector	camera;
	t_vector	sample_vector;
	t_vector	start_vector;
	t_vector	player_to_obj;

	vector_2pt(&player_to_obj, &vars->pos_obj, &vars->posv);
	rotate_vector(&camera, &(vars->dirv), to_radians(90));
	normalize_vector(&camera, tan(to_radians(FOV / 2)));
	cpy_scale_vector(&sample_vector, &camera, 2.0 / SAMPLE);
	cpy_scale_vector(&start_vector, &sample_vector, -SAMPLE / 2.0);
	while (++i < (int)SAMPLE)
	{
		add_vector(&vars->ray_obj[i], &vars->dirv, &start_vector);
		radians = atan(vector_magnitude(&start_vector) / \
			vector_magnitude(&vars->dirv));
		vars->ray_obj_dist_pt_ln[i] = dist_line_pt(&vars->posv, \
			&vars->ray_obj[i], &vars->pos_obj);
		set_ray_obj_dist(vars, &player_to_obj, i);
		normalize_vector(&vars->ray_obj[i], vars->ray_obj_dist[i]);
		vars->ray_obj_dist[i] = vars->ray_obj_dist[i] * cos(radians);
		add_vector(&start_vector, &start_vector, &sample_vector);
	}
}

static void	render_obj_pixel(t_vars *vars, int *p_screen, int color, int i)
{
	int	x;
	int	y;

	if (get_t(color) >= 1)
		return ;
	x = p_screen[0];
	y = p_screen[1];
	if (vars->key_state[O])
		color = fade_color(color, vars->ray_obj_dist[i]);
	put_pixel_to_buf(vars, x, y, color);
}

static int	set_bottom_index(double wall_height)
{
	int	j;

	j = 0;
	if (DISPLAY_H / 2.0 - wall_height / 2.0 + j < 0)
		j = wall_height / 2 - DISPLAY_H / 2.0;
	return (j);
}

void	draw_obj(t_vars *vars, int i, int j)
{
	t_vector	pos_on_obj;
	double		wall_height;
	int			pos_screen[2];

	if (vars->pos_obj.x <= 0 || vars->pos_obj.y <= 0)
		return ;
	while (++i < (int)SAMPLE)
	{
		if (vars->ray_dist[i] < vars->ray_obj_dist[i])
			continue ;
		wall_height = DISPLAY_H / vars->ray_obj_dist[i] * HEIGHT_RATIO;
		pos_on_obj.x = (vars->ray_obj_dist_pt_ln[i] + 0.5) * TEXTURE_SIZE;
		pos_screen[0] = POSITION_X + i * (DISPLAY_W / SAMPLE);
		j = set_bottom_index(wall_height) - 1;
		while (j < (int)(wall_height))
		{
			pos_screen[1] = DISPLAY_H / 2.0 - wall_height / 2.0 + (double)j;
			if (pos_screen[1] > DISPLAY_H)
				break ;
			pos_on_obj.y = j / wall_height * TEXTURE_SIZE;
			render_obj_pixel(vars, pos_screen,
				get_texcolor(vars->tex_object, &pos_on_obj, -1), i);
			j++;
		}
	}
}
