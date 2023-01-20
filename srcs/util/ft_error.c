/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:29:34 by seheo             #+#    #+#             */
/*   Updated: 2023/01/20 23:29:38 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(t_game *game, char *msg)
{
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->img.ptr)
		mlx_destroy_image(game->mlx, game->img.ptr);
	ft_printf("Error : %s\n", msg);
	exit(0);
}
