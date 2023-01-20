/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 23:29:46 by seheo             #+#    #+#             */
/*   Updated: 2023/01/20 23:29:51 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_game(t_game *game)
{
	int	i;

	i = 0;
	if (game->line != NULL)
		free(game->line);
	if (game->map != NULL)
		ft_free_strs(game->map);
}
