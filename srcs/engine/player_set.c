/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:21:21 by seheo             #+#    #+#             */
/*   Updated: 2023/01/29 15:37:28 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	set_dir(t_game *game, double d_x, double d_y)
{
	game->player.dir_x = d_x;
	game->player.dir_y = d_y;
}

static void	set_plane(t_game *game, double p_x, double p_y)
{
	game->player.plane_x = p_x;
	game->player.plane_y = p_y;
}

static void	set_pos(t_game *game, char pos, int i, int j)
{
	if (pos == 'E')
	{
		set_dir(game, 1, 0);
		set_plane(game, 0, 0.66);
	}
	if (pos == 'W')
	{
		set_dir(game, -1, 0);
		set_plane(game, 0, -0.66);
	}
	if (pos == 'S')
	{
		set_dir(game, 0, 1);
		set_plane(game, -0.66, 0);
	}
	if (pos == 'N')
	{
		set_dir(game, 0, -1);
		set_plane(game, 0.66, 0);
	}
	game->player.pos_x = i + 0.1;
	game->player.pos_y = j + 0.1;
}

void	find_player(t_game *game)
{
	int	h;
	int	w;

	h = 0;
	while (h < game->map_info.height)
	{
		w = 0;
		while (w < game->map_info.width)
		{
			if (game->map[h][w] == 'N' || game->map[h][w] == 'S' || \
				game->map[h][w] == 'W' || game->map[h][w] == 'E')
			{
				set_pos(game, game->map[h][w], h, w);
				return ;
			}
			w++;
		}
		h++;
	}
}
