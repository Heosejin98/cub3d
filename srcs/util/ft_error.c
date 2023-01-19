#include "cub3d.h"

void	ft_error(t_game *game, char *msg)
{
	if(game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->img.ptr)
		mlx_destroy_image(game->mlx, game->img.ptr);
	ft_printf("Error : %s\n", msg);
	//system("leaks cub3d");
	exit(0);
}