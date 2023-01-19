#include "cub3d.h"

static void validate(t_game *game, char *texture_file)
{
	int fd;

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