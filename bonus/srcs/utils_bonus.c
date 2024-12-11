/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:01:01 by yfan              #+#    #+#             */
/*   Updated: 2024/12/06 19:01:03 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	len_char_array(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
		++i;
	return (i);
}

int	ft_in_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		++i;
	}
	return (0);
}

int	check_color_range(int *color, char **part_color)
{
	color[0] = ft_atoi(part_color[0]);
	color[1] = ft_atoi(part_color[1]);
	color[2] = ft_atoi(part_color[2]);
	if (color[0] < 0 || color[0] > 255 || color[1] < 0 \
		|| color[1] > 255 || color[2] < 0 || color[2] > 255)
		return (0);
	return (1);
}

int	lst_add_back_buffer(t_list **map, char *line)
{
	t_list	*new_node;

	if (!map || !line)
		return (0);
	new_node = ft_lstnew((void *)line);
	if (!new_node)
		return (ft_lstclear(map, free), free(line), 0);
	ft_lstadd_back(map, new_node);
	return (1);
}

void	finish_error(t_vars *vars, char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	destroy_vars(vars);
	exit(EXIT_FAILURE);
}
