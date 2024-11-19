#include "../includes/cub3d.h"

static void	render(t_game *game)
{
	int	x;
	int	y;
	int	i;
	int	j;
	int	color;

	mlx_clear_window(game->mlx, game->win);
	y = 0;
	while (y < 5)
	{
		x = 0;
		while (x < 6)
		{
			if (game->map[y][x] == '1')
				color = 0x0000FF;
			else if (game->map[y][x] == 'P')
				color = 0xFF0000;
			else
				color = 0xFFFFFF;
			i = 0;
			while (i < 64)
			{
				j = 0;
				while (j < 64)
				{
					mlx_pixel_put(game->mlx, game->win, x * 64 + i, \
						y * 64 + j, color);
					++j;
				}
				++i;
			}
			++x;
		}
		++y;
	}
}

int	update(t_game *game)
{
	render(game);
	return (1);
}
