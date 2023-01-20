/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cub_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:21:55 by seheo             #+#    #+#             */
/*   Updated: 2023/01/20 23:32:46 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parsing_cub_file(t_game *game, char *file)
{
	int		fd;
	char	*line;

	fd = read_file(file);
	if (fd < 0)
		ft_error(game, "failed to open .cub file");
	parsing_texture_lines(game, fd);
	parsing_rgb_lines(game, fd);
	validate_rgb_lines(game);
	parsing_map_lines(game, fd);
	check_needless_lines(game, fd);
	validate_map(game);
	close(fd);
}
