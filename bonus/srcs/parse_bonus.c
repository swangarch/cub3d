/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:28:52 by yfan              #+#    #+#             */
/*   Updated: 2024/12/06 18:28:54 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	parse_map(t_game *game, char *path_map)
{
	int		fd;
	int		flag;
	char	*line;
	t_list	*map_buffer;

	fd = open(path_map, O_RDONLY);
	if (fd < 0)
		map_error(MES_OPEN_ERR);
	map_buffer = NULL;
	flag = 1;
	line = get_next_line(fd);
	while (line)
	{
		flag = (flag && parse_oneline(game, line, &map_buffer));
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!flag || set_map_check(game, map_buffer))
		return (ft_lstclear(&map_buffer, free), 1);
	ft_lstclear(&map_buffer, free);
	if (check_color_tex(game))
		return (1);
	return (0);
}

int	check_access_eat(char **map, int i, int j, t_game *game)
{
	if (map[i][j] == '1')
		return (0);
	if (map[i][j] == 'C')
		++game->eat_access;
	if (map[i][j] == ' ')
		return (1);
	map[i][j] = '1';
	if (check_access_eat(map, i - 1, j, game))
		return (1);
	if (check_access_eat(map, i + 1, j, game))
		return (1);
	if (check_access_eat(map, i, j - 1, game))
		return (1);
	if (check_access_eat(map, i, j + 1, game))
		return (1);
	return (0);
}

int	valid_element(t_game *game, t_list *map_buffer)
{
	char	*line;
	int		i;
	int		max_len;
	int		size;

	max_len = 0;
	size = 0;
	while (map_buffer)
	{
		line = (char *)map_buffer->content;
		if (check_line_element(line, " 01NSWEC"))
			return (1);
		i = 0;
		set_player_check(game, i, size, line);
		if ((int)ft_strlen(line) > max_len)
			max_len = ft_strlen(line);
		map_buffer = map_buffer->next;
		++size;
	}
	game->map_col = max_len;
	return (0);
}

int	parse_oneline(t_game *game, char *line, t_list **map)
{
	int			len;
	int			type;

	len = ft_strlen(line);
	if (len == 1 && line[0] == '\n' && game->set[T_MAP])
		return (0);
	if (len == 1 && line[0] == '\n')
		return (1);
	type = check_tex_type(line);
	if (type != T_MAP && (game->set[type] || game->set[T_MAP]))
		return (0);
	if (type >= T_NORTH && type <= T_CEILING_SP)
		return (parse_texture(game, type, line));
	if (type == T_CEILING || type == T_FLOOR)
	{
		return (parse_color(game, type, line));
	}
	game->set[type] = 1;
	return (lst_add_back_buffer(map, ft_strdup(line)));
}

int	parse_texture(t_game *game, int type, char *line)
{
	char	**path;

	path = NULL;
	if (game->tex_path[type])
	{
		free(game->tex_path[type]);
		game->tex_path[type] = NULL;
	}
	path = ft_split(line, ' ');
	if (!path || path[2])
		return (free_char_array(path), 0);
	game->tex_path[type] = ft_strtrim(path[1], "\n");
	if (!game->tex_path[type])
		return (free_char_array(path), 0);
	game->set[type] = 1;
	return (free_char_array(path), 1);
}
