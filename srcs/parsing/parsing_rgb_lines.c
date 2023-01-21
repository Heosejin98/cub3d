/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_rgb_lines.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:22:56 by seheo             #+#    #+#             */
/*   Updated: 2023/01/21 19:47:27 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	assign_rgb_by_key(t_game *game, int *field, \
char *key, char *value)
{
	char	**strs;
	int		i;

	i = -1;
	while (value[++i] != '\0')
		if (!ft_isdigit(value[i]) && value[i] != ',')
			ft_error(game, "rgb property contains strange characters");
	strs = ft_split(value, ',');
	if (strs == NULL)
		ft_error(game, "malloc error");
	if (strs[3] != NULL || !strs[0] || !strs[1] || !strs[2])
	{
		ft_free_strs(strs);
		ft_error(game, "rgb property must have 3 numbers");
	}
	i = -1;
	while (++i < 3)
		field[i] = ft_atoi(strs[i]);
	ft_free_strs(strs);
}

static void	assign_rgb(t_game *game, char *key, char *value)
{
	if (ft_strcmp(key, "F") == 0)
		assign_rgb_by_key(game, game->map_info.f_rgb, key, value);
	else if (ft_strcmp(key, "C") == 0)
		assign_rgb_by_key(game, game->map_info.c_rgb, key, value);
	else
		ft_error(game, "");
}

static void	check_f_c_rgb(t_game *game)
{
	if (game->map_info.f_rgb[0] < 0 || game->map_info.f_rgb[1] < 0 \
		|| game->map_info.f_rgb[2] < 0 || game->map_info.c_rgb[0] < 0 \
		|| game->map_info.c_rgb[1] < 0 || game->map_info.c_rgb[2] < 0)
		ft_error(game, "need more imformation about rgb property");
}

void	parsing_rgb_lines(t_game *game, int fd)
{
	char	**strs;

	while (game->line != NULL && ft_strcmp(game->line, "\n") == 0)
	{
		free(game->line);
		game->line = get_next_line(fd);
	}
	while (game->line != NULL && ft_strcmp(game->line, "\n") != 0)
	{
		strs = ft_split_isspace(game->line);
		if (strs == NULL)
			ft_error(game, "malloc error");
		if (strs[2] != NULL || !strs[0] || !strs[1])
		{
			ft_free_strs(strs);
			ft_error(game, "rgb property must have 2 fields");
		}
		assign_rgb(game, strs[0], strs[1]);
		ft_free_strs(strs);
		free(game->line);
		game->line = get_next_line(fd);
	}
	check_f_c_rgb(game);
}
