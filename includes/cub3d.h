/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 14:59:49 by hajeong           #+#    #+#             */
/*   Updated: 2023/01/20 15:55:39 by seheo            ###   ########.fr       */
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

# define texWidth 64
# define texHeight 64

# define KEY_ESC		53
# define KEY_W			13
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2

# define WIDTH			1980
# define HEIGHT			1020

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
	int		*texture[4];
}	t_player;

typedef struct	s_ray
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			dir_side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wall_x;
}				t_ray;

typedef struct	s_map
{
	int			width;
	int			height;
	int			floor_text;
	int			ceiling_text;
	char		*texture_file[4];
	int			f_rgb[3];
	int			c_rgb[3];
}				t_map;

typedef struct	s_img
{
	void		*ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
	int			img_width;
	int			img_height;
}				t_img;

typedef struct s_game
{
	char		*line;
	void		*mlx;
	void		*win;
	char		**map;;
	int			**buf;	
	int			re_buf;	
	t_player	player;
	t_map		map_info;
	t_img		img;	
}	t_game;

typedef struct	s_text
{
	double		t_pos;
	int			t_x;
	int			t_y;
	int			t_num;
	int			color;
}				t_text;

enum texture
{
	NORTH,
	SOUTH,
	WEST, 
	EAST,
	FLOOR,
	CELL
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