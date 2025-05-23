/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:58:14 by yfan              #+#    #+#             */
/*   Updated: 2024/05/22 14:09:27 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;

	if (!s1 || !set)
		return (0);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	len = ft_strlen(s1);
	while (len && ft_strchr(set, s1[len]))
		len--;
	return (ft_substr(s1, 0, len + 1));
}
/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	if (argc == 3)
		printf("%s\n", ft_strtrim(argv[1],argv[2]));
	else if (ft_strtrim(NULL, NULL) == NULL)
		printf("NULL\n");
	return (0);
}*/
