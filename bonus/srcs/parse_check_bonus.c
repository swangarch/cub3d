/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:29:11 by yfan              #+#    #+#             */
/*   Updated: 2024/12/06 18:29:12 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	check_map_name(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (i <= 4)
		return (1);
	if (str[i - 1] == 'b' && str[i - 2] == 'u' && str[i - 3] == 'c' \
			&& str[i - 4] == '.')
		return (0);
	return (1);
}

int	check_space_inside(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ')
				return (1);
			++j;
		}
		++i;
	}
	return (0);
}

int	check_inclosed_wall(char **map, int i, int j, t_game *game)
{
	if (i < 0 || i >= game->map_row + 2 || j < 0 \
		|| j >= game->map_col + 1 || map[i][j] == '1')
		return (0);
	if (ft_in_set(map[i][j], "0NSWEC"))
		return (1);
	map[i][j] = '1';
	if (check_inclosed_wall(map, i - 1, j, game))
		return (1);
	if (check_inclosed_wall(map, i + 1, j, game))
		return (1);
	if (check_inclosed_wall(map, i, j - 1, game))
		return (1);
	if (check_inclosed_wall(map, i, j + 1, game))
		return (1);
	return (0);
}

int	check_element(t_game *game, t_list *map_buffer)
{
	if (!game || !map_buffer)
		return (1);
	if (check_top_bottom(map_buffer))
		return (1);
	game->map_row = ft_lstsize(map_buffer);
	if (game->map_row < 3 || valid_element(game, map_buffer))
		return (1);
	if (game->map_col < 3 || game->num_player != 1 || game->num_eat != 1)
		return (1);
	return (0);
}

int	check_top_bottom(t_list *map_buffer)
{
	char	*line;
	t_list	*tmp_node;

	line = (char *)map_buffer->content;
	if (check_line_element(line, " 1"))
		return (1);
	tmp_node = ft_lstlast(map_buffer);
	line = (char *)tmp_node->content;
	if (check_line_element(line, " 1"))
		return (1);
	return (0);
}
