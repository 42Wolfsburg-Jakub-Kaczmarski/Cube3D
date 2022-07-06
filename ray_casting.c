/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 10:42:55 by kmilchev          #+#    #+#             */
/*   Updated: 2022/07/06 14:14:58 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube.h"
#include <sys/time.h>

#define mapWidth 24
#define mapHeight 24
// #define screenWidth 640
#define screenWidth mapWidth * IMG_SIDE
// #define screenHeight 480
#define screenHeight mapHeight * IMG_SIDE

int draw_line(mlx_image_t *img,int x, int beginY, int endY, int colour)
{
  	int diff = abs(beginY - endY);
	if (beginY > endY)
	{
		while (diff--)
		{
			mlx_put_pixel(img, x, endY, colour);
			endY++;
		}
	}
	else
	{
		while (diff--)
		{
			mlx_put_pixel(img, x, beginY, colour);
			beginY++;
		}
	}
	return (0);
}




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
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void key_w(t_ray_casting *data)
{
	// printf("here\n");
	// printf("%d\n\n", worldMap[(int)(data->posX + data->dirX * MOVEMENT_SPEED)][(int)data->posY]);
	// // if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
	// printf("Position X = %f\n", data->posX);
	// printf("Position Y = %f\n", data->posY);
	// printf("Direction X = %f\n", data->dirX);
	// printf("Direction Y = %f\n", data->dirY);
	// printf("Projected position X: %f\n", data->posX + data->dirX * MOVEMENT_SPEED);
	// printf("Map box: %d\n", int(data->posX + data->dirX * MOVEMENT_SPEED);
	if (worldMap[(int)(data->posX + data->dirX * MOVEMENT_SPEED)][(int)(data->posY)] == false)
	{
		// printf("here1\n");
		data->posX += data->dirX * MOVEMENT_SPEED;
	}
	if (worldMap[(int)(data->posX)][(int)(data->posY - data->dirY * MOVEMENT_SPEED)] == false)
	{	
		// printf("From second: %d\n", worldMap[(int)(data->posX)][(int)(data->posY - data->dirY * MOVEMENT_SPEED)]);
		// printf("here2\n");
		data->posY += data->dirY * MOVEMENT_SPEED;
	}
}

void key_a(t_ray_casting *data)
{
	
}
void  movement_hook(void *x)
{
  t_mlx *data;
  
  data = x;

	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		key_w(&data->data);
		
}

void init_data_for_ray_cast(t_ray_casting *data)
{
	data->posX = 22;
	data->posY = 12;
	data->dirX = -1;
	data->dirY = 0;
	data->planeX = 0;
	data->planeY = 0.66;
	data->time = 0;
	data->old_time = 0;
	data->confused = true;
}


void do_stuff(t_mlx *mlx_info, t_ray_casting *data)
{
	mlx_delete_image(mlx_info->mlx, mlx_info->img_arr[5]);
	mlx_info->img_arr[5] = mlx_new_image(mlx_info->mlx, screenWidth, screenHeight);
	for(int x = 0; x < screenWidth; x++)
		{
			///INITIALISATIONS
			data->cameraX = 2 * x / (double)screenWidth - 1;
			data->rayDirX = data->dirX + data->planeX * data->cameraX;
			data->rayDirY = data->dirY + data->planeY * data->cameraX;
			data->mapX = (int)(data->posX); //why?
			data->mapY = (int)(data->posY); //why?
			if(data->rayDirX == 0)
				data->deltaDistX = 1e30;//very big number to avoid division by 0
			else
				data->deltaDistX = 1 / data->rayDirX;
			if (data->rayDirY == 0)
				data->deltaDistY = 1e30;
			else
				data->deltaDistY = 1/ data->rayDirY;
			data->hit = false;
			//////////////////////////

			//calculate step and initial sideDist
			if (data->rayDirX < 0)
			{
				data->stepX = -1;
				data->sideDistX = (data->posX - data->mapX) * data->deltaDistX;

			}
			else
			{
				data->stepX = 1;
				data->sideDistX = (data->mapX + 1.0 - data->posX) * data->deltaDistX;
			}
			if (data->rayDirY < 0)
			{
				data->stepY = -1;
				data->sideDistY = (data->posY - data->mapY) * data->deltaDistY;
			}
			else
			{
				data->stepY = 1;
				data->sideDistY = (data->mapY + 1.0 - data->posY) * data->deltaDistY;
			}
			////////////////////////////////////////////
			////DDA
			while(data->hit == false)
			{
				if (data->sideDistX < data->sideDistY)
				{
					data->sideDistX += data->deltaDistX;
					data->mapX += data->stepX;
					data->side = 0;
				}
				else
				{
					data->sideDistY += data->deltaDistY;
					data->mapY += data->stepY;
					data->side = 1;
				}
				if (worldMap[data->mapX][data->mapY] == 1) //char in our case, not int
					data->hit = true; // or just break
			}
			//////////
			//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
			if (data->side == 0)
				data->perpWallDist = data->sideDistX - data->deltaDistX;
			else
				data->perpWallDist = data->sideDistY - data->deltaDistY;
			
			//Calculate height of line to draw on screen
			data->line_height = (int)(screenHeight / data->perpWallDist);
			data->draw_start = -data->line_height / 2 + screenHeight / 2;
			if (data->draw_start < 0)
				data->draw_start = 0;
			data->draw_end = data->line_height / 2 + screenHeight / 2;
			if (data->draw_end >= screenHeight)
				data->draw_end = screenHeight - 1;
			//calculate lowest and highest pixel to fill in current stripe
			if (worldMap[data->mapX][data->mapY] == 1)
				data->colour = 0xFF0000FF;
			else if (worldMap[data->mapX][data->mapY] == 2)
				data->colour = 0xFF00FFFF;
			else if (worldMap[data->mapX][data->mapY] == 3)
				data->colour = 0xFFFF00FF;
			else if (worldMap[data->mapX][data->mapY] == 4)
				data->colour = 0xFFBCFFFF;
			else if (worldMap[data->mapX][data->mapY] == 5)
				data->colour = 0xF0000FFF;
			draw_line(mlx_info->img_arr[5], x, data->draw_start, data->draw_end, data->colour);
   		}
	mlx_image_to_window(mlx_info->mlx, mlx_info->img_arr[5], 0, 0);
}

int main(int argc, char *argv[])
{
	t_mlx mlx_info;

	init_data_for_ray_cast(&mlx_info.data);
	mlx_info.mlx = mlx_init( screenWidth, screenHeight, "Cat shooter", 1);
	mlx_info.img_arr = ft_calloc(10, sizeof(mlx_image_t));
	mlx_info.img_arr[0] = mlx_new_image(mlx_info.mlx, screenWidth, screenHeight);
	memset(mlx_info.img_arr[0]->pixels, 255, screenWidth* screenHeight* sizeof(int));
	mlx_image_to_window(mlx_info.mlx, mlx_info.img_arr[0], 0 ,0);
	do_stuff(&mlx_info, &mlx_info.data);
	
		
	mlx_loop_hook(mlx_info.mlx, &movement_hook, (void*)&mlx_info);
	mlx_loop(mlx_info.mlx);
}