#include "cub3d.h"

static void validate(t_game *game, int *arr)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (0 > arr[i] || arr[i] > 255)
			ft_error(game, "rgb value must be between 0 and 255");
	}
}

void	validate_rgb_lines(t_game *game)
{
	validate(game, game->f_rgb);
	validate(game, game->c_rgb);
}