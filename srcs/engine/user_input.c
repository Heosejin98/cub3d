/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:05:03 by seheo             #+#    #+#             */
/*   Updated: 2023/02/10 15:05:04 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	press_ws(t_game *game, int flag)
{	
	double	move_x;
	double	move_y;

	move_x = game->player.pos_x + game->player.dir_x * (double)S * flag;
	move_y = game->player.pos_y + game->player.dir_y * (double)S * flag;
	if (game->map[(int)move_x][(int)(game->player.pos_y)] == '1' ||
		game->map[(int)(game->player.pos_x)][(int)move_y] == '1')
		return ;
	game->player.pos_x = move_x;
	game->player.pos_y = move_y;
}

void	press_ad(t_game *game, int flag)
{
	double	move_x;
	double	move_y;

	move_x = \
	game->player.pos_x + game->player.plane_x * (double)S * (double)flag;
	move_y = \
	game->player.pos_y + game->player.plane_y * (double)S * (double)flag;
	if (game->map[(int)move_x][(int)(game->player.pos_y)] == '1' ||
		game->map[(int)(game->player.pos_x)][(int)move_y] == '1')
		return ;
	game->player.pos_x = move_x;
	game->player.pos_y = move_y;
}

void	press_lr(t_game *game, int flag)
{
	double	old_dir_x;
	double	old_dir_y;

	old_dir_y = game->player.plane_x;
	old_dir_x = game->player.dir_x;
	game->player.dir_x \
	= game->player.dir_x * cos(game->player.rot_speed * flag) \
	- game->player.dir_y * sin(game->player.rot_speed * flag);
	game->player.dir_y = \
	old_dir_x * sin(game->player.rot_speed * flag) \
	+ game->player.dir_y * cos(game->player.rot_speed * flag);
	game->player.plane_x \
	= game->player.plane_x * cos(game->player.rot_speed * flag) \
	- game->player.plane_y * sin(game->player.rot_speed * flag);
	game->player.plane_y = \
	old_dir_y * sin(game->player.rot_speed * flag) \
	+ game->player.plane_y * cos(game->player.rot_speed * flag);
}

int	click_destroy(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	ft_free_game(game);
	exit(EXIT_SUCCESS);
}

int	press_key(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		press_ws(game, 1);
	else if (keycode == KEY_A)
		press_ad(game, -1);
	else if (keycode == KEY_S)
		press_ws(game, -1);
	else if (keycode == KEY_D)
		press_ad(game, 1);
	else if (keycode == KEY_LEFT)
		press_lr(game, -1);
	else if (keycode == KEY_RIGHT)
		press_lr(game, 1);
	else if (keycode == KEY_ESC)
		click_destroy(game);
	cub_loop(game);
	return (0);
}
