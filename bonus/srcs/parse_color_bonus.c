/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:26:30 by yfan              #+#    #+#             */
/*   Updated: 2024/12/06 18:26:31 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	check_color_tex(t_game *game)
{
	int	i;

	i = 0;
	while (game->tex_path[i] && i < 8)
		++i;
	if (i != 8)
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
	if (line[i] == '\n' && line[i + 1])
		return (1);
	if (line[i] == '\n' && line[i - 1] == ' ')
		return (1);
	return (0);
}

int	check_tex_type(char *line)
{
	if (!ft_strncmp(line, "NO", 2) && line[2] == ' ')
		return (T_NORTH);
	if (!ft_strncmp(line, "SO", 2) && line[2] == ' ')
		return (T_SOUTH);
	if (!ft_strncmp(line, "WE", 2) && line[2] == ' ')
		return (T_WEST);
	if (!ft_strncmp(line, "EA", 2) && line[2] == ' ')
		return (T_EAST);
	if (!ft_strncmp(line, "OB", 2) && line[2] == ' ')
		return (T_OBJ);
	if (!ft_strncmp(line, "OBP", 3) && line[3] == ' ')
		return (T_OBJ_SP);
	if (!ft_strncmp(line, "SO1", 3) && line[3] == ' ')
		return (T_SOUTH_SP);
	if (!ft_strncmp(line, "WE1", 3) && line[3] == ' ')
		return (T_WEST_SP);
	if (!ft_strncmp(line, "FP", 2) && line[2] == ' ')
		return (T_FLOOR_SP);
	if (!ft_strncmp(line, "CP", 2) && line[2] == ' ')
		return (T_CEILING_SP);
	if (!ft_strncmp(line, "F", 1) && line[1] == ' ')
		return (T_FLOOR);
	if (!ft_strncmp(line, "C", 1) && line[1] == ' ')
		return (T_CEILING);
	return (T_MAP);
}
