#ifndef CUB_STRUCT_H
# define CUB_STRUCT_H

# include "cub_define_bonus.h"
# include <sys/time.h>

typedef struct s_game
{
	int			color_f;
	int			color_c;
    int         dir_player;//+++++++++++++++++++
	int			map_col;
	int			map_row;
	int			num_player;
    int         num_eat;
    int         eat_access;
	char		**map;
	double		player_x;
	double		player_y;
    double      eat_x;
    double      eat_y;
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
    t_vector    ray[(int)SAMPLE];
    int         ray_color[(int)SAMPLE];
    double      ray_dist[(int)SAMPLE];
    double      ray_poswall[(int)SAMPLE];

    t_vector    ray_obj[(int)SAMPLE];
    int         ray_obj_color[(int)SAMPLE];

    double      ray_obj_dist[(int)SAMPLE];
    double      ray_obj_pos[(int)SAMPLE];
    double      ray_obj_dist_pt_ln[(int)SAMPLE];

    time_t      last_frame_t;

    t_vector    posv;
    t_vector    dirv;

    double      mouse_move_dir;
    t_vector    last_mouse_pos;
    int         key_state[256];
    double      height_ratio;

    double      hp;
    int         touch_wall;
    int         show_map;
    double      map_size;

    int         show_fps;


    int         fade;
    int         shadow;

	void		*mlx;
	void		*win;
    char		**map;
    t_vector    pos_obj;
    char        *buf_img;
    void        *buf_img_ptr;
    int         bits_per_pixel;
    int         size_line;
    int         endian;

    void        *tex_w;
    void        *tex_e;
    void        *tex_n;
    void        *tex_s;
    void        *tex_s_1;
    void        *tex_w_1;
    void        *tex_s_2;
    void        *tex_w_2;

    void        *tex_c;
    void        *tex_f;

    void        *tex_object;

	t_game		*game;
}	t_vars;

#endif
