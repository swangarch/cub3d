/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:12:37 by yfan              #+#    #+#             */
/*   Updated: 2024/12/06 16:12:39 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_STRUCT_H
# define CUB_STRUCT_H

# include "cub_define.h"

typedef struct s_game
{
	int			color_f;
	int			color_c;
	int			dir_player;
	int			map_col;
	int			map_row;
	int			num_player;
	char		**map;
	double		player_x;
	double		player_y;
	char		*tex_path[LEN_TEX];
	int			set[LEN_TYPE];
}	t_game;

typedef struct s_vector
{
	double		x;
	double		y;
}	t_vector;

typedef struct s_drawl
{
	int		x0;
	int		y0;
	int		x1;
	int		y1;
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;
}	t_drawl;

typedef struct s_vars
{
	t_vector	ray[(int)SAMPLE];
	int			ray_color[(int)SAMPLE];
	double		ray_dist[(int)SAMPLE];
	double		ray_poswall[(int)SAMPLE];
	time_t		last_frame_t;
	t_vector	posv;
	t_vector	dirv;
	double		mouse_move_dir;
	t_vector	last_mouse_pos;
	int			key_state[256];
	int			touch_wall;
	int			show_map;
	double		map_size;
	int			show_fps;
	int			fade;
	int			shadow;
	void		*mlx;
	void		*win;
	char		**map;
	char		*buf_img;
	void		*buf_img_ptr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	void		*tex_w;
	void		*tex_e;
	void		*tex_n;
	void		*tex_s;
	t_game		*game;
}	t_vars;

#endif
