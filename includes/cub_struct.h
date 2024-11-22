#ifndef CUB_STRUCT_H
# define CUB_STRUCT_H

# include "cub_define.h"

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			win_w;
	int			win_h;
	int			map_col;
	int			map_row;
	int			num_player;
	char		**map;
	double		player_x;
	double		player_y;
	char		*tex_path[LEN_TEX];
	int			set[LEN_TYPE];
	int			color_f;
	int			color_c;
}	t_game;

#endif
