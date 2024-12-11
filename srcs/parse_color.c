/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:56:40 by yfan              #+#    #+#             */
/*   Updated: 2024/12/06 15:56:42 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_color_tex(t_game *game)
{
	int	i;

	i = 0;
	while (game->tex_path[i])
		++i;
	if (i != 4)
		return (1);
	if (game->color_c < 0 || game->color_f < 0)
		return (1);
	return (0);
}

char	**split_line_color(char *line)
{
	char	**part_line;
	char	**part_color;
	char	*trim_line;
	int		i;

	trim_line = ft_strtrim(line, "\n");
	if (!trim_line)
		return (NULL);
	part_line = ft_split(trim_line, ' ');
	free(trim_line);
	if (!part_line || len_char_array(part_line) != 2)
		return (free_char_array(part_line), NULL);
	i = 0;
	while (part_line[1][i])
		if (!ft_in_set(part_line[1][i++], ",0123456789"))
			return (free_char_array(part_line), NULL);
	part_color = ft_split(part_line[1], ',');
	return (free_char_array(part_line), part_color);
}

int	parse_color(t_game *game, int type, char *line)
{
	char	**part_color;
	int		c[3];

	part_color = split_line_color(line);
	if (!part_color || len_char_array(part_color) != 3)
		return (free_char_array(part_color), 0);
	if (!check_color_range(c, part_color))
		return (free_char_array(part_color), 0);
	if (type == T_CEILING)
		game->color_c = (c[0] << 16) | (c[1] << 8) | c[2];
	else if (type == T_FLOOR)
		game->color_f = (c[0] << 16) | (c[1] << 8) | c[2];
	free_char_array(part_color);
	return (1);
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
