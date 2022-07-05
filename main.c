/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:37:02 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/05 18:30:32 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Cube.h"
void cast_rays(t_mlx *data);

#define mapWidth 24
#define mapHeight 24

void	better_pixel_put(t_image *data, int x, int y, int color)
{
	char *dst;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,3,3,3,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,3,3,3,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


int draw_line(t_mlx_info *mlx_info,int x, int beginY, int endY, int colour)
{
	int beg_y = beginY;
  	// printf("SMORT %i %i %i %i\n",beginX,  beginY,  endX,  endY);
	while (beg_y < endY)
	{
		better_pixel_put(&mlx_info->main_img ,x, beg_y, colour);
		beg_y++;
	}
	return (0);
}

void	init_for_drawing(t_mlx_info *mlx_info, int x, int w)
{
	mlx_info->draw_prop.cameraX = 3 * x / (double) w - 1;
	mlx_info->draw_prop.rayDirX = mlx_info->unique_prop.dirX + mlx_info->unique_prop.planeX 
	* mlx_info->draw_prop.cameraX;
	mlx_info->draw_prop.rayDirY = mlx_info->unique_prop.dirY + mlx_info->unique_prop.planeY 
	* mlx_info->draw_prop.cameraX;
	mlx_info->draw_prop.mapX = (int)mlx_info->unique_prop.posX;
	mlx_info->draw_prop.mapY = (int)mlx_info->unique_prop.posY;
	mlx_info->draw_prop.hit = 0;
	if(mlx_info->draw_prop.rayDirX == 0)
		mlx_info->draw_prop.deltaDistX = 1e30;
	else
		mlx_info->draw_prop.deltaDistX = fabs(1/ mlx_info->draw_prop.rayDirX);
	if(mlx_info->draw_prop.rayDirY == 0)
		mlx_info->draw_prop.deltaDistY = 1e30;
	else
		mlx_info->draw_prop.deltaDistY = fabs(1 / mlx_info->draw_prop.rayDirY);
}

void	check_sideXY(t_mlx_info *mlx_info)
{
	if(mlx_info->draw_prop.rayDirX < 0)
	{
		mlx_info->draw_prop.stepX = -1;
		mlx_info->draw_prop.sideDistX = (mlx_info->unique_prop.posX - mlx_info->draw_prop.mapX) * mlx_info->draw_prop.deltaDistX;
	}else{
		mlx_info->draw_prop.stepX = 1;
		mlx_info->draw_prop.sideDistX = (mlx_info->draw_prop.mapX + 1.0 - mlx_info->unique_prop.posX) * mlx_info->draw_prop.deltaDistX;
	}
	if(mlx_info->draw_prop.rayDirY < 0)
	{
		mlx_info->draw_prop.stepY = -1;
		mlx_info->draw_prop.sideDistY = (mlx_info->unique_prop.posY - mlx_info->draw_prop.mapY) * mlx_info->draw_prop.deltaDistY;
	}else{
		mlx_info->draw_prop.stepY = 1;
		mlx_info->draw_prop.sideDistY = (mlx_info->draw_prop.mapY + 1.0 - mlx_info->unique_prop.posY) * mlx_info->draw_prop.deltaDistY;
	}
}

void	hit_loop(t_mlx_info *mlx_info)
{
	while(mlx_info->draw_prop.hit == 0)
	{
		if(mlx_info->draw_prop.sideDistX < mlx_info->draw_prop.sideDistY)
		{
			mlx_info->draw_prop.sideDistX += mlx_info->draw_prop.deltaDistX;
			mlx_info->draw_prop.mapX += mlx_info->draw_prop.stepX;
			mlx_info->draw_prop.side = 0;
		}else{
			mlx_info->draw_prop.sideDistY += mlx_info->draw_prop.deltaDistY;
			mlx_info->draw_prop.mapY += mlx_info->draw_prop.stepY;
			mlx_info->draw_prop.side = 1;
		}
		if(worldMap[mlx_info->draw_prop.mapX][mlx_info->draw_prop.mapY] > 0)
			mlx_info->draw_prop.hit = 1;
	}
}
void	calculate_wall_dist(t_mlx_info *mlx_info)
{
	if(mlx_info->draw_prop.side == 0)
	{
		mlx_info->draw_prop.perpWallDist = mlx_info->draw_prop.sideDistX - mlx_info->draw_prop.deltaDistX;
	}else{
		mlx_info->draw_prop.perpWallDist = (mlx_info->draw_prop.sideDistY - mlx_info->draw_prop.deltaDistY);
	}
	mlx_info->draw_prop.lineHeight = (int)(mlx_info->window_height / mlx_info->draw_prop.perpWallDist);
	mlx_info->draw_prop.drawStart = -mlx_info->draw_prop.lineHeight / 2 + mlx_info->window_height / 2;
	if(mlx_info->draw_prop.drawStart < 0)
	{
		mlx_info->draw_prop.drawStart = 0;
	}
	mlx_info->draw_prop.drawEnd = mlx_info->draw_prop.lineHeight / 2 + mlx_info->window_height / 2;
	
	if(mlx_info->draw_prop.drawEnd >= mlx_info->window_height)
	{
		mlx_info->draw_prop.drawEnd = mlx_info->window_height - 1;
	}
}

void	color_walls(t_mlx_info *mlx_info, int x)
{
	int color;

	if(worldMap[mlx_info->draw_prop.mapX][mlx_info->draw_prop.mapY] == 1)
		color = 0x00FFFFFF;	
	else if(worldMap[mlx_info->draw_prop.mapX][mlx_info->draw_prop.mapY] == 2)
		color = 0x00FF00FF;
	else if(worldMap[mlx_info->draw_prop.mapX][mlx_info->draw_prop.mapY] == 0)
		color = 0;
	else if(worldMap[mlx_info->draw_prop.mapX][mlx_info->draw_prop.mapY] == 3)
		color = 0x0000FFFF;
	else if(worldMap[mlx_info->draw_prop.mapX][mlx_info->draw_prop.mapY] == 4)
		color = 0x00FFF0FF;
	else
		color = 0;

	if(mlx_info->draw_prop.side == 1)
		color = color / 2;
	draw_line(mlx_info,  x, mlx_info->draw_prop.drawStart, mlx_info->draw_prop.drawEnd, color);
}

void	init_img(t_mlx_info *mlx_info)
{
	//IF there is a leak it's hereeee :)
	mlx_info->main_img.img = mlx_new_image(mlx_info->mlx, mlx_info->window_width, mlx_info->window_height);
	mlx_info->main_img.addr = mlx_get_data_addr(mlx_info->main_img.img, &mlx_info->main_img.bits_per_pixel, &mlx_info->main_img.line_length, &mlx_info->main_img.endian);
}
void	render(t_mlx_info *mlx_info)
{
	int x = 0;
	int w = mlx_info->window_width;
	init_img(mlx_info);
	// mlx_clear_window(mlx_info->mlx, mlx_info->main_win);
	while(x < w)
	{
		init_for_drawing(mlx_info, x, w);
		check_sideXY(mlx_info);
		hit_loop(mlx_info);
		calculate_wall_dist(mlx_info);
		color_walls(mlx_info, x);
		x++;
	};
		mlx_put_image_to_window(mlx_info->mlx, mlx_info->main_win, mlx_info->main_img.img, 0,0);
}

void	init_main(t_mlx_info *mlx_info)
{
	mlx_info->window_width = 800;
	mlx_info->window_height = 500;
	mlx_info->unique_prop.dirX = -1;
	mlx_info->unique_prop.dirY = 0;
	mlx_info->unique_prop.planeX = 0;
	mlx_info->unique_prop.planeY = 0.66;
	mlx_info->unique_prop.rotSpeed = 0.1;
	mlx_info->unique_prop.move_speed = 0.6;
	mlx_info->unique_prop.posX = 22;
	mlx_info->unique_prop.posY = 12;
	mlx_info->mlx_imgs = calloc(4, sizeof(void *));
	mlx_info->main_win = mlx_new_window(mlx_info->mlx, mlx_info->window_width, mlx_info->window_height, "Starting point");
}

void key_W_hook(t_mlx_info *mlx_info)
{
	if(worldMap[(int)mlx_info->unique_prop.posX + (int)mlx_info->unique_prop.dirX * (int)mlx_info->unique_prop.move_speed][(int)mlx_info->unique_prop.posY] != 1)
		{
			mlx_info->unique_prop.posX += mlx_info->unique_prop.dirX * mlx_info->unique_prop.move_speed;
		}
		if(worldMap[(int)mlx_info->unique_prop.posX][(int)mlx_info->unique_prop.posY - (int)mlx_info->unique_prop.dirY * (int)mlx_info->unique_prop.move_speed ] != 1)
		{
			mlx_info->unique_prop.posY += mlx_info->unique_prop.dirY * mlx_info->unique_prop.move_speed;
		}
		mlx_clear_window(mlx_info->mlx, mlx_info->main_win);
		// mlx_destroy_image(mlx_info->mlx, mlx_info->main_img.img);
		render(mlx_info);
}

void	key_S(t_mlx_info *mlx_info)
{
	if(worldMap[(int)mlx_info->unique_prop.posX - (int)mlx_info->unique_prop.dirX * (int) mlx_info->unique_prop.move_speed][(int)mlx_info->unique_prop.posY] != 1)
	{
		mlx_info->unique_prop.posX -= mlx_info->unique_prop.dirX * mlx_info->unique_prop.move_speed;
	}
	if(worldMap[(int)mlx_info->unique_prop.posX][(int)mlx_info->unique_prop.posY - (int)mlx_info->unique_prop.dirY * (int)mlx_info->unique_prop.move_speed ] != 1)
	{
		mlx_info->unique_prop.posY -= mlx_info->unique_prop.dirY * mlx_info->unique_prop.move_speed;
	}
	mlx_clear_window(mlx_info->mlx, mlx_info->main_win);
	// mlx_destroy_image(mlx_info->mlx, mlx_info->main_img.img);
	render(mlx_info);
}

void	key_A(t_mlx_info *mlx_info)
{
		if(worldMap[(int)mlx_info->unique_prop.posX - (int)mlx_info->unique_prop.planeX * (int)mlx_info->unique_prop.move_speed][(int)mlx_info->unique_prop.posY] != 1)
		{
			mlx_info->unique_prop.posX -= mlx_info->unique_prop.planeX * mlx_info->unique_prop.move_speed;
		}
		if(worldMap[(int)mlx_info->unique_prop.posX][(int)mlx_info->unique_prop.posY - (int)mlx_info->unique_prop.planeY * (int)mlx_info->unique_prop.move_speed ] != 1)
		{
			mlx_info->unique_prop.posY -= mlx_info->unique_prop.planeY * mlx_info->unique_prop.move_speed;

		}
		render(mlx_info);
}

void	key_D(t_mlx_info *mlx_info)
{
		if(worldMap[(int)mlx_info->unique_prop.posX - (int)mlx_info->unique_prop.planeX * (int)mlx_info->unique_prop.move_speed][(int)mlx_info->unique_prop.posY] != 1)
		{
			mlx_info->unique_prop.posX += mlx_info->unique_prop.planeX * mlx_info->unique_prop.move_speed;
		}
		if(worldMap[(int)mlx_info->unique_prop.posX][(int)mlx_info->unique_prop.posY - (int)mlx_info->unique_prop.planeY * (int)mlx_info->unique_prop.move_speed ] != 1)
		{
			mlx_info->unique_prop.posY += mlx_info->unique_prop.planeY * mlx_info->unique_prop.move_speed;

		}
		render(mlx_info);
}

void	key_right_arr(t_mlx_info *mlx_info)
{
	double oldDirX = mlx_info->unique_prop.dirX;
	mlx_info->unique_prop.dirX = mlx_info->unique_prop.dirX * cos(-mlx_info->unique_prop.rotSpeed) - mlx_info->unique_prop.dirY * sin(-mlx_info->unique_prop.rotSpeed);
	mlx_info->unique_prop.dirY = oldDirX * sin(-mlx_info->unique_prop.rotSpeed)  + mlx_info->unique_prop.dirY * cos(-mlx_info->unique_prop.rotSpeed);
	double oldplaneX = mlx_info->unique_prop.planeX;
	mlx_info->unique_prop.planeX = mlx_info->unique_prop.planeX * cos(-mlx_info->unique_prop.rotSpeed) - mlx_info->unique_prop.planeY * sin(-mlx_info->unique_prop.rotSpeed);
	mlx_info->unique_prop.planeY = oldplaneX * sin(-mlx_info->unique_prop.rotSpeed) + mlx_info->unique_prop.planeY * cos(-mlx_info->unique_prop.rotSpeed);
	render(mlx_info);
}

void	key_left_arr(t_mlx_info *mlx_info)
{
	double oldDirX = mlx_info->unique_prop.dirX;
	mlx_info->unique_prop.dirX = mlx_info->unique_prop.dirX * cos(mlx_info->unique_prop.rotSpeed) - mlx_info->unique_prop.dirY * sin(mlx_info->unique_prop.rotSpeed);
	mlx_info->unique_prop.dirY = oldDirX * sin(mlx_info->unique_prop.rotSpeed)  + mlx_info->unique_prop.dirY * cos(mlx_info->unique_prop.rotSpeed);
	double oldplaneX = mlx_info->unique_prop.planeX;
	mlx_info->unique_prop.planeX = mlx_info->unique_prop.planeX * cos(mlx_info->unique_prop.rotSpeed) - mlx_info->unique_prop.planeY * sin(mlx_info->unique_prop.rotSpeed);
	mlx_info->unique_prop.planeY = oldplaneX * sin(mlx_info->unique_prop.rotSpeed) + mlx_info->unique_prop.planeY * cos(mlx_info->unique_prop.rotSpeed);
	render(mlx_info);
}

int	key_hook(int keycode,void *mlx)
{
	t_mlx_info *mlx_info = (t_mlx_info *) mlx;
	if(keycode == 13)
	{	
		key_W_hook(mlx_info);
	}
	if (keycode == 1)
	{
		key_S(mlx_info);
	}
	if(keycode == 0)
	{
		key_A(mlx_info);
	}
	if(keycode == 2)
	{
		key_D(mlx_info);
	}
	if(keycode == 124)
	{
		key_right_arr(mlx_info);
	}
	if(keycode == 123)
	{
		key_left_arr(mlx_info);
	}
	if(keycode == 53)
	{
		mlx_destroy_window(mlx_info->mlx, mlx_info->main_win);
		exit(1);
	}
	return 0;
}


int main(void)
{
	t_mlx_info mlx_info;
	mlx_info.mlx = mlx_init();
	if(!mlx_info.mlx)
		return 0;
	init_main(&mlx_info);
	// mlx_info.main_img.img = mlx_new_image(mlx_info.mlx, mlx_info.window_width, mlx_info.window_height);
	// mlx_info.mlx_imgs[0] = mlx_png_file_to_image(mlx_info.mlx, "catto_Tex.png", &w, &h);
	// mlx_put_image_to_window(mlx_info.mlx, mlx_info.main_win, 	mlx_info.mlx_imgs[0], 0,0);
	render(&mlx_info);
	// mlx_loop_hook(mlx_info.mlx, frame_render, &mlx_info);
	mlx_hook(mlx_info.main_win, 2,0,key_hook,&mlx_info);
	mlx_loop(mlx_info.mlx);
}
