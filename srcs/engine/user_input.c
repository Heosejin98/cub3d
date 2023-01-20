#include "../includes/cub3d.h"

int	key_press(int key, t_game *game)
{
	if (key == KEY_W)
	{
		if (game->map[(int)(game->player.pos_x + game->player.dir_x * game->player.move_speed)][(int)(game->player.pos_y)] != '1')
			game->player.pos_x += game->player.dir_x * game->player.move_speed;
		if (game->map[(int)(game->player.pos_x)][(int)(game->player.pos_y + game->player.dir_y * game->player.move_speed)] != '1')
			game->player.pos_y += game->player.dir_y * game->player.move_speed;
	}
	if (key == KEY_S)
	{
		if (game->map[(int)(game->player.pos_x - game->player.dir_x * game->player.move_speed)][(int)(game->player.pos_y)] != '1')
			game->player.pos_x -= game->player.dir_x * game->player.move_speed;
		if (game->map[(int)(game->player.pos_x)][(int)(game->player.pos_y - game->player.dir_y * game->player.move_speed)] != '1')
			game->player.pos_y -= game->player.dir_y * game->player.move_speed;
	}
	if (key == KEY_D)
	{
		double oldDirX = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(game->player.rot_speed) - game->player.dir_y * sin(game->player.rot_speed);
		game->player.dir_y = oldDirX * sin(game->player.rot_speed) + game->player.dir_y * cos(game->player.rot_speed);
		double oldPlaneX = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(game->player.rot_speed) - game->player.plane_y * sin(game->player.rot_speed);
		game->player.plane_y = oldPlaneX * sin(game->player.rot_speed) + game->player.plane_y * cos(game->player.rot_speed);
	}
	if (key == KEY_A)
	{
		double oldDirX = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(-game->player.rot_speed) - game->player.dir_y * sin(-game->player.rot_speed);
		game->player.dir_y = oldDirX * sin(-game->player.rot_speed) + game->player.dir_y * cos(-game->player.rot_speed);
		double oldPlaneX = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(-game->player.rot_speed) - game->player.plane_y * sin(-game->player.rot_speed);
		game->player.plane_y = oldPlaneX * sin(-game->player.rot_speed) + game->player.plane_y * cos(-game->player.rot_speed);
	}
	if (key == KEY_ESC)
		exit(0);
	mlx_clear_window(game->mlx, game->win);
	cub_loop(game);
	return (0);
}