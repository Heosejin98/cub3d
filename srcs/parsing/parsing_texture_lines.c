/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture_lines.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:28:17 by seheo             #+#    #+#             */
/*   Updated: 2023/01/20 23:28:18 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_error_wrong_field_number(t_game *game, char **strs)
{
	ft_free_strs(strs);
	ft_error(game, "texture property must have 2 fields");
}

static void	assign_texture_by_key(t_game *game, char **field, \
char *key, char *value)
{
	if (*field != NULL)
		ft_error(game, "texture property is duplicated defined");
	*field = value;
}

static void	assign_texture(t_game *game, char *key, char *value)
{
	if (ft_strcmp(key, "NO") == 0)
		assign_texture_by_key \
		(game, &(game->map_info.texture_file[NORTH]), key, value);
	else if (ft_strcmp(key, "SO") == 0)
		assign_texture_by_key \
		(game, &(game->map_info.texture_file[SOUTH]), key, value);
	else if (ft_strcmp(key, "WE") == 0)
		assign_texture_by_key \
		(game, &(game->map_info.texture_file[WEST]), key, value);
	else if (ft_strcmp(key, "EA") == 0)
		assign_texture_by_key \
		(game, &(game->map_info.texture_file[EAST]), key, value);
	else
		ft_error(game, "strange identifier in texture lines");
}

static void	check_texture(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (game->map_info.texture_file[i] == NULL)
			ft_error(game, "need more imformation about texture property");
	}
}

void	parsing_texture_lines(t_game *game, int fd)
{
	char	**strs;

	game->line = ft_strdup("\n");
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
			ft_error_wrong_field_number(game, strs);
		assign_texture(game, strs[0], strs[1]);
		free(strs[0]);
		free(strs);
		free(game->line);
		game->line = get_next_line(fd);
	}
	check_texture(game);
}
