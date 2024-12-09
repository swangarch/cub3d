/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_set_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:01:54 by yfan              #+#    #+#             */
/*   Updated: 2024/12/06 16:01:56 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	set_map_check(t_game *game, t_list *map_buffer)
{
	char	**map;

	if (check_element(game, map_buffer))
		return (1);
	if (set_map_full(game, &map, map_buffer))
		return (ft_putstr_fd("Malloc failed!", 2), 1);
	if (check_inclosed_wall(map, 0, 0, game))
		return (free_char_array(map), 1);
	if (check_space_inside(map))
		return (free_char_array(map), 1);
	return (free_char_array(map), 0);
}

int	set_map_full(t_game *game, char ***map_to_set, t_list *map_buffer)
{
	int		i;
	char	**map;

	map = (char **)malloc((game->map_row + 3) * sizeof(char *));
	if (!map)
		return (1);
	i = 0;
	while (i < game->map_row + 3)
		map[i++] = NULL;
	i = 0;
	while (i < game->map_row + 2)
	{
		map[i] = (char *)malloc((game->map_col + 2) * sizeof(char));
		if (!map[i])
			return (free_char_array(map), 1);
		++i;
	}
	if (copy_list_to_char(game, map_buffer))
		return (ft_putstr_fd("Malloc failed!", 2), free_char_array(map), 1);
	set_map_content(game, map);
	*map_to_set = map;
	return (0);
}

int	copy_list_to_char(t_game *game, t_list *map_buffer)
{
	int		i;
	char	*content;

	game->map = (char **)malloc((game->map_row + 1) * sizeof(char *));
	if (!game->map)
		return (1);
	i = 0;
	while (i < game->map_row + 1)
		game->map[i++] = NULL;
	i = 0;
	while (i < game->map_row && map_buffer)
	{
		content = ft_strtrim((char *)map_buffer->content, "\n");
		if (!content)
			return (free_char_array(game->map), 1);
		game->map[i] = ft_strdup(content);
		if (!game->map[i])
			return (free_char_array(game->map), free(content), 1);
		free(content);
		map_buffer = map_buffer->next;
		++i;
	}
	return (0);
}

void	set_map_content(t_game *game, char **map)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (i < game->map_row + 2)
	{
		j = 0;
		if (i == 0 || i == game->map_row + 1)
		{
			while (j < game->map_col + 1)
				map[i][j++] = ' ';
			map[i++][j] = '\0';
		}
		else
		{
			k = 0;
			map[i][j++] = ' ';
			while (game->map[i - 1][k])
				map[i][j++] = game->map[i - 1][k++];
			while (j < game->map_col + 1)
				map[i][j++] = ' ';
			map[i++][j] = '\0';
		}
	}
}

int	set_player_check(t_game *game, int size, char *line)
{
	int	i;

	if (check_line_element(line, " 01NSWE"))
		return (1);
	i = 0;
	while (line[i])
	{
		if (ft_in_set(line[i], "NWSE"))
		{
			if (line[i] == 'N')
				game->dir_player = NORTH;
			else if (line[i] == 'S')
				game->dir_player = SOUTH;
			else if (line[i] == 'W')
				game->dir_player = WEST;
			else
				game->dir_player = EAST;
			++game->num_player;
			game->player_x = (double)i + 0.5;
			game->player_y = (double)size + 0.5;
		}
		++i;
	}
	return (0);
}
