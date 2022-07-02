/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:08:38 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/02 19:29:46 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube.h"

bool	epsilon_function(double target, double patient, double offset)
{
	if (patient < target + offset && patient > target - offset)
		return (true);
	return (false);
}

void fix_rounding_errors(double *ra)
{
	if (epsilon_function(0, *ra, rotationfix) || epsilon_function(2 * PI, *ra, rotationfix))
		*ra = 0;
	else if (epsilon_function(PI, *ra, rotationfix))
		*ra = PI;
	if (epsilon_function(SOUTH, *ra, rotationfix))
		*ra = SOUTH;
	else if (epsilon_function(NORTH, *ra, rotationfix))
		*ra = NORTH;
}

double ray_len(t_mlx *mlx_info, double *rx, double *ry)
{
	double result;
	result = sqrt((mlx_info->px - *rx) * (mlx_info->px - *rx) + ((mlx_info->py - *ry)) * (mlx_info->py - *ry));
	return (result);
}

int draw_rays(t_mlx *mlx_info)
{
	int r;
	int dof;
	int mx;
	int my;
	double ra;
	double rx;
	double ry;
	double yo;
	double xo;
	double horizontal_ray;
	double vertical_ray;
	double rx_temp_h;
	double ry_temp_h;
	double rx_temp_v;
	double ry_temp_v;

	horizontal_ray = vertical_ray = 100000000000;
	// ra = mlx_info->dir;
	ra = mlx_info->dir - DR * 30;
	if (ra < 0)
	{
		ra += 2 * PI;
	}
	if (ra > 2 * PI)
	{
		ra -= 2 * PI;
	}
	// printf("%f\n", ra);
	fix_rounding_errors(&ra);
	// printf("%f\n", ra);
	mlx_delete_image(mlx_info->mlx, mlx_info->img_arr[5]);
	mlx_info->img_arr[5] = mlx_new_image(mlx_info->mlx, mlx_info->map_width * IMG_SIDE, mlx_info->map_height * IMG_SIDE);
	for (r = 0;r < 60; r++)
	{
		printf("Index: %d\n", r);
		dof = 0;
		double aTan = -1/tan(ra);
		if (ra > PI)
		{
			ry = (int)(mlx_info->py/IMG_SIDE) * IMG_SIDE - 0.0001;
			rx = (mlx_info->py - ry) * aTan + mlx_info->px;
			yo = -IMG_SIDE;
			xo = -yo * aTan;
		}
		if (ra < PI)
		{
			ry = (int)(mlx_info->py/IMG_SIDE) * IMG_SIDE + IMG_SIDE;
			rx = (mlx_info->py - ry) * aTan + mlx_info->px;
			yo = IMG_SIDE;
			xo = -yo * aTan;
		}
		if (ra == 0 || ra == PI)
		{
			rx = mlx_info->px;
			ry = mlx_info->py;
			dof = 8;
		}
		while(dof < 8)
		{
			mx = (int)(rx / IMG_SIDE);
			my = (int)(ry / IMG_SIDE);
			
			if (mx > 0 && my > 0 && mx < mlx_info->map_width && my < mlx_info->map_height && mlx_info->map[my][mx] == '1')
				dof = 8;
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		rx_temp_h = rx;
		ry_temp_h = ry;
		horizontal_ray = ray_len(mlx_info, &rx, &ry);


		// ////////////////VERTICAL
		dof = 0;
		double nTan = -tan(ra);
		if (ra > SOUTH && ra < NORTH)
		{
			rx = (int)(mlx_info->py/IMG_SIDE) * IMG_SIDE - 0.0001;
			ry = (mlx_info->px - rx) * nTan + mlx_info->py;
			xo = -IMG_SIDE;
			yo = -xo * nTan;
		}
		if (ra < SOUTH || ra > NORTH)
		{
			rx = (int)(mlx_info->px/IMG_SIDE) * IMG_SIDE + IMG_SIDE;
			ry = (mlx_info->px - rx) * nTan + mlx_info->py;
			xo = IMG_SIDE;
			yo = -xo * nTan;
		}
		if (ra == 0 || ra == PI)
		{
			rx = mlx_info->px;
			ry = mlx_info->py;
			dof = 8;
		}
		while(dof < 8)
		{
			mx = (int)(rx / IMG_SIDE);
			my = (int)(ry / IMG_SIDE);
			if (mx > 0 && my > 0 && mx < mlx_info->map_width && my < mlx_info->map_height && mlx_info->map[my][mx] == '1')
				dof = 8;
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		// mlx_delete_image(mlx_info->mlx, mlx_info->img_arr[5]);
		// mlx_info->img_arr[5] = mlx_new_image(mlx_info->mlx, mlx_info->map_width * IMG_SIDE, mlx_info->map_height * IMG_SIDE);
		rx_temp_v = rx;
		ry_temp_v = ry;	
		vertical_ray = ray_len(mlx_info, &rx, &ry);
		if (horizontal_ray >= vertical_ray)
		{
			rx = rx_temp_v;
			ry = ry_temp_v;
		}
		if (vertical_ray > horizontal_ray)
		{
			rx = rx_temp_h;
			ry = ry_temp_h;
		}
		// draw_line(mlx_info->img_arr[5], mlx_info->px + PLAYER_SIZE / 2, mlx_info->py + PLAYER_SIZE / 2, rx, ry, 0xFF0000FF);

		ra += DR;
		printf("RA: %f\n", ra);
		
	}
		mlx_image_to_window(mlx_info->mlx, mlx_info->img_arr[5], 0, 0);
		mlx_set_instance_depth(mlx_info->img_arr[5]->instances, 999);
	
	
	return 0;
}


void load_textures(t_mlx *mlx)
{
	//Empty space
	mlx->img_arr[1] = mlx_new_image(mlx->mlx, IMG_SIDE, IMG_SIDE);
	int i = 0;
	int j = 0;
	while(i < IMG_SIDE)
	{
		j = 0;
		while(j < IMG_SIDE)
		{
			mlx_put_pixel(mlx->img_arr[1], i, j, 0xFFFFFF);
			j++;
		}
		i++;
	}
	//Wall
	mlx->img_arr[2] = mlx_new_image(mlx->mlx, IMG_SIDE, IMG_SIDE);
	i = 0;
	j = 0;
	 while(i < IMG_SIDE)
	{
		j = 0;
		while(j < IMG_SIDE)
		{
			mlx_put_pixel(mlx->img_arr[2], i, j, 0x0000FF);
			j++;
		}
		i++;
	}
	//Load_colors for now
}





void    init_mlx_thingy(t_mlx *mlx_info)
{
	mlx_info->px = 200;
    mlx_info->py = 200;
	mlx_info->wx = 0;
	mlx_info->wy = 0;
	mlx_info->dir = SOUTH;
    mlx_info->mlx = mlx_init((mlx_info->map_width - 1 )* IMG_SIDE, (mlx_info->map_height) * IMG_SIDE, "Cat shooter", 1);
    mlx_info->img_arr = ft_calloc(1000,sizeof(mlx_image_t));
	draw_grid(mlx_info);
	draw_player(mlx_info);
	draw_rays(mlx_info);
}

bool check_movement(t_mlx *data)
{

	int y_pos0 = (data->pdy + data->py - (data->py / IMG_SIDE)) / IMG_SIDE;
	int x_pos0 = (data->pdx + data->px - (data->px / IMG_SIDE)) / IMG_SIDE;
	int x_pos1 = (data->pdx + data->px + PLAYER_SIZE - (data->px / IMG_SIDE)) / IMG_SIDE;
	int y_pos1 = (data->pdy + data->py - (data->py / IMG_SIDE)) / IMG_SIDE;
	int x_pos2 = (data->pdx + data->px + PLAYER_SIZE - (data->px / IMG_SIDE)) / IMG_SIDE;
	int y_pos2 = (data->pdy + data->py + PLAYER_SIZE - (data->py / IMG_SIDE)) / IMG_SIDE;
	int x_pos3 = (data->pdx + data->px - (data->px / IMG_SIDE)) / IMG_SIDE;
	int y_pos3 = (data->pdy + data->py + PLAYER_SIZE - (data->py / IMG_SIDE)) / IMG_SIDE;
	
	// ft_putstr_fd("X Y Map[i]\n", 2);
	// ft_putnbr_fd(x_pos, 2);
	// ft_putchar_fd(' ',2);
	// ft_putnbr_fd(y_pos, 2);
	// ft_putchar_fd(' ',2);
	// ft_putchar_fd(data->map[y_pos][x_pos], 2);
	// ft_putchar_fd('\n',2);
	// printf("X: %d Y: %d Map[i] = ", x_pos, y_pos, data->map[y_pos][x_pos]);
	if (data->map[y_pos0][x_pos0] == '1'
		|| data->map[y_pos1][x_pos1] == '1'
		|| data->map[y_pos2][x_pos2] == '1'
		|| data->map[y_pos3][x_pos3] == '1'
		)
		return (true);
	return (false);
}

void  movement_hook(void *x)
{
	t_mlx *data;
  
	data = x;

	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		key_w(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		key_s(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		key_a(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		key_d(data);

	
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		key_right_arrow(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		key_left_arrow(data);  
	mlx_delete_image(data->mlx, data->img_arr[PLAYER]);
	draw_player(data);	
	draw_rays(data);
}

#define mapWidth 24
#define mapHeight 24
#define screenWidth 800
#define screenHeight 1200

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
double posX = 22; //Player starting position
double posY = 12; 
	double move_speed = 0.1;
	double rotSpeed = 0.01;

	double dirX = -1;
	double dirY = 0; // Initial direction vector
			double planeX = 0;
	double planeY = 0.66; //The 2d raycaster version of camera plane
void draw(t_mlx *mlx_info);
void	handly_hand(void *tmp)
{
	t_mlx *mlx_info = (t_mlx*)tmp;
	if (mlx_is_key_down(mlx_info->mlx, MLX_KEY_W))
	{
		if(worldMap[(int)posX + (int)dirX * (int)move_speed][(int)posY] != 1)
		{
			posX += dirX * move_speed;
		}
		if(worldMap[(int)posX][(int)posY - (int)dirY * (int)move_speed ] != 1)
		{
			posY += dirY * move_speed;

		}
		if(worldMap[(int)posX + (int)dirX * (int)move_speed][(int)posY] == 1 && worldMap[(int)posX][(int)posY - (int)dirY * (int)move_speed ] == 1)
		{
					perror("Cannot move Backwards");
		}else
			draw(mlx_info);
	}
	if (mlx_is_key_down(mlx_info->mlx, MLX_KEY_S))
	{
		if(worldMap[(int)posX - (int)dirX * (int)move_speed][(int)posY] != 1)
		{
			posX -= dirX * move_speed;
		}
		if(worldMap[(int)posX][(int)posY - (int)dirY * (int)move_speed ] != 1)
		{
			posY -= dirY * move_speed;

		}
		if(worldMap[(int)posX][(int)posY - (int)dirY * (int)move_speed ] == 1 && worldMap[(int)posX - (int)dirX * (int)move_speed][(int)posY] == 1)
		{
					perror("Cannot move Backwards");
		}else{
							draw(mlx_info);
		}

	
	}
		if (mlx_is_key_down(mlx_info->mlx, MLX_KEY_D))
	{
		double oldDirX = dirX;
		dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
		dirY = oldDirX * sin(-rotSpeed)  + dirY * cos(-rotSpeed);
		double oldplaneX = planeX;
		planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
		planeY = oldplaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
		draw(mlx_info);
	}
	if (mlx_is_key_down(mlx_info->mlx, MLX_KEY_A))
	{
		double oldDirX = dirX;
		dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
		dirY = oldDirX * sin(rotSpeed)  + dirY * cos(rotSpeed);
		double oldplaneX = planeX;
		planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
		planeY = oldplaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
		draw(mlx_info);
	}

	// if (mlx_is_key_down(mlx_info->mlx, MLX_KEY_D))
	// {
		
	// }
	
}

void draw(t_mlx *mlx_info)
{

	int x = 0;
	int w = screenWidth;
	mlx_delete_image(mlx_info->mlx, mlx_info->img_arr[5]);
	mlx_info->img_arr[5] = mlx_new_image(mlx_info->mlx, screenWidth, screenHeight);
	while(x < w)
	{
		double cameraX =  3 * x / (double) w - 1; // X coordinate in camera space
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		int mapX = (int)posX;
		int mapY = (int)posY;

		double sideDistX;
		double sideDistY;
		
		double deltaDistX;
		double deltaDistY;
		if(rayDirX == 0)
		{
			deltaDistX = 1e30;
		}else{
			deltaDistX = fabs(1/ rayDirX);
		}
		if(rayDirY == 0)
		{
			deltaDistY = 1e30;
		}else{
			deltaDistY = fabs(1 / rayDirY);
		}
		double perpWallDist;
		
		int stepX;
		int stepY;
		
		int hit = 0; // Check if wall was hit
		int side;
		
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}else{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}else{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		
		while(hit == 0)
		{
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}else{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if(worldMap[mapX][mapY] > 0) hit = 1;
		}
		if(side == 0)
		{
			perpWallDist = sideDistX - deltaDistX;
		}else{
			perpWallDist = (sideDistY - deltaDistY);
		}



		int lineHeight = (int)(2.5 * screenHeight / perpWallDist);
		int drawStart = -lineHeight / 2 + screenHeight / 2;
		if(drawStart < 0)
		{
			drawStart = 0;
		}
		int drawEnd = lineHeight / 2 + screenHeight / 2;
		
		if(drawEnd >= lineHeight)
		{
			drawEnd = lineHeight - 1;
		}

		int color;

		if(worldMap[mapX][mapY] == 1)
		{
			color = 0xFF0000FF;	
		}else if(worldMap[mapX][mapY] == 2)
		{
			color = 0xFF0000FF;
		}else if(worldMap[mapX][mapY] == 0)
		{
			color = 0;
		}else if(worldMap[mapX][mapY] == 3)
		{
			color = 0xFF0000FF;
		}else if(worldMap[mapX][mapY] == 4)
		{
			perror("4 found\n");
			color = 0xFF0000FF;
		}
		if(side == 1)
		{
			color = color / 2;
		}
		draw_line(mlx_info->img_arr[5],  x, drawStart, drawEnd, color);
		x++;
	}
	mlx_image_to_window(mlx_info->mlx, mlx_info->img_arr[5], 0, 0);
}
int main(int argc, char **argv)
{
    t_mlx   mlx_info;
	if(argc && argv)
	{}
    // if(argc != 2 || check_map(argv, &mlx_info) == 0)
    // {
    //     printf("Error\n");
    //     return (0);
    // 
    // init_mlx_thingy(&mlx_info);
	mlx_info.mlx = mlx_init(screenWidth, screenHeight, "Render thing", 1) ;
	
	// mlx_loop_hook(mlx_info.mlx, &movement_hook, (void*)&mlx_info);
	// mlx_info
		// mlx_delete_image(mlx_info->mlx, mlx_info->img_arr[5]);
	mlx_info.img_arr = ft_calloc(sizeof(mlx_image_t), 10);
	draw(&mlx_info);
	mlx_loop_hook(mlx_info.mlx, handly_hand, (void *)&mlx_info);
	mlx_loop(mlx_info.mlx);
}

/////SET Z later = ask Djaisin how