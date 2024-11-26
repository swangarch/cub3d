#ifndef CUB_STRUCT_H
# define CUB_STRUCT_H

# include "cub_define.h"

typedef struct s_game
{
	int			color_f;
	int			color_c;
	// void		*mlx;
	// void		*win;
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
    double         x;
    double         y;
}	t_vector;

typedef struct s_vars
{
    t_vector    ray[(int)SAMPLE + 1];
    int         ray_color[(int)SAMPLE + 1];
    double      ray_dist[(int)SAMPLE + 1];
    double      ray_poswall[(int)SAMPLE + 1];

    time_t      last_frame_t;
    time_t      last_key_move_t;

    t_vector    posv;
    t_vector    dirv;

    t_vector    last_mouse_pos;
    time_t      last_mouse_move_t;

	void		*mlx;
	void		*win;
	// char		(*map)[9];
    char		**map;

    char        *buf_img;
    void        *buf_img_ptr;
    int         bits_per_pixel;
    int         size_line;
    int         endian;

    void        *tex_w;
    void        *tex_e;
    void        *tex_n;
    void        *tex_s;

    double      height_ratio;
	t_game		*game;
}	t_vars;

#endif
