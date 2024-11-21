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
		return (1);
	map_buffer = NULL;
	flag = 1;
	line = get_next_line(fd);
	while (line)
	{
		flag = (flag && parse_oneline(game, line, &map_buffer));
		free(line);
		line = get_next_line(fd);
	}
	//...
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
	if (type >= T_NORTH && type <= T_EAST)
		return (parse_texture(game, type, line));
	if (type == T_CEILING || type == T_FLOOR)
		return (parse_color(game, type, line));
	game->set[type] = 1;
	return (lst_add_back_buffer(map, ft_strdup(line)));//add!!
}

int	parse_color(t_game *game, int type, char *line)
{
	char	**part_line;
	char	**part_color;
	int		i;
	int		c[3];

	part_line = ft_split(line, ' ');
	if (!part_line || len_char_array(part_line) != 2)
		return (free_char_array(part_line), 0);
	i = 0;
	while (part_line[1][i])
		if (!ft_in_set(part_line[1][i], ",0123456789"))
			return (free_char_array(part_line), 0);
	part_color = ft_split(part_line[1], ",");
	free_char_array(part_line);
	if (!part_color || len_char_array(part_color) != 3)
		return (free_char_array(part_color), 0);
	if (!check_color_range(c, part_color))
		return (free_char_array(part_color), 0);
	if (type == T_CEILING)
		game->color_c = (c[0] << 16) | (c[1] << 8) | c[2];
	else
		game->color_f = (c[0] << 16) | (c[1] << 8) | c[2];
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
	game->tex_path[type] = ft_strdup(path[1]);
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
