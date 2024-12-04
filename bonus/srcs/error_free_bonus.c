#include "../includes/cub3d_bonus.h"

void	map_error(char *str)
{
	ft_putstr_fd(MES_ERR, STDERR_FILENO);
	if (str)
		ft_putstr_fd(str, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	free_char_array(char **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	destroy_vars(t_vars *vars)
{
	(void)vars;
	return ; 
}
