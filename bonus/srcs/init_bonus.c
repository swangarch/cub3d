/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:22:36 by shuwang           #+#    #+#             */
/*   Updated: 2024/11/25 16:22:36 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	set_init_dir(t_vars *vars, t_game *game)
{
	vars->posv.x = game->player_x;
	vars->posv.y = game->player_y;
	if (game->dir_player == NORTH)
	{
		vars->dirv.x = 0;
		vars->dirv.y = -SCALE;
	}
	else if (game->dir_player == SOUTH)
	{
		vars->dirv.x = 0;
		vars->dirv.y = SCALE;
	}
	else if (game->dir_player == WEST)
	{
		vars->dirv.x = -SCALE;
		vars->dirv.y = 0;
	}
	else if (game->dir_player == EAST)
	{
		vars->dirv.x = SCALE;
		vars->dirv.y = 0;
	}
}

static void	start_game(t_vars *vars)
{
	vars->buf_img = NULL;
	vars->tex_w_1 = NULL;
	vars->tex_w_2 = NULL;
	vars->tex_s_1 = NULL;
	vars->tex_s_2 = NULL;
	vars->tex_n = NULL;
	vars->tex_e = NULL;
	vars->tex_c = NULL;
	vars->tex_f = NULL;
	vars->tex_object_1 = NULL;
	vars->tex_object_2 = NULL;
	vars->mlx = mlx_init();
	if (!vars->mlx)
		finish_error(vars, "Error: mlx init failed\n");
	load_all_texture(vars);
	vars->buf_img = mlx_new_image(vars->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!vars->buf_img)
		finish_error(vars, "Error: creating new image failed\n");
	vars->buf_img_ptr = mlx_get_data_addr(vars->buf_img, \
		&vars->bits_per_pixel, &vars->size_line, &vars->endian);
	if (!vars->buf_img_ptr)
		finish_error(vars, "Error: getting image data address failed\n");
	vars->win = mlx_new_window(vars->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	if (!vars->win)
		finish_error(vars, "Error: creating new window failed\n");
}

void	init_vars(t_vars *vars, t_game *game)
{
	set_init_dir(vars, game);
	normalize_vector(&(vars->dirv), 1.0);
	vars->height_ratio = 0.5;
	vars->last_frame_t = 0;
	vars->last_mouse_pos.x = -1;
	vars->last_mouse_pos.y = -1;
	vars->mouse_move_dir = 0;
	vars->hp = 1.0;
	vars->touch_wall = 0;
	vars->show_map = 1;
	vars->show_fps = 0;
	vars->map_size = MAP_SIZE;
	vars->key_state[O] = 1;
	vars->key_state[P] = 1;
	vars->key_state[M] = 1;
	vars->fade = 1;
	vars->shadow = 1;
	vars->game = game;
	vars->map = game->map;
	vars->mlx = NULL;
	vars->win = NULL;
	vars->pos_obj.x = game->eat_x;
	vars->pos_obj.y = game->eat_y;
	ft_memset(&(vars->key_state), 0, 256 * sizeof(int));
	start_game(vars);
}

int	load_texture(t_vars *vars, void **img, char *path)
{
	int	img_width;
	int	img_height;

	*img = mlx_xpm_file_to_image(vars->mlx, path, &img_width, &img_height);
	if (!*img)
		finish_error(vars, "Error: load image failed\n");
	if (img_height != TEXTURE_SIZE || img_width != TEXTURE_SIZE)
		finish_error(vars, "Error: wrong image size\n");
	return (0);
}

void	load_all_texture(t_vars *vars)
{
	load_texture(vars, &(vars->tex_e), vars->game->tex_path[T_EAST]);
	load_texture(vars, &(vars->tex_n), vars->game->tex_path[T_NORTH]);
	load_texture(vars, &(vars->tex_s_2), vars->game->tex_path[T_SOUTH_SP]);
	load_texture(vars, &(vars->tex_w_2), vars->game->tex_path[T_WEST_SP]);
	load_texture(vars, &(vars->tex_s_1), vars->game->tex_path[T_SOUTH]);
	load_texture(vars, &(vars->tex_w_1), vars->game->tex_path[T_WEST]);
	load_texture(vars, &(vars->tex_object_1), vars->game->tex_path[T_OBJ]);
	load_texture(vars, &(vars->tex_object_2), vars->game->tex_path[T_OBJ_SP]);
	if (vars->game->tex_path[T_FLOOR_SP])
		load_texture(vars, &(vars->tex_f), vars->game->tex_path[T_FLOOR_SP]);
	if (vars->game->tex_path[T_CEILING_SP])
		load_texture(vars, &(vars->tex_c), vars->game->tex_path[T_CEILING_SP]);
}
