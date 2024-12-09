/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_sky.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:37:13 by shuwang           #+#    #+#             */
/*   Updated: 2024/12/03 11:37:14 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	draw_ground(t_vars *vars, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < SCREEN_WIDTH)
	{
		j = 0;
		while (j < SCREEN_HEIGHT)
		{
			if (j >= SCREEN_HEIGHT / 2)
				put_pixel_to_buf(vars, i, j, color);
			j++;
		}
		i++;
	}
}

void	init_info_floor_sky(t_tex *tex, t_vars *vars)
{
	tex->y = SCREEN_HEIGHT / 2 - 1;
	while (tex->y >= 0)
	{
		tex->row_distances_sky[tex->y] = (SCREEN_HEIGHT / 2.0) / \
			(SCREEN_HEIGHT / 2.0 - tex->y);
		tex->y--;
	}
	tex->y = SCREEN_HEIGHT / 2;
	while (tex->y < SCREEN_HEIGHT)
	{
		tex->row_distances[tex->y] = (SCREEN_HEIGHT / 2.0) / \
			(tex->y - SCREEN_HEIGHT / 2.0);
		tex->y++;
	}
	rotate_vector(&tex->camera, &(vars->dirv), to_radians(90));
	normalize_vector(&tex->camera, tan(to_radians(FOV / 2)));
	tex->ray_dir_left.x = vars->dirv.x - tex->camera.x;
	tex->ray_dir_left.y = vars->dirv.y - tex->camera.y;
	tex->ray_dir_right.x = vars->dirv.x + tex->camera.x;
	tex->ray_dir_right.y = vars->dirv.y + tex->camera.y;
}

void	set_tex_floor(t_tex *tex, t_vars *vars)
{
	tex->floor_x = vars->posv.x + tex->row_distances[tex->y] * HEIGHT_RATIO * \
		(tex->ray_dir_left.x + (tex->x / (double)SCREEN_WIDTH) * \
		(tex->ray_dir_right.x - tex->ray_dir_left.x));
	tex->floor_y = vars->posv.y + tex->row_distances[tex->y] * HEIGHT_RATIO * \
		(tex->ray_dir_left.y + (tex->x / (double)SCREEN_WIDTH) * \
		(tex->ray_dir_right.y - tex->ray_dir_left.y));
	tex->tex_floor.x = (int)(tex->floor_x * TEXTURE_SIZE / 1.0) % TEXTURE_SIZE;
	tex->tex_floor.y = (int)(tex->floor_y * TEXTURE_SIZE / 1.0) % TEXTURE_SIZE;
	if (tex->tex_floor.x < 0)
		tex->tex_floor.x += TEXTURE_SIZE;
	if (tex->tex_floor.y < 0)
		tex->tex_floor.y += TEXTURE_SIZE;
	tex->pixel_color = get_texcolor(vars->tex_f, &tex->tex_floor, -1);
	put_pixel_to_buf(vars, tex->x, tex->y, tex->pixel_color);
}

void	render_floor_texture(t_vars *vars)
{
	t_tex	tex;

	init_info_floor_sky(&tex, vars);
	tex.y = 0;
	while (tex.y < SCREEN_HEIGHT)
	{
		if (tex.y >= SCREEN_HEIGHT / 2)
		{
			tex.x = 0;
			while (tex.x < SCREEN_WIDTH)
			{
				set_tex_floor(&tex, vars);
				tex.x++;
			}
		}
		tex.y++;
	}
}

void	render_floor_sky(t_vars *vars)
{
	if (vars->tex_f)
		render_floor_texture(vars);
	else
		draw_ground(vars, vars->game->color_f);
	if (vars->tex_c)
		render_sky_texture(vars);
	else
		draw_sky(vars, vars->game->color_c);
}
