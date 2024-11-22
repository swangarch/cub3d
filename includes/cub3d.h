#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/libft.h"
# include <fcntl.h>
# include "cub_define.h"
# include "cub_struct.h"
# include "../mlx/mlx.h"

void	map_error(char *str);
void	start_game(t_game *game);
int		update(t_game *game);
int	check_map_name(char *str);
int	parse_map(t_game *game, char *path_map);
int	parse_oneline(t_game *game, char *line, t_list **map);
void	init_game(t_game *game);
int	check_tex_type(char *line);
int	parse_texture(t_game *game, int type, char *line);
void	free_char_array(char **array);
int	parse_color(t_game *game, int type, char *line);
int	len_char_array(char **str);
int	ft_in_set(char c, const char *set);
int	check_color_range(int *color, char **part_color);
int	lst_add_back_buffer(t_list **map, char *line);
int	set_map_check(t_game *game, t_list *map_buffer);
int	check_element(t_game *game, t_list *map_buffer);
int	check_top_bottom(t_list *map_buffer);
int	check_line_element(char *line, const char *set);
int	valid_element(t_game *game, t_list *map_buffer);
int	set_map_full(t_game *game, char **map, t_list *map_buffer);
void	set_map_content(t_game *game, char **map, t_list *map_buffer);
int	copy_list_to_char(t_game *game, t_list *map_buffer);
int	check_inclosed_wall(char **map, int i, int j, t_game *game);

/* only to show content of game for debug */
void	print_game_info(t_game game);

#endif
