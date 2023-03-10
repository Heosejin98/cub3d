/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_needless_lines.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:21:51 by seheo             #+#    #+#             */
/*   Updated: 2023/01/20 23:22:35 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_needless_lines(t_game *game, int fd)
{
	int	i;

	while (game->line != NULL)
	{
		i = -1;
		while (game->line[++i] != '\0')
		{
			if (!ft_isspace(game->line[i]))
				ft_error(game, "needless lines after map lines");
		}
		free(game->line);
		game->line = get_next_line(fd);
	}
}
