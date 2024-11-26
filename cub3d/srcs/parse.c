#include "../includes/cub3d.h"

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
		// printf("**************\n");//for test!!!!!!!!!!!!!!!
		// printf("line = %s\n", line);//for test!!!!!!!!!!!!
		flag = (flag && parse_oneline(game, line, &map_buffer));
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	// printf("flag = %d\n", flag);//test!!!!!!!
	if (!flag || set_map_check(game, map_buffer))
		return (ft_lstclear(&map_buffer, free), 1);
	ft_lstclear(&map_buffer, free);
	return (0);
}

int	set_map_check(t_game *game, t_list *map_buffer)
{
	char	**map;
	int		i;

	// print_map_list(map_buffer);//test!!!!!!!
	if (check_element(game, map_buffer))
		return (1);
	if (set_map_full(game, &map, map_buffer))
		return (ft_putstr_fd("Malloc failed!", 2), 1);
	// game->index = (int **)malloc((game->map_row + 2) * sizeof(int *));
	// if (!game->index)
	// {
	// 	ft_putstr_fd("Malloc failed!", 2);
	// 	return (free_char_array(map), 1);
	// }
	// i = 0;
	// while (i < game->map_row + 2)
	// {
	// 	game->index[i] = (int *)malloc((game->map_col + 1) * sizeof(int));
	// 	//check and free
	// 	j = 0;
	// 	while (j < game->map_col + 1)
	// 	{
	// 		game->index[i][j] = 0;
	// 		++j;
	// 	}
	// 	++i;
	// }
	if (check_inclosed_wall(map, 0, 0, game))
		return (free_char_array(map), 1);
	if (check_space_inside(map))
		return (free_char_array(map), 1);
	return (free_char_array(map), 0);
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
	if (ft_in_set(map[i][j], "0NSWE"))
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

int	check_element(t_game *game, t_list *map_buffer)
{
	if (!game || !map_buffer)
		return (1);
	if (check_top_bottom(map_buffer))
		return (1);
	game->map_row = ft_lstsize(map_buffer);
	// printf("map_row = %d\n", game->map_row);//test!!!!
	if (game->map_row < 3 || valid_element(game, map_buffer))
		return (1);
	// printf("map_col = %d\n", game->map_col);//test!!!!!!!!!
	// printf("num_player = %d\n", game->num_player);//test!!!
	if (game->map_col < 3 || game->num_player != 1)
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
		if (check_line_element(line, " 01NSWE"))
			return (1);
		i = 0;
		while (line[i])
		{
			if (ft_in_set(line[i], "NWSE"))
			{
				++game->num_player;
				game->player_x = (double)i + 0.5;
				game->player_y = (double)size + 0.5;
			}
			++i;
		}
		if (ft_strlen(line) > max_len)
			max_len = ft_strlen(line);
		map_buffer = map_buffer->next;
		++size;
	}
	game->map_col = max_len;
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

int	check_line_element(char *line, const char *set)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!ft_in_set(line[i], set))
			return (1);
		++i;
	}
	// if (line[i] != '\n')
	// 	return (1);
	if (line[i] == '\n' && line[i + 1])
		return (1);
	if (line[i] == '\n' && line[i - 1] == ' ')
		return (1);
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
	// printf("oneline: type = %d\n", type);//test!!!!!!!!!!
	// printf("oneline: line = %s\n", line);//test!!!!!!!!!!
	if (type != T_MAP && (game->set[type] || game->set[T_MAP]))
		return (0);
	if (type >= T_NORTH && type <= T_EAST)
		return (parse_texture(game, type, line));
	if (type == T_CEILING || type == T_FLOOR)
	{
		return (parse_color(game, type, line));
	}
	game->set[type] = 1;
	return (lst_add_back_buffer(map, ft_strdup(line)));
}

int	parse_color(t_game *game, int type, char *line)
{
	char	**part_line;
	char	**part_color;
	char	*trim_line;
	int		i;
	int		c[3];

	// printf("oneline: type = %d\n", type);//test!!!!!!!!!!
	// printf("oneline: line = %s\n", line);//test!!!!!!!!!!
	trim_line = ft_strtrim(line, "\n");
	if (!trim_line)
		return (0);
	part_line = ft_split(trim_line, ' ');
	free(trim_line);
	if (!part_line || len_char_array(part_line) != 2)
		return (free_char_array(part_line), 0);
	i = 0;
	while (part_line[1][i])
		if (!ft_in_set(part_line[1][i++], ",0123456789"))
			return (free_char_array(part_line), 0);
	part_color = ft_split(part_line[1], ',');
	free_char_array(part_line);
	if (!part_color || len_char_array(part_color) != 3)
		return (free_char_array(part_color), 0);
	if (!check_color_range(c, part_color))
		return (free_char_array(part_color), 0);
	if (type == T_CEILING)
		game->color_c = (c[0] << 16) | (c[1] << 8) | c[2];
	else if (type == T_FLOOR)
		game->color_f = (c[0] << 16) | (c[1] << 8) | c[2];
	// if (game->color_c != 0)
	// 	printf("%d\n", game->color_c);
	// if (game->color_f != 0)
	// 	printf("%d\n", game->color_f);
	return (1);
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

int	check_tex_type(char *line)
{
	if (!ft_strncmp(line, "NO", 2) && line[2] == ' ')
		return (T_NORTH);
	else if (!ft_strncmp(line, "SO", 2) && line[2] == ' ')
		return (T_SOUTH);
	else if (!ft_strncmp(line, "WE", 2) && line[2] == ' ')
		return (T_WEST);
	else if (!ft_strncmp(line, "EA", 2) && line[2] == ' ')
		return (T_EAST);
	else if (!ft_strncmp(line, "F", 1) && line[1] == ' ')
		return (T_FLOOR);
	else if (!ft_strncmp(line, "C", 1) && line[1] == ' ')
		return (T_CEILING);
	return (T_MAP);
}
