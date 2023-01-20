/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:17:47 by seheo             #+#    #+#             */
/*   Updated: 2023/01/20 23:21:12 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	load_image(t_game *game, int tex_num, char *path)
{
	t_img	img;
	int		y;
	int		x;

	img.ptr = mlx_xpm_file_to_image \
			(game->mlx, path, &img.img_width, &img.img_height);
	if (!img.ptr)
		ft_error(game, "wrong file");
	img.data = (int *)mlx_get_data_addr \
				(img.ptr, &img.bpp, &img.size_l, &img.endian);
	y = -1;
	while (++y < img.img_height)
	{
		x = -1;
		while (++x < img.img_width)
		{
			game->player.texture[tex_num][img.img_width * y + x] \
				= img.data[img.img_width * y + x];
		}
	}
	mlx_destroy_image(game->mlx, img.ptr);
}

void	get_texture_img(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		load_image(game, i, game->map_info.texture_file[i]);
	}
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3d");
	game->img.ptr = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img.data = (int *)mlx_get_data_addr \
		(game->img.ptr, &game->img.bpp, &game->img.size_l, &game->img.endian);
}

void	game_setting(t_game *game)
{
	int	i;

	i = -1;
	game->player.move_speed = 0.6;
	game->player.rot_speed = 0.3;
	game->mlx = mlx_init();
	game->buf = ft_calloc(HEIGHT, sizeof(int *));
	while (++i < HEIGHT)
	{
		game->buf[i] = ft_calloc(WIDTH, sizeof(int));
	}
	i = -1;
	while (++i < 4)
	{
		game->player.texture[i] = \
		(int *)malloc(sizeof(int) * (TEXHIGHT * TEXWIDTH));
		if (game->player.texture[i] == NULL)
			ft_error(game, "malloc error");
	}
	i = -1;
	while (++i < 4)
	{	
		ft_memset(game->player.texture[i], 0, (TEXHIGHT * TEXWIDTH));
	}
}
