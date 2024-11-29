#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>
# include "cub_define.h"
# include "cub_struct.h"
# include "../mlx_linux/mlx.h"
# include <stdio.h>//for test!!!!!!!!!!1

void	map_error(char *str);
// void	start_game(t_game *game);
// int		update(t_game *game);
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
int	set_map_full(t_game *game, char ***map_to_set, t_list *map_buffer);
void	set_map_content(t_game *game, char **map);
int	copy_list_to_char(t_game *game, t_list *map_buffer);
int	check_inclosed_wall(char **map, int i, int j, t_game *game);
int	check_space_inside(char **map);

/* only to show content of game for debug */
void	print_game_info(t_game game);
void	print_map_list(t_list *map_buffer);

/**************************************************/

/*INIT*/
void init_vars(t_vars *vars, t_game *game);
int load_texture(t_vars *vars, void **img, char *path);
int load_all_texture(t_vars *vars);

/*MATH*/
double to_radians(double angle);
double ft_abs(double num);
int double_eql(double a, double b);
double len_2pt(t_vector *v1, t_vector *v2);
int closest_int(double num);

/*DRAW GEOMETRY*/
void put_pixel_to_buf(t_vars *vars, int x, int y, int color);
void draw_line(t_vars *vars, t_vector *v0, t_vector *v1, int color);
void draw_box(t_vars *vars, double x, double y, double size, int color);

void draw_ground(t_vars *vars, int color);
void draw_sky(t_vars *vars, int);

void draw_rec(t_vars *vars, t_vector *pt1, t_vector *pt2, int color);
void fill_rec(t_vars *vars, t_vector *pt1, t_vector *pt2, int color);

/*GAME CONTROL*/
int	move_character(t_vars *vars);
void rotate_when_mouse_move(t_vars *vars);
//int	key_control(int keycode, t_vars *vars);
int	key_press(int keycode, t_vars *vars);
int	key_release(int keycode, t_vars *vars);
int mouse_move(int x, int y, t_vars *vars);
int cross_press(t_vars *vars);

/*VECTOR*/

void normalize_vector(t_vector *vector, double scale);
void rotate_vector(t_vector *v, t_vector *vo, double radians);
double wall_distance(t_vars *vars, t_vector *vector, int i);
double vector_magnitude(t_vector *v);

void add_vector(t_vector *v_result, t_vector *v1, t_vector *v2);
void cpy_scale_vector(t_vector *v_result, t_vector *v, double scale);

/*RENDER*/
void    render_game(t_vars *vars);
void clear_image_buf(t_vars *vars);
int    update_frame(t_vars *vars);
int get_texture_pixel_color(void *tex, t_vector *pos);

/*TEXTURE*/
void draw_texture(t_vars *vars);
void draw_obj(t_vars *vars);

/*COLOR*/
int create_trgb(int t, int r, int g, int b);
int get_r(int color);
int get_g(int color);
int get_b(int color);
int get_t(int color);
int color_range(int color_element);

/*UTILS*/
time_t  get_current_time(void);

/*UI*/
void draw_ui(t_vars *vars);

/*UPDATE STATE*/
void    update_state(t_vars *vars);

/*SPECIAL EFFECT*/
int put_shadow(int color, double height, double wall_height);
int fade_color(int color, double distance);
int put_vertical_shadow(int color);



double obj_distance(t_vars *vars, t_vector *vector, int index);
void cal_render_obj(t_vars *vars);

#endif
