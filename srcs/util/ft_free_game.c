#include "cub3d.h"

void	ft_free_game(t_game *game)
{
	int	i;

	i = 0;
	if (game->line != NULL)
		free(game->line);
	
	while (i < 4)
	{
		if (game->texture_file[i] != NULL)
			free(game->texture_file[i]);
		i++;
	}
	if (game->map != NULL)
		ft_free_strs(game->map);
	
}