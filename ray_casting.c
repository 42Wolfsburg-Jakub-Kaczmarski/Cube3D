/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 10:42:55 by kmilchev          #+#    #+#             */
/*   Updated: 2022/07/05 15:45:44 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube.h"
#include <sys/time.h>

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
//#define screenWidth mapWidth * IMG_SIDE
#define screenHeight 480
//#define screenHeight mapHeight * IMG_SIDE
int draw_line(mlx_image_t *img,  int beginX, int beginY, int endX, int endY, int colour)
{
	double	deltaX;
	double	deltaY;
	int 	pixels;
	double 	pixelX;
	double 	pixelY;

  	// printf("SMORT %i %i %i %i\n",beginX,  beginY,  endX,  endY);
	deltaX = endX - beginX;
	deltaY = endY - beginY;
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	pixelX = beginX;
	pixelY = beginY;
	deltaX /= pixels;
	deltaY /= pixels;
	while (pixels)
	{
		mlx_put_pixel(img, pixelX, pixelY, colour);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
	return (0);
}

void  movement_hook(void *x)
{
  t_mlx *data;
  
  data = x;

	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
}


typedef struct s_ray_casting
{
	//Player position
	double  posX;
	double  posY;
	//Make sure the camera plane is perpendicular to the direction, but you can change the length of it.
	//Direciton
	double  dirX;
	double  dirY;
  //Plane
	double  planeX;
	double  planeY;
  //the time difference between these two -> how much you should move when a certain key is pressed
  //and for the FPS counter.
	double  time;
	double  old_time;
	//the x-coordinate on the camera plane that the current x-coordinate of the screen represents,
	//done this way so that the right side of the screen will get coordinate 1,
	//the center of the screen gets coordinate 0, and the left side of the screen gets coordinate -1. 
	double  cameraX;
	//Ray direction
	double  rayDirX;
	double  rayDirY;
	//mapX and mapY represent the current square of the map the ray is in.
	int     mapX;
	int     mapY;
	//sideDistX and sideDistY are initially the distance the ray has to travel from its start position
	//to the first x-side and the first y-side. They will be incremented while steps are taken.
	double sideDistX;
	double sideDistY;
	//deltaDistX and deltaDistY are the distance the ray has to travel to go from 1 x-side to the next x-side,
	//or from 1 y-side to the next y-side.
	double deltaDistX;
	double deltaDistY;
	//used later to calculate the length of the ray
	double perpWallDist;
	//used to determinate whether or not the coming loop may be ended
	bool  hit;
	int  side; //0 for x-side, 1 for y-side
	//direction indicaiton
	int	stepX;
	int stepY;
	long long int colour;
	int line_height;
	int draw_start;
	int draw_end;
	//for the loop, idk yet
	bool confused;
} t_ray_casting;

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

int main(int argc, char *argv[])
{
	t_ray_casting data;
	t_mlx mlx_info;
  
	// mlx_info.mlx = mlx_init( mapWidth * IMG_SIDE, mapHeight * IMG_SIDE, "Cat shooter", 1);
	init_data_for_ray_cast(&data);
	mlx_info.mlx = mlx_init( screenWidth,screenHeight, "Cat shooter", 1);
	
	mlx_info.img_arr[0] = mlx_new_image(mlx_info.mlx, screenWidth, screenHeight);
	while(data.confused)
	{
		for(int x = 0; x < screenWidth; x++)
		{
			///INITIALISATIONS
			data.cameraX = 2 * x / (double)screenWidth - 1;
			data.rayDirX = data.dirX + data.planeX * data.cameraX;
			data.rayDirY = data.dirY + data.planeY * data.cameraX;
			data.mapX = (int)(data.posX); //why?
			data.mapY = (int)(data.posY); //why?
			if(data.rayDirX == 0)
				data.deltaDistX = 1e30;//very big number to avoid division by 0
			else
				data.deltaDistX = 1 / data.rayDirX;
			if (data.rayDirY == 0)
				data.deltaDistY = 1e30;
			else
				data.deltaDistY = 1/ data.rayDirY;
			data.hit = false;
			//////////////////////////

			//calculate step and initial sideDist
			if (data.rayDirX < 0)
			{
				data.stepX = -1;
				data.sideDistX = (data.posX - data.mapX) * data.deltaDistX;

			}
			else
			{
				data.stepX = 1;
				data.sideDistX = (data.mapX + 1.0 - data.posX) * data.deltaDistX;
			}
			if (data.rayDirY < 0)
			{
				data.stepY = -1;
				data.sideDistY = (data.posY - data.mapY) * data.deltaDistY;
			}
			else
			{
				data.stepY = 1;
				data.sideDistY = (data.mapY + 1.0 - data.posY) * data.deltaDistY;
			}
			////////////////////////////////////////////
			////DDA
			while(data.hit == false)
			{
				if (data.sideDistX < data.sideDistY)
				{
					data.sideDistX += data.deltaDistX;
					data.mapX += data.stepX;
					data.side = 0;
				}
				else
				{
					data.sideDistY += data.deltaDistY;
					data.mapY += data.stepY;
					data.side = 1;
				}
				if (worldMap[data.mapX][data.mapY] == 1) //char in our case, not int
					data.hit = true; // or just break
			}
			//////////
			//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
			if (data.side == 0)
				data.perpWallDist = data.sideDistX - data.deltaDistX;
			else
				data.perpWallDist = data.sideDistY - data.deltaDistY;
			
			//Calculate height of line to draw on screen
			data.line_height = (int)(screenHeight / data.perpWallDist);
			data.draw_start = -data.line_height / 2 + screenHeight / 2;
			if (data.draw_start < 0)
				data.draw_start = 0;
			data.draw_end = data.line_height / 2 + screenHeight / 2;
			if (data.draw_end >= screenHeight)
				data.draw_end = screenHeight - 1;
			//calculate lowest and highest pixel to fill in current stripe
			if (worldMap[data.mapX][data.mapY] == 1)
				data.colour = 0xFF0000FF;
			else if (worldMap[data.mapX][data.mapY] == 2)
				data.colour = 0xFF00FFFF;
			else if (worldMap[data.mapX][data.mapY] == 3)
				data.colour = 0xFFFF00FF;
			else if (worldMap[data.mapX][data.mapY] == 4)
				data.colour = 0xFFBCFFFF;
			else if (worldMap[data.mapX][data.mapY] == 5)
				data.colour = 0xF0000FFF;
			draw_line(mlx_info.img_arr[0], 0, data.draw_start, 0, data.draw_end, data.colour);
   		}
		data.old_time = data.time;
		data.time = gettimeofday();
	}
	mlx_loop_hook(mlx_info.mlx, &movement_hook, (void*)&mlx_info);
	mlx_loop(mlx_info.mlx);
}