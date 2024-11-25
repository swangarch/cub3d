#ifndef CUB_STRUCT_H
# define CUB_STRUCT_H

# include "cub_define.h"

typedef struct s_game
{
	int			color_f;
	int			color_c;
	void		*mlx;
	void		*win;
	int			map_col;
	int			map_row;
	int			num_player;
	char		**map;
	double		player_x;
	double		player_y;
	char		*tex_path[LEN_TEX];
	int			set[LEN_TYPE];
}	t_game;

#endif
