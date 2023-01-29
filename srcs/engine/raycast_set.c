/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:21:28 by seheo             #+#    #+#             */
/*   Updated: 2023/01/29 17:33:28 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	set_draw_index(t_game *game)
{
	if (game->ray.draw_start < 0)
		game->ray.draw_start = 0;
	game->ray.draw_end = game->ray.line_height / 2 + HEIGHT / 2;
	if (game->ray.draw_end >= HEIGHT)
		game->ray.draw_end = HEIGHT - 1;
}

static void	set_wallx_direction(t_game *game)
{
	if (game->ray.dir_side == 0)
		game->ray.wall_x = \
		game->player.pos_y + game->ray.perp_wall_dist * game->ray.ray_dir_y;
	else
		game->ray.wall_x = \
		game->player.pos_x + game->ray.perp_wall_dist * game->ray.ray_dir_x;
	game->ray.wall_x -= floor(game->ray.wall_x);
	if (game->ray.dir_side == 1 && game->ray.step_y < 0)
		game->ray.text_num = NORTH;
	else if (game->ray.dir_side == 1)
		game->ray.text_num = SOUTH;
	else if (game->ray.step_x < 0)
		game->ray.text_num = WEST;
	else
		game->ray.text_num = EAST;
}

static void	set_texture_info(t_game *game)
{
	game->ray.tex_x = (int)(game->ray.wall_x * (double)TEXWIDTH);
	if (game->ray.dir_side == 0 && game->ray.ray_dir_x > 0)
		game->ray.tex_x = TEXWIDTH - game->ray.tex_x - 1;
	if (game->ray.dir_side == 1 && game->ray.ray_dir_y < 0)
		game->ray.tex_x = TEXWIDTH - game->ray.tex_x - 1;
	game->ray.step = 1.0 * TEXHIGHT / game->ray.line_height;
}

static void	set_map(t_game *game, int x)
{
	double	tex_pos;
	int		y;
	int		tex_y;
	int		color;

	tex_pos = (game->ray.draw_start - HEIGHT / 2 \
			+ game->ray.line_height / 2) * game->ray.step;
	y = game->ray.draw_start;
	while (++y < game->ray.draw_end)
	{
		tex_y = (int)tex_pos & (TEXHIGHT - 1);
		tex_pos += game->ray.step;
		color = \
		game->player.texture \
		[game->ray.text_num][TEXHIGHT * tex_y + game->ray.tex_x];
		if (game->ray.dir_side == 1)
			color = (color >> 1) & 8355711;
		game->buf[y][x] = color;
	}
	y = game->ray.draw_end + 1;
	while (++y < HEIGHT)
	{
		game->buf[y][x] = arr_to_hex(game->map_info.f_rgb);
		game->buf[HEIGHT - y][x] = arr_to_hex(game->map_info.c_rgb);
	}
}

void	set_draw(t_game *game, int x)
{
	set_draw_index(game);
	set_wallx_direction(game);
	set_texture_info(game);
	set_map(game, x);
}
