/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sky_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:34:50 by yfan              #+#    #+#             */
/*   Updated: 2024/12/06 17:34:51 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	draw_sky(t_vars *vars, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < SCREEN_WIDTH)
	{
		j = 0;
		while (j < SCREEN_HEIGHT)
		{
			if (j < SCREEN_HEIGHT / 2)
				put_pixel_to_buf(vars, i, j, color);
			j++;
		}
		i++;
	}
}

static void	set_tex_sky(t_tex *tex, t_vars *vars)
{
	tex->floor_x = tex->row_distances_sky[tex->y] * HEIGHT_RATIO * \
		(tex->ray_dir_left.x + (tex->x / (double)SCREEN_WIDTH) * \
		(tex->ray_dir_right.x - tex->ray_dir_left.x));
	tex->floor_y = tex->row_distances_sky[tex->y] * HEIGHT_RATIO * \
		(tex->ray_dir_left.y + (tex->x / (double)SCREEN_WIDTH) * \
		(tex->ray_dir_right.y - tex->ray_dir_left.y));
	tex->tex_sky.x = (int)(tex->floor_x * TEXTURE_SIZE / 3.0) % TEXTURE_SIZE;
	tex->tex_sky.y = (int)(tex->floor_y * TEXTURE_SIZE / 3.0) % TEXTURE_SIZE;
	if (tex->tex_sky.x < 0)
		tex->tex_sky.x += TEXTURE_SIZE;
	if (tex->tex_sky.y < 0)
		tex->tex_sky.y += TEXTURE_SIZE;
	tex->pixel_color = get_texcolor(vars->tex_c, &tex->tex_sky, -1);
	put_pixel_to_buf(vars, tex->x, tex->y, tex->pixel_color);
}

void	render_sky_texture(t_vars *vars)
{
	t_tex	tex;

	init_info_floor_sky(&tex, vars);
	tex.y = 0;
	while (tex.y < SCREEN_HEIGHT)
	{
		if (tex.y < SCREEN_HEIGHT / 2)
		{
			tex.x = 0;
			while (tex.x < SCREEN_WIDTH)
			{
				set_tex_sky(&tex, vars);
				tex.x++;
			}
		}
		tex.y++;
	}
}

void	fill_rec(t_vars *vars, t_vector *pt1, t_vector *pt2, int color)
{
	t_vector	nw;
	t_vector	ne;
	int			i;

	nw.x = pt1->x;
	nw.y = pt1->y;
	ne.x = pt2->x;
	ne.y = pt1->y;
	i = 0;
	while (i < pt2->y - pt1->y)
	{
		draw_line(vars, &nw, &ne, color);
		nw.y++;
		ne.y++;
		i++;
	}
}
