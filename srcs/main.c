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
		set_dir(game, 1, 0);
		set_plane(game, 0, 0.66);
	}
	if (pos == 'W')
	{
		set_dir(game, -1, 0);
		set_plane(game, 0, -0.66);
	}
	if (pos == 'S')
	{
		set_dir(game, 0, 1);
		set_plane(game, -0.66, 0);
	}
	if (pos == 'N')
	{
		set_dir(game, 0, -1);
		set_plane(game, 0.66, 0);
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
		if (game->map[(int)(game->player.pos_x + game->player.dir_x * game->player.move_speed)][(int)(game->player.pos_y)] != '1')
			game->player.pos_x += game->player.dir_x * game->player.move_speed;
		if (game->map[(int)(game->player.pos_x)][(int)(game->player.pos_y + game->player.dir_y * game->player.move_speed)] != '1')
			game->player.pos_y += game->player.dir_y * game->player.move_speed;
	}
	//move backwards if no wall behind you
	if (key == K_S)
	{
		if (game->map[(int)(game->player.pos_x - game->player.dir_x * game->player.move_speed)][(int)(game->player.pos_y)] != '1')
			game->player.pos_x -= game->player.dir_x * game->player.move_speed;
		if (game->map[(int)(game->player.pos_x)][(int)(game->player.pos_y - game->player.dir_y * game->player.move_speed)] != '1')
			game->player.pos_y -= game->player.dir_y * game->player.move_speed;
	}
	//rotate to the right
	if (key == K_D)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(game->player.rot_speed) - game->player.dir_y * sin(game->player.rot_speed);
		game->player.dir_y = oldDirX * sin(game->player.rot_speed) + game->player.dir_y * cos(game->player.rot_speed);
		double oldPlaneX = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(game->player.rot_speed) - game->player.plane_y * sin(game->player.rot_speed);
		game->player.plane_y = oldPlaneX * sin(game->player.rot_speed) + game->player.plane_y * cos(game->player.rot_speed);
	}
	//rotate to the left
	if (key == K_A)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(-game->player.rot_speed) - game->player.dir_y * sin(-game->player.rot_speed);
		game->player.dir_y = oldDirX * sin(-game->player.rot_speed) + game->player.dir_y * cos(-game->player.rot_speed);
		double oldPlaneX = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(-game->player.rot_speed) - game->player.plane_y * sin(-game->player.rot_speed);
		game->player.plane_y = oldPlaneX * sin(-game->player.rot_speed) + game->player.plane_y * cos(-game->player.rot_speed);
	}
	if (key == K_ESC)
		exit(0);
	mlx_clear_window(game->mlx, game->win);
	main_loop(game);
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

static int	arr_to_hex(int *arr)
{
	int	hex;

	hex = 256 * 256 * arr[0] + 256 * arr[1] + arr[2];
	return (hex);
}

