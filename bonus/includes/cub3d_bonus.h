/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:02:18 by yfan              #+#    #+#             */
/*   Updated: 2024/12/09 17:02:20 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>
# include "cub_define_bonus.h"
# include "cub_struct_bonus.h"
# include "../../mlx_linux/mlx.h"

int		create_trgb(int t, int r, int g, int b);
int		get_r(int color);
int		get_g(int color);
int		get_b(int color);
int		get_t(int color);
void	draw_ground(t_vars *vars, int color);
void	init_info_floor_sky(t_tex *tex, t_vars *vars);
void	set_tex_floor(t_tex *tex, t_vars *vars);
void	render_floor_texture(t_vars *vars);
void	render_floor_sky(t_vars *vars);
void	render_sky_texture(t_vars *vars);
void	draw_sky(t_vars *vars, int color);
void	fill_rec(t_vars *vars, t_vector *pt1, t_vector *pt2, int color);
void	draw_line(t_vars *vars, t_vector *v0, t_vector *v1, int color);
void	draw_box(t_vars *vars, t_vector *pos, double size, int color);
void	draw_rec(t_vars *vars, t_vector *pt1, t_vector *pt2, int color);
void	draw_visibility(t_vars *vars, double size);
void	draw_map_background(t_vars *vars, t_vector *pos);
void	draw_map_element(t_vars *vars, t_vector *pos, int i, int j);
void	draw_map(t_vars *vars, double x, double y);
int		get_texcolor(void *tex, t_vector *pos, int color);
void	*get_texture(t_vars *vars, int i);
void	draw_texture(t_vars *vars, int i, int j);
void	map_error(char *str);
void	free_char_array(char **array);
void	destroy_vars(t_vars *vars);
void	finish_error(t_vars *vars, char *str);
int		double_eql(double a, double b);
double	ft_abs(double num);
double	to_radians(double angle);
double	vector_magnitude(t_vector *v);
double	dot_product(t_vector *v1, t_vector *v2);
void	normalize_vector(t_vector *vector, double scale);
void	rotate_vector(t_vector *v, t_vector *vo, double radians);
void	add_vector(t_vector *v_result, t_vector *v1, t_vector *v2);
void	cpy_scale_vector(t_vector *v_result, t_vector *v, double scale);
void	vector_2pt(t_vector *v_result, t_vector *end, t_vector *begin);
int		cross_press(t_vars *vars);
int		key_press(int keycode, t_vars *vars);
int		key_release(int keycode, t_vars *vars);
int		mouse_move(int x, int y, t_vars *vars);
void	rotate_when_mouse_move(t_vars *vars);
void	init_game(t_game *game);
void	init_vars(t_vars *vars, t_game *game);
int		load_texture(t_vars *vars, void **img, char *path);
void	load_all_texture(t_vars *vars);
int		move_character(t_vars *vars);
int		check_map_name(char *str);
int		check_space_inside(char **map);
int		check_inclosed_wall(char **map, int i, int j, t_game *game);
int		check_element(t_game *game, t_list *map_buffer);
int		check_top_bottom(t_list *map_buffer);
int		check_color_tex(t_game *game);
int		check_access_eat(char **map, int i, int j, t_game *game);
char	**split_line_color(char *line);
int		parse_color(t_game *game, int type, char *line);
int		check_tex_type(char *line);
int		set_map_check(t_game *game, t_list *map_buffer);
int		set_map_full(t_game *game, char ***map_to_set, t_list *map_buffer);
int		copy_list_to_char(t_game *game, t_list *map_buffer);
void	set_map_content(t_game *game, char **map);
void	set_player_check(t_game *game, int i, int size, char *line);
int		parse_map(t_game *game, char *path_map);
int		valid_element(t_game *game, t_list *map_buffer);
int		check_line_element(char *line, const char *set);
int		parse_oneline(t_game *game, char *line, t_list **map);
int		parse_texture(t_game *game, int type, char *line);
void	put_pixel_to_buf(t_vars *vars, int x, int y, int color);
void	clear_image_buf(t_vars *vars);
void	cal_render(t_vars *vars);
void	render_frame(t_vars *vars);
int		update_frame(t_vars *vars);
int		put_shadow(int color, double height, double wall_height);
int		put_vertical_shadow(int color);
int		fade_color(int color, double distance);
double	dist_line_pt(t_vector *v1, t_vector *vdir, t_vector *v2);
void	set_ray_obj_dist(t_vars *vars, t_vector *player_to_obj, int i);
void	cal_render_obj(t_vars *vars, double radians, int i);
void	draw_obj(t_vars *vars, int i, int j);
void	draw_hp_bar(t_vars *vars);
void	draw_sight(t_vars *vars);
void	draw_ui(t_vars *vars);
void	life(t_vars *vars);
void	eat(t_vars *vars, int i, int j);
void	update_animation_frame(t_vars *vars);
void	update_state(t_vars *vars);
time_t	get_current_time(void);
double	len_2pt(t_vector *v1, t_vector *v2);
int		color_range(int color_element);
void	first_pos(t_vars *vars, t_vector *result, \
	t_vector *v, t_vector *ist);
int		len_char_array(char **str);
int		ft_in_set(char c, const char *set);
int		check_color_range(int *color, char **part_color);
int		lst_add_back_buffer(t_list **map, char *line);
int		on_box(t_vars *vars, t_vector *center, t_vector *ist, int index);
double	hit_wall(t_vars *vars, t_vector *intersect, \
	int index, t_vector map_loc);
double	next_dir_int_dist(double dir, double comp);
void	move_first(t_vars *vars, t_vector *t_max, t_vector *t_delta, int i);
double	wall_distance(t_vars *vars, t_vector *vector, int index);
void	move_timeval(t_vector *intersect, t_vector *posv, \
	double timeval, t_vector *dv);
void	update_map_loc(t_vector *t_max, t_vector *vector, t_vector *map_loc);
int		in_range(double number, double bottom, double top);
int		get_unit(double num1, double num2);
void	update_time(t_vector *t_max, t_vector *t_delta);

#endif
