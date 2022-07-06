/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 10:42:55 by kmilchev          #+#    #+#             */
/*   Updated: 2022/07/06 19:58:25 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube.h"
#include <sys/time.h>

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480


void draw_line(mlx_image_t *img, int x, int beginY, int endY, int colour)
{
	while(beginY < endY)
	{
		mlx_put_pixel(img, x, beginY, colour);
		beginY++;
	}	
}


// typedef struct s_ray_casting
// {
// 	//Player position
// 	double  posX;
// 	double  posY;
// 	//Make sure the camera plane is perpendicular to the direction, but you can change the length of it.
// 	//Direciton
// 	double  dirX;
// 	double  dirY;
//   //Plane
// 	double  planeX;
// 	double  planeY;
//   //the time difference between these two -> how much you should move when a certain key is pressed
//   //and for the FPS counter.
// 	double  time;
// 	double  old_time;
// 	//the x-coordinate on the camera plane that the current x-coordinate of the screen represents,
// 	//done this way so that the right side of the screen will get coordinate 1,
// 	//the center of the screen gets coordinate 0, and the left side of the screen gets coordinate -1. 
// 	double  cameraX;
// 	//Ray direction
// 	double  rayDirX;
// 	double  rayDirY;
// 	//mapX and mapY represent the current square of the map the ray is in.
// 	int     mapX;
// 	int     mapY;
// 	//side_dist_X and side_dist_Y are initially the distance the ray has to travel from its start position
// 	//to the first x-side and the first y-side. They will be incremented while steps are taken.
// 	double side_dist_X;
// 	double side_dist_Y;
// 	//delta_dist_X and delta_dist_Y are the distance the ray has to travel to go from 1 x-side to the next x-side,
// 	//or from 1 y-side to the next y-side.
// 	double delta_dist_X;
// 	double delta_dist_Y;
// 	//used later to calculate the length of the ray
// 	double perp_wall_dist;
// 	//used to determinate whether or not the coming loop may be ended
// 	bool  hit;
// 	int  side; //0 for x-side, 1 for y-side
// 	//direction indicaiton
// 	int	stepX;
// 	int stepY;
// 	long long int colour;
// 	int line_height;
// 	int draw_start;
// 	int draw_end;
// 	//for the loop, idk yet
// 	bool confused;
// } t_ray_casting;

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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

///INITIALISATIONS
void ray_init(t_ray_casting *data, int i)
{
	data->cameraX = 2 * i / (double)screenWidth - 1;
	data->rayDirX = data->dirX + data->planeX * data->cameraX;
	data->rayDirY = data->dirY + data->planeY * data->cameraX;
	data->mapX = (int)(data->posX);
	data->mapY = (int)(data->posY);
	if(data->rayDirX == 0)
		data->delta_dist_X = 1e30;//very big number to avoid division by 0
	else
		data->delta_dist_X = fabs(1 / data->rayDirX); //it was the fabs that was missing for me
	if (data->rayDirY == 0)
		data->delta_dist_Y = 1e30;
	else
		data->delta_dist_Y = fabs(1/ data->rayDirY);
	data->hit = false;
}

//calculate step and initial sideDist
void calculate_step(t_ray_casting *data)
{
	if (data->rayDirX < 0)
	{
		data->stepX = -1;
		data->side_dist_X = (data->posX - data->mapX) * data->delta_dist_X;
	}
	else
	{
		data->stepX = 1;
		data->side_dist_X = (data->mapX + 1.0 - data->posX) * data->delta_dist_X;
	}
	if (data->rayDirY < 0)
	{
		data->stepY = -1;
		data->side_dist_Y = (data->posY - data->mapY) * data->delta_dist_Y;
	}
	else
	{
		data->stepY = 1;
		data->side_dist_Y = (data->mapY + 1.0 - data->posY) * data->delta_dist_Y;
	}
}

////DDA
void check_if_hit(t_ray_casting *data)
{
	while(data->hit == false)
	{
		if (data->side_dist_X < data->side_dist_Y)
		{
			data->side_dist_X += data->delta_dist_X;
			data->mapX += data->stepX;
			data->side = 0;
		}
		else
		{
			data->side_dist_Y += data->delta_dist_Y;
			data->mapY += data->stepY;
			data->side = 1;
		}
		if (worldMap[data->mapX][data->mapY] == 1) //char in our case, not int
			data->hit = true; // or just break
	}
}

//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
void calculate_ray_len(t_ray_casting *data)
{
	if (data->side == 0)
		data->perp_wall_dist = data->side_dist_X - data->delta_dist_X;
	else
		data->perp_wall_dist = data->side_dist_Y - data->delta_dist_Y;
}

//Calculate height of line to draw on screen
void get_line_start_end_points(t_ray_casting *data)
{
	data->line_height = (int)(screenHeight / data->perp_wall_dist); //maybe no int
	data->draw_start = -(data->line_height) / 2 + screenHeight / 2;
	if (data->draw_start < 0)
		data->draw_start = 0;
	data->draw_end = data->line_height / 2 + screenHeight / 2;
	if (data->draw_end >= screenHeight)
		data->draw_end = screenHeight - 1;
}

void cast_rays(t_ray_casting* data, t_mlx* mlx_info)
{
	for(int x = 0; x < screenWidth; x++)
	{	
		ray_init(data, x);
		calculate_step(data);
		check_if_hit(data);
		calculate_ray_len(data);
		get_line_start_end_points(data);
		draw_line(mlx_info->img_arr[ALL], x, data->draw_start, data->draw_end, 0xFF0000FF);
		// draw_line(mlx_info->img_arr[ALL], 2, 100, 200, 0xFF0000FF);
	}
	mlx_image_to_window(mlx_info->mlx, mlx_info->img_arr[ALL], 0, 0);
}
int main(int argc, char *argv[])
{
	t_ray_casting data;
	t_mlx mlx_info;
	data.colour = 0xFF0000FF;//RED
	init_data_for_ray_cast(&data);
	mlx_info.mlx = mlx_init( screenWidth,screenHeight, "Cat shooter", 1);

	mlx_info.img_arr[ALL] = mlx_new_image(mlx_info.mlx, screenWidth, screenHeight);
	// draw_line(mlx_info.img_arr[PLAYER], 40, 20, 200, 0xFF00FFFF);
	cast_rays(&data, &mlx_info);
	mlx_loop_hook(mlx_info.mlx, &movement_hook, (void*)&mlx_info);
	mlx_loop(mlx_info.mlx);
}