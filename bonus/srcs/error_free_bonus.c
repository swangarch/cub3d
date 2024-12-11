/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:10:51 by yfan              #+#    #+#             */
/*   Updated: 2024/12/06 18:10:53 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	map_error(char *str)
{
	ft_putstr_fd(MES_ERR, STDERR_FILENO);
	if (str)
		ft_putstr_fd(str, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	free_char_array(char **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static void	destroy_all_image(t_vars *vars)
{
	if (vars->buf_img)
		mlx_destroy_image(vars->mlx, vars->buf_img);
	if (vars->tex_e)
		mlx_destroy_image(vars->mlx, vars->tex_e);
	if (vars->tex_n)
		mlx_destroy_image(vars->mlx, vars->tex_n);
	if (vars->tex_w_1)
		mlx_destroy_image(vars->mlx, vars->tex_w_1);
	if (vars->tex_w_2)
		mlx_destroy_image(vars->mlx, vars->tex_w_2);
	if (vars->tex_s_1)
		mlx_destroy_image(vars->mlx, vars->tex_s_1);
	if (vars->tex_s_2)
		mlx_destroy_image(vars->mlx, vars->tex_s_2);
	if (vars->tex_c)
		mlx_destroy_image(vars->mlx, vars->tex_c);
	if (vars->tex_f)
		mlx_destroy_image(vars->mlx, vars->tex_f);
	if (vars->tex_object_1)
		mlx_destroy_image(vars->mlx, vars->tex_object_1);
	if (vars->tex_object_2)
		mlx_destroy_image(vars->mlx, vars->tex_object_2);
}

void	destroy_vars(t_vars *vars)
{
	int	i;

	i = 0;
	free_char_array(vars->game->map);
	while (i < LEN_TEX)
		free(vars->game->tex_path[i++]);
	destroy_all_image(vars);
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
}
