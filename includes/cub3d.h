/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:59:49 by hajeong           #+#    #+#             */
/*   Updated: 2023/01/18 22:04:12 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

# define KEY_RELEASE 	3
# define KEY_EXIT 		17
# define X_EVENT_KEY_PRESS	2

# define KEY_ESC		53
# define KEY_W			13
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2

# define WIDTH			1980
# define HEIGHT			1080

typedef struct s_ray
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	void	*mlx;
	void	*win;
	double	moveSpeed;
	double	rotSpeed;
	int		worldmap[24][24];
}	t_ray;

typedef struct s_game
{
	char	*line;
	char	*texture_file[4];
	int		f_rgb[3];
	int		c_rgb[3];
	int		map_height;
	int		map_width;
	char	**map;
	t_ray	ray;
}	t_game;

enum texture
{
	NORTH,
	SOUTH,
	WEST, 
	EAST
};



// parsing
void	parsing_cub_file(t_game *game, char *file);
int		read_file(char *file);
void	parsing_texture_lines(t_game *game, int fd);
void	parsing_rgb_lines(t_game *game, int fd);
void	parsing_map_lines(t_game *game, int fd);
void	validate_texture_lines(t_game *game);
void	validate_rgb_lines(t_game *game);
void	validate_map(t_game *game);
void	check_needless_lines(t_game *game, int fd);

// util
void	init_game_struct(t_game *game);
int		ft_isspace(char c);
char	**ft_split_isspace(char const *s);
void	ft_free_strs(char **strs);
void	ft_free_game(t_game *game);
void	ft_error(t_game *game, char *msg);
void	validate_arg(t_game *game, int argc, char *argv[]);

#endif