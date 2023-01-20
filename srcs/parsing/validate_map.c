/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:28:32 by seheo             #+#    #+#             */
/*   Updated: 2023/01/20 23:28:54 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	validate_map_char(t_game *game)
{
	int	i;
	int	j;
	int	cnt;

	cnt = 0;
	i = -1;
	while (++i < game->map_info.height)
	{
		j = -1;
		while (game->map[i][++j] != '\0')
		{
			if (!ft_strchr(" 01NSEW", game->map[i][j]))
				ft_error(game, "strange characters in the map");
			else if (ft_strchr("NSEW", game->map[i][j]))
				cnt++;
		}
	}
	if (cnt < 1)
		ft_error(game, "no start position");
	if (cnt > 1)
		ft_error(game, "too many start position");
}

static void	validate_row(t_game *game, int row)
{
	int	i;

	i = 0;
	while (i < game->map_info.width)
	{
		while (i < game->map_info.width && game->map[row][i] == ' ')
			i++;
		if (game->map[row][i] == '\0')
			break ;
		if (game->map[row][i] != '1')
			ft_error(game, "map is not walled around");
		while (i < game->map_info.width && game->map[row][i] != ' ')
			i++;
		if (game->map[row][i - 1] != '1')
			ft_error(game, "map is not walled around");
	}
}

static void	validate_column(t_game *game, int column)
{
	int	i;

	i = 0;
	while (i < game->map_info.height)
	{
		while (i < game->map_info.height && game->map[i][column] == ' ')
			i++;
		if (i >= game->map_info.height)
			break ;
		if (game->map[i][column] != '1')
			ft_error(game, "map is not walled around");
		while (i < game->map_info.height && game->map[i][column] != ' ')
			i++;
		if (game->map[i - 1][column] != '1')
			ft_error(game, "map is not walled around");
	}
}

static void	validate_map_wall(t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->map_info.height)
		validate_row(game, i);
	i = -1;
	while (++i < game->map_info.width)
		validate_column(game, i);
}

void	validate_map(t_game *game)
{
	validate_map_char(game);
	validate_map_wall(game);
}
