#include "../includes/cub3d.h"


# define K_A 0
# define K_B 11
# define K_C 8
# define K_D 2
# define K_E 14
# define K_F 3
# define K_G 5
# define K_H 4
# define K_I 34
# define K_J 38
# define K_K 40
# define K_L 37
# define K_M 46
# define K_N 45
# define K_O 31
# define K_P 35
# define K_Q 12
# define K_R 15
# define K_S 1
# define K_T 17
# define K_U 32
# define K_V 9
# define K_W 13
# define K_X 7
# define K_Y 16
# define K_Z 6
# define K_ESC 53

int	main_loop(t_game *game);

void	set_dir(t_game *game, double d_x, double d_y)
{
	game->player.dir_x = d_x;
	game->player.dir_y = d_y;
}

void	set_plane(t_game *game, double p_x, double p_y)
{
	game->player.plane_x = p_x;
	game->player.plane_y = p_y;
}

void	set_pos(t_game *game, char pos, int i, int j)
{
	if (pos == 'E')
	{
		set_dir(game, 0, 1);
		set_plane(game, 0.66, 0);
	}
	if (pos == 'W')
	{
		set_dir(game, 0, -1);
		set_plane(game, -0.66, 0);
	}
	if (pos == 'S')
	{
		set_dir(game, 1, 0);
		set_plane(game, 0, -0.66);
	}
	if (pos == 'N')
	{
		set_dir(game, -1, 0);
		set_plane(game, 0, 0.66);
	}
	game->player.pos_x = i;
	game->player.pos_y = j;
}

void	verLine(t_game *game, int x, int y1, int y2, int color)
{
	int	y;
	t_text	t;

	y = y1;
	while (y <= y2)
	{	
		t.t_y = (int)t.t_pos &
		mlx_pixel_put(game->mlx, game->win, x, y, color);
		y++;
	}
}

void side_wall(t_game *game, t_ray *ray)
{
	t_player *p;

	p = &game->player;
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (p->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - p->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (p->pos_x - ray->map_x) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->map_y + 1.0 - p->pos_y) * ray->delta_dist_y;
	}
}

void	ray_hit_wall(t_game *game, t_ray *ray)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->dir_side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->dir_side = 1;
		}
		if (game->map[ray->map_x][ray->map_y] > '0')
			hit = 1;
	}
}
int	key_press(int key, t_game *game)
{
	if (key == K_W)
	{
		if (!game->map[(int)(game->player.pos_x + game->player.dir_x * game->player.move_speed)][(int)(game->player.pos_y)])
			game->player.pos_x += game->player.dir_x * game->player.move_speed;
		if (!game->map[(int)(game->player.pos_x)][(int)(game->player.pos_y + game->player.dir_y * game->player.move_speed)])
			game->player.pos_y += game->player.dir_y * game->player.move_speed;
	}

	if (key == K_S)
	{
		if (!game->map[(int)(game->player.pos_x - game->player.dir_x * game->player.move_speed)][(int)(game->player.pos_y)])
			game->player.pos_x -= game->player.dir_x * game->player.move_speed;
		if (!game->map[(int)(game->player.pos_x)][(int)(game->player.pos_y - game->player.dir_y * game->player.move_speed)])
			game->player.pos_y -= game->player.dir_y * game->player.move_speed;
	}

	if (key == K_D)
	{
		double oldDirX = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(-game->player.rot_speed) - game->player.dir_y * sin(-game->player.rot_speed);
		game->player.dir_y = oldDirX * sin(-game->player.rot_speed) + game->player.dir_y * cos(-game->player.rot_speed);
		double oldPlaneX = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(-game->player.rot_speed) - game->player.plane_y * sin(-game->player.rot_speed);
		game->player.plane_y = oldPlaneX * sin(-game->player.rot_speed) + game->player.plane_y * cos(-game->player.rot_speed);
	}
	if (key == K_A)
	{
		double oldDirX = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(game->player.rot_speed) - game->player.dir_y * sin(game->player.rot_speed);
		game->player.dir_y = oldDirX * sin(game->player.rot_speed) + game->player.dir_y * cos(game->player.rot_speed);
		double oldPlaneX = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(game->player.rot_speed) - game->player.plane_y * sin(game->player.rot_speed);
		game->player.plane_y = oldPlaneX * sin(game->player.rot_speed) + game->player.plane_y * cos(game->player.rot_speed);
	}

	mlx_clear_window(game->mlx, game->win);
	main_loop(game);
	if (key == K_ESC)
		exit(0);
	return (0);
}

void	draw(t_game *game)
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			game->img.data[y * WIDTH + x] = game->buf[y][x];
		}
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
}


