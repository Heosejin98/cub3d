/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:31:32 by seheo             #+#    #+#             */
/*   Updated: 2023/01/21 21:05:35 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw(t_game *game)
{
	int	y;
	int	x;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			game->img.data[y * WIDTH + x] = game->buf[y][x];
		}
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
}

int	cub_loop(t_game *game)
{
	raycasting(game);
	draw(game);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_game		game;

	ft_memset(&game, 0, sizeof(t_game));
	validate_arg(&game, argc, argv);
	parsing_cub_file(&game, argv[1]);
	game_setting(&game);
	find_player(&game);
	get_texture_img(&game);
	mlx_hook(game.win, X_EVENT_KEY_PRESS, 0, press_key, &game);
	mlx_loop_hook(game.mlx, &cub_loop, &game);
	mlx_loop(game.mlx);
	ft_free_game(&game);
}
