/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_setup_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:22:21 by yfan              #+#    #+#             */
/*   Updated: 2024/12/06 18:22:23 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	init_game(t_game *game)
{
	int	i;

	if (!game)
		return ;
	i = 0;
	game->color_c = -1;
	game->color_f = -1;
	game->num_player = 0;
	game->num_eat = 0;
	game->eat_access = 0;
	game->map = NULL;
	while (i < LEN_TEX)
		game->tex_path[i++] = NULL;
	i = 0;
	while (i < LEN_TYPE)
		game->set[i++] = 0;
}
