/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:17:28 by seheo             #+#    #+#             */
/*   Updated: 2023/01/29 18:54:17 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	cal_sidedist_stepx(t_game *game)
{
	if (game->ray.ray_dir_x < 0)
	{
		game->ray.step_x = -1;
		game->ray.side_dist_x = \
		(game->player.pos_x - game->ray.map_x) * game->ray.delta_dist_x;
	}
	else
	{
		game->ray.step_x = 1;
		game->ray.side_dist_x = \
		(game->ray.map_x + 1.0 - game->player.pos_x) * game->ray.delta_dist_x;
	}
	if (game->ray.ray_dir_y < 0)
	{
		game->ray.step_y = -1;
		game->ray.side_dist_y = \
		(game->player.pos_y - game->ray.map_y) * game->ray.delta_dist_y;
	}
	else
	{
		game->ray.step_y = 1;
		game->ray.side_dist_y = \
		(game->ray.map_y + 1.0 - game->player.pos_y) * game->ray.delta_dist_y;
	}
}

void	cal_ray_val(t_game *game, int x)
{
	game->ray.camera_x = 2 * x / (double)WIDTH - 1;
	game->ray.ray_dir_x = \
		game->player.dir_x + game->player.plane_x * game->ray.camera_x;
	game->ray.ray_dir_y = \
		game->player.dir_y + game->player.plane_y * game->ray.camera_x;
	game->ray.map_x = (int)game->player.pos_x;
	game->ray.map_y = (int)game->player.pos_y;
	game->ray.delta_dist_x = fabs(1 / game->ray.ray_dir_x);
	game->ray.delta_dist_y = fabs(1 / game->ray.ray_dir_y);
	cal_sidedist_stepx(game);
}

void	dda(t_game *game)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (game->ray.side_dist_x < game->ray.side_dist_y)
		{
			game->ray.side_dist_x += game->ray.delta_dist_x;
			game->ray.map_x += game->ray.step_x;
			game->ray.dir_side = 0;
		}
		else
		{
			game->ray.side_dist_y += game->ray.delta_dist_y;
			game->ray.map_y += game->ray.step_y;
			game->ray.dir_side = 1;
		}
		if (game->map[game->ray.map_x][game->ray.map_y] == '1')
			hit = 1;
	}
}

void	cal_pre_wall_dist(t_game *game)
{
	double	xdist;
	double	ydist;

	xdist = game->ray.map_x - game->player.pos_x;
	ydist = game->ray.map_y - game->player.pos_y;
	if (game->ray.dir_side == 0)
		game->ray.perp_wall_dist = \
		(xdist + (1 - game->ray.step_x) / 2) / game->ray.ray_dir_x;
	else
		game->ray.perp_wall_dist = \
		(ydist + (1 - game->ray.step_y) / 2) / game->ray.ray_dir_y;

	game->ray.line_height = (int)(HEIGHT / game->ray.perp_wall_dist);
}

void	raycasting(t_game *game)
{
	int	x;

	x = -1;
	while (++x < WIDTH)
	{
		cal_ray_val(game, x);
		dda(game);
		cal_pre_wall_dist(game);
		game->ray.draw_start = -game->ray.line_height / 2 + HEIGHT / 2;
		set_draw(game, x);
	}
}