void	calc(t_game *game)
{
	//FLOOR CASTING
	for(int y = 0; y < HEIGHT; y++)
	{
		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		float rayDirX0 = game->player.dir_x - game->player.plane_x;
		float rayDirY0 = game->player.dir_y - game->player.plane_y;
		float rayDirX1 = game->player.dir_x + game->player.plane_x;
		float rayDirY1 = game->player.dir_y + game->player.plane_y;

		// Current y position compared to the center of the screen (the horizon)
		int p = y - HEIGHT / 2;

		// Vertical position of the camera.
		float posZ = 0.5 * HEIGHT;

		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
		float rowDistance = posZ / p;

		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / WIDTH;
		float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / WIDTH;

		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		float floorX = game->player.pos_x + rowDistance * rayDirX0;
		float floorY = game->player.pos_y + rowDistance * rayDirY0;

		for(int x = 0; x < WIDTH; ++x)
		{
			// the cell coord is simply got from the integer parts of floorX and floorY
			int cellX = (int)(floorX);
			int cellY = (int)(floorY);

			// get the texture coordinate from the fractional part
			int tx = (int)(texWidth * (floorX - cellX)) & (texWidth - 1);
			int ty = (int)(texHeight * (floorY - cellY)) & (texHeight - 1);

			floorX += floorStepX;
			floorY += floorStepY;

			// choose texture and draw the pixel
			int floorTexture = 4;
			int ceilingTexture = 5;

			int color;

			// floor
			color = game->player.texture[floorTexture][texWidth * ty + tx];
			color = (color >> 1) & 8355711; // make a bit darker

			game->buf[y][x] = color;

			//ceiling (symmetrical, at screenHeight - y - 1 instead of y)
			color = game->player.texture[ceilingTexture][texWidth * ty + tx];
			color = (color >> 1) & 8355711; // make a bit darker

			game->buf[HEIGHT - y - 1][x] = color;
		}
	}
	//WALL CASTING
	for(int x = 0; x < WIDTH; x++)
	{
		double cameraX = 2 * x / (double)WIDTH - 1;
		double rayDirX = game->player.dir_x + game->player.plane_x * cameraX;
		double rayDirY = game->player.dir_y + game->player.plane_y * cameraX;
		
		int mapX = (int)game->player.pos_x;
		int mapY = (int)game->player.pos_y;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;
		
		 //length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;
		
		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;
		
		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (game->player.pos_x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->player.pos_x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (game->player.pos_y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->player.pos_y) * deltaDistY;
		}

		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (game->map[mapX][mapY] == '1') hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - game->player.pos_x + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - game->player.pos_y + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(HEIGHT / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if(drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;


		// calculate value of wallX
		double wallX;
		if (side == 0)
			wallX = game->player.pos_y + perpWallDist * rayDirY;
		else
			wallX = game->player.pos_x + perpWallDist * rayDirX;
		wallX -= floor(wallX);



		int textint;

		if (side == 1 && stepY < 0)
			textint = NORTH;
		else if (side == 1)
			textint = SOUTH;
		else if (stepX < 0)
			textint = WEST;
		else
			textint = EAST;

		// x coordinate on the texture
		int texX = (int)(wallX * (double)texWidth);
		if (side == 0 && rayDirX > 0)
			texX = texWidth - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = texWidth - texX - 1;

		// How much to increase the texture coordinate perscreen pixel
		double step = 1.0 * texHeight / lineHeight;

		// Starting texture coordinate
		double texPos = (drawStart - HEIGHT / 2 + lineHeight / 2) * step;

		for (int y = drawStart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;

			int color = game->player.texture[textint][texHeight * texY + texX];

			// make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if (side == 1)
				color = (color >> 1) & 8355711;

			game->buf[y][x] = color;
		}

		//FLOOR CASTING (vertical version, directly after drawing the vertical wall stripe for the current x)
		double floorXWall, floorYWall; //x, y position of the floor texel at the bottom of the wall

		//4 different wall directions possible
		if(side == 0 && rayDirX > 0)
		{
			floorXWall = mapX;
			floorYWall = mapY + wallX;
		}
		else if(side == 0 && rayDirX < 0)
		{
			floorXWall = mapX + 1.0;
			floorYWall = mapY + wallX;
		}
		else if(side == 1 && rayDirY > 0)
		{
			floorXWall = mapX + wallX;
			floorYWall = mapY;
		}
		else
		{
			floorXWall = mapX + wallX;
			floorYWall = mapY + 1.0;
		}

		double distWall, distPlayer, currentDist;

		distWall = perpWallDist;
		distPlayer = 0.0;

		if (drawEnd < 0) drawEnd = HEIGHT; //becomes < 0 when the integer overflows

		//draw the floor from drawEnd to the bottom of the screen
		for(int y = drawEnd + 1; y < HEIGHT; y++)
		{
			//floor
			game->buf[y][x] = arr_to_hex(game->map_info.f_rgb);
			//ceiling (symmetrical!)
			game->buf[HEIGHT - y][x] = arr_to_hex(game->map_info.c_rgb);
		}
	}
}

int	main_loop(t_game *game)
{
	calc(game);
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

#include <stdio.h>

int		game_setting(t_game *game)
{
	int i;

	i = -1;
	game->player.move_speed = 0.6;
	game->player.rot_speed = 0.3;
	game->mlx = mlx_init();
	game->buf = ft_calloc(HEIGHT, sizeof(int *));

	while (++i < HEIGHT)
	{
		game->buf[i] = ft_calloc(WIDTH, sizeof(int));
	}
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

#include <stdio.h>

int main(int argc, char *argv[])
{
	t_game		game;

	ft_memset(&game, 0, sizeof(t_game));
	validate_arg(&game, argc, argv);
	parsing_cub_file(&game, argv[1]);	
	game_setting(&game);
	find_player(&game);


	
	for (int i = 0; i < 6; i++)
	{
		if (!(game.player.texture[i] = (int *)malloc(sizeof(int) * (texHeight * texWidth))))
			return (-1);
	}
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < texHeight * texWidth; j++)
		{
			game.player.texture[i][j] = 0;
		}
	}
	get_texture_img(&game);

	game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "cub3d");
	game.img.ptr = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	game.img.data = (int *)mlx_get_data_addr(game.img.ptr, &game.img.bpp, &game.img.size_l, &game.img.endian);

	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_hook(game.win, X_EVENT_KEY_PRESS, 0, &key_press, &game);
	mlx_loop(game.mlx);
	ft_free_game(&game);
}
