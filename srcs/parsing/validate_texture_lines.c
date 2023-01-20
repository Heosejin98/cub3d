/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_texture_lines.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:29:11 by seheo             #+#    #+#             */
/*   Updated: 2023/01/20 23:29:20 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	validate(t_game *game, char *texture_file)
{
	int	fd;

	fd = read_file(texture_file);
	if (fd < 0)
		ft_error(game, "cannot open texture_file");
}

void	validate_texture_lines(t_game *game)
{
	validate(game, game->map_info.texture_file[NORTH]);
	validate(game, game->map_info.texture_file[SOUTH]);
	validate(game, game->map_info.texture_file[WEST]);
	validate(game, game->map_info.texture_file[EAST]);
}
