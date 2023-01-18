/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:42:45 by hajeong           #+#    #+#             */
/*   Updated: 2023/01/18 20:52:54 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game_struct(t_game *game)
{
	int i;

	i = -1;
	game->line = NULL;
	game->map = NULL;
	game->texture_file[NORTH] = NULL;
	game->texture_file[SOUTH] = NULL;
	game->texture_file[WEST] = NULL;
	game->texture_file[EAST] = NULL;
	while (++i < 3)
	{
		game->f_rgb[i] = -1;
		game->c_rgb[i] = -1;
	}
}