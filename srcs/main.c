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

void	verLine(t_ray *rcasting, int x, int y1, int y2, int color)
{
	int	y;

	y = y1;
	while (y <= y2)
	{
		mlx_pixel_put(rcasting->mlx, rcasting->win, x, y, color);
		y++;
	}
}

int	key_press(int key, t_game *game)
{
	if (key == K_W)
	{
		if (!game->ray.worldmap[(int)(game->ray.posX + game->ray.dirX * game->ray.moveSpeed)][(int)(game->ray.posY)])
			game->ray.posX += game->ray.dirX * game->ray.moveSpeed;
		if (!game->ray.worldmap[(int)(game->ray.posX)][(int)(game->ray.posY + game->ray.dirY * game->ray.moveSpeed)])
			game->ray.posY += game->ray.dirY * game->ray.moveSpeed;
	}

	if (key == K_S)
	{
		if (!game->ray.worldmap[(int)(game->ray.posX - game->ray.dirX * game->ray.moveSpeed)][(int)(game->ray.posY)])
			game->ray.posX -= game->ray.dirX * game->ray.moveSpeed;
		if (!game->ray.worldmap[(int)(game->ray.posX)][(int)(game->ray.posY - game->ray.dirY * game->ray.moveSpeed)])
			game->ray.posY -= game->ray.dirY * game->ray.moveSpeed;
	}

	if (key == K_D)
	{
		double oldDirX = game->ray.dirX;
		game->ray.dirX = game->ray.dirX * cos(-game->ray.rotSpeed) - game->ray.dirY * sin(-game->ray.rotSpeed);
		game->ray.dirY = oldDirX * sin(-game->ray.rotSpeed) + game->ray.dirY * cos(-game->ray.rotSpeed);
		double oldPlaneX = game->ray.planeX;
		game->ray.planeX = game->ray.planeX * cos(-game->ray.rotSpeed) - game->ray.planeY * sin(-game->ray.rotSpeed);
		game->ray.planeY = oldPlaneX * sin(-game->ray.rotSpeed) + game->ray.planeY * cos(-game->ray.rotSpeed);
	}
	if (key == K_A)
	{
		double oldDirX = game->ray.dirX;
		game->ray.dirX = game->ray.dirX * cos(game->ray.rotSpeed) - game->ray.dirY * sin(game->ray.rotSpeed);
		game->ray.dirY = oldDirX * sin(game->ray.rotSpeed) + game->ray.dirY * cos(game->ray.rotSpeed);
		double oldPlaneX = game->ray.planeX;
		game->ray.planeX = game->ray.planeX * cos(game->ray.rotSpeed) - game->ray.planeY * sin(game->ray.rotSpeed);
		game->ray.planeY = oldPlaneX * sin(game->ray.rotSpeed) + game->ray.planeY * cos(game->ray.rotSpeed);
	}

	mlx_clear_window(game->ray.mlx, game->ray.win);
	main_loop(game);
	if (key == K_ESC)
		exit(0);
	return (0);
}


int	main_loop(t_game *game)
{
	int	x;
	t_ray rcasting;

	rcasting = game->ray;

	x = 0;
	while (x < WIDTH)
	{
		double cameraX = 2 * x / (double)WIDTH - 1; 
		double rayDirX = rcasting.dirX + rcasting.planeX * cameraX;
		double rayDirY = rcasting.dirY + rcasting.planeY * cameraX;
		
		int mapX = (int)rcasting.posX;
		int mapY = (int)rcasting.posY;

		double sideDistX;
		double sideDistY;
		
		double deltaDistX = (rayDirX == 0) ? 0 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 0 : fabs(1 / rayDirY);

		double perpWallDist;

		int stepX;
		int stepY;

		int hit = 0; 
		int side;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (rcasting.posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - rcasting.posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (rcasting.posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - rcasting.posY) * deltaDistY;
		}

		while (hit == 0)
		{
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
			if (rcasting.worldmap[mapX][mapY] > 0) 
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - rcasting.posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - rcasting.posY + (1 - stepY) / 2) / rayDirY;

		int lineHeight = (int)(HEIGHT / perpWallDist);

		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if(drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;

		int	color;

		if (rcasting.worldmap[mapY][mapX] == 1)
			color = 0xFF0000;
		else if (rcasting.worldmap[mapY][mapX] == 2)
			color = 0x00FF00;
		else if (rcasting.worldmap[mapY][mapX] == 3)
			color = 0x0000FF;
		else if (rcasting.worldmap[mapY][mapX] == 4)
			color = 0xFFFFFF;
		else
			color = 0xFFFF00;
		
		

		verLine(&rcasting, x, drawStart, drawEnd, color);
		
		x++;
	}

	return (0);
}

int main(int argc, char *argv[])
{
	t_game		game;

	init_game_struct(&game);
	validate_arg(&game, argc, argv);
	parsing_cub_file(&game, argv[1]);


	int	height;
	int	width;
	height = 0;
	while(height < game.map_height)
	{
		width = 0;
		while (width < game.map_width)
		{
			if (game.map[height][width] == 'N' || game.map[height][width] == 'S' || \
				 game.map[height][width] == 'W' || game.map[height][width] == 'E')
			{
				game.ray.posX = width;
				game.ray.posY = height;
				break;
			}
			width++;
		}
		height++;
	}


	game.ray.mlx = mlx_init();
	game.ray.dirX = -1;
	game.ray.dirY = 0;
	//카메라 평면
	game.ray.planeX = 0;
	game.ray.planeY = 0.66;
	//이동 속도
	game.ray.moveSpeed = 1;
	game.ray.rotSpeed = 0.5;

	int map_h = 0;

	while (game.map[map_h])
		map_h++;
	for (int i = 0; i < map_h; i++)
	{
		for (int j = 0; j < ft_strlen(game.map[i]); j++)
		{
			game.ray.worldmap[i][j] = game.map[i][j] - '0';
		}
	}

	game.ray.win = mlx_new_window(game.ray.mlx, WIDTH, HEIGHT, "cub3d");
	mlx_loop_hook(game.ray.mlx, &main_loop, &game);
	mlx_hook(game.ray.win, X_EVENT_KEY_PRESS, 0, &key_press, &game);
	mlx_loop(game.ray.mlx);
	ft_free_game(&game);
}
