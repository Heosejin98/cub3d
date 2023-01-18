#include "cub3d.h"

static void	assign_rgb_by_key(t_game *game, int *field, \
char *key, char *value)
{
	char	**strs;
	int		i;
	
	if (field[0] >= 0 || field[1] >= 0 || field[2] >= 0)
		ft_error(game, "rgb property is duplicated defined");
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
		field[i] = atoi(strs[i]);
	ft_free_strs(strs);
}

static void	assign_rgb(t_game *game, char *key, char *value)
{
	if (ft_strcmp(key, "F") == 0)
		assign_rgb_by_key(game, game->f_rgb, key, value);
	else if (ft_strcmp(key, "C") == 0)
		assign_rgb_by_key(game, game->c_rgb, key, value);
	else
		ft_error(game, "");
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
	if (game->f_rgb[0] < 0 || game->f_rgb[1] < 0 || game->f_rgb[2] < 0 || \
		game->c_rgb[0] < 0 || game->c_rgb[1] < 0 || game->c_rgb[2] < 0)
		ft_error(game, "need more imformation about rgb property");
}