int	main_loop(t_game *game)
{
	int			x;
	t_ray		ray;
	t_player	p;

	x = -1;
	p = game->player;
	while (++x < WIDTH)
	{
		ray.camera_x = 2 * x / (double)WIDTH - 1;
		ray.ray_dir_x = p.dir_x + p.plane_x * ray.camera_x;
		ray.ray_dir_y = p.dir_y + p.plane_y * ray.camera_x;	
		ray.map_x = (int)p.pos_x;
		ray.map_y = (int)p.pos_y;
		ray.delta_dist_x = fabs(1 / ray.ray_dir_x);
		ray.delta_dist_y = fabs(1 / ray.ray_dir_y);
		side_wall(game, &ray);
		ray_hit_wall(game, &ray);
		if (ray.dir_side == 0)
			ray.perp_wall_dist = (ray.map_x - p.pos_x + (1 - ray.step_x) / 2) / ray.ray_dir_x;
		else
			ray.perp_wall_dist = (ray.map_y - p.pos_y + (1 - ray.step_y) / 2) / ray.ray_dir_y; 
		

		int lineHeight = (int)(HEIGHT / ray.perp_wall_dist);

		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if(drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;

		
		int textint;

		if (ray.dir_side == 0 && ray.ray_dir_x < 0)
			textint = NORTH;
		else
			textint = SOUTH;
		
		if (ray.dir_side == 1 && ray.ray_dir_y < 0)
			textint = WEST;
		else
			textint = EAST;
		
		double wallX;
		if (ray.dir_side == 0)
			wallX = game->player.pos_x + ray.perp_wall_dist * ray.ray_dir_y;
		else
			wallX = game->player.pos_y + ray.perp_wall_dist * ray.ray_dir_x;
		wallX -= floor(wallX);

		// x coordinate on the texture
		int texX = (int)(wallX * (double)64);
		if (ray.dir_side == 0 && ray.ray_dir_x > 0)
			texX = 64 - texX - 1;
		if (ray.dir_side  == 1 && ray.ray_dir_y < 0)
			texX = 64 - texX - 1;

		// How much to increase the texture coordinate perscreen pixel
		double step = 1.0 * 64 / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - game->map_info.height / 2 + lineHeight / 2) * step;
		for (int y = drawStart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (64 - 1);
			texPos += step;
			int color = game->player.texture[textint][64 * texY + texX];
			// make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if (ray.dir_side == 1)
				color = (color >> 1) & 8355711;
			
			game->buf[y][x] = color;
			game->re_buf = 1;
		}
		x++;
	}
	draw(game);
	return (0);
}


void	load_image(t_game *game, int tex_num, char *path)
{
	t_img	img;
	int		y;
	int		x;

	img.ptr = mlx_xpm_file_to_image(game->mlx, path, &img.img_width, &img.img_height);
	if (!img.ptr)
	{
		ft_error(game, "wrong file");
	}
	img.data = (int *)mlx_get_data_addr(img.ptr, &img.bpp, &img.size_l, &img.endian);
	y = -1;
	for (int y = 0; y < img.img_height; y++)
	{
		for (int x = 0; x < img.img_width; x++)
		{
			game->player.texture[tex_num][img.img_width * y + x] = img.data[img.img_width * y + x];
		}
	}
	
	mlx_destroy_image(game->mlx, img.ptr);
}


void	get_texture_img(t_game *game)
{
	int i;

	i = -1;
	while (++i < 4)
	{
		load_image(game, i, game->map_info.texture_file[i]);
	}

}

int		game_setting(t_game *game)
{
	game->player.move_speed = 0.6;
	game->player.rot_speed = 0.3;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3d");
	game->img.ptr = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img.data = (int *)mlx_get_data_addr(game->img.ptr, &game->img.bpp, &game->img.size_l, &game->img.endian);
	return (1);
}

void find_player(t_game *game)
{
	int	height;
	int	width;
	
	height = 0;
	while(height < game->map_info.height)
	{
		width = 0;
		while (width < game->map_info.width)
		{
			if (game->map[height][width] == 'N' || game->map[height][width] == 'S' || \
				 game->map[height][width] == 'W' || game->map[height][width] == 'E')
			{
				set_pos(game, game->map[height][width], height, width);
				return ;
			}
			width++;
		}
		height++;
	}
}

int main(int argc, char *argv[])
{
	t_game		game;

	ft_memset(&game, 0, sizeof(t_game));
	validate_arg(&game, argc, argv);
	parsing_cub_file(&game, argv[1]);	

	game_setting(&game);
	find_player(&game);

	game.re_buf = 0;

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			game.buf[i][j] = 0;
		}
	}
	get_texture_img(&game);
	
	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_hook(game.win, X_EVENT_KEY_PRESS, 0, &key_press, &game);
	mlx_loop(game.mlx);
	ft_free_game(&game);
}
