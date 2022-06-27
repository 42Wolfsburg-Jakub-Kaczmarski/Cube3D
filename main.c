/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:14:43 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/06/27 20:17:37 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "MLX42/include/MLX42/MLX42.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.1415926535
#define IMG_HEIGHT 80
#define IMG_WIDTH 80
#define ROWS 12
#define THICKNESS 15
#define LENGTH 80
#define COLS 6
#define WINDOW_WIDTH ((ROWS * IMG_WIDTH) + ROWS - 1)
#define WINDOW_HEIGHT ((COLS * IMG_HEIGHT) + COLS - 1)
#define ROTATION_SPEED (PI / 90)
#define MOVEMENT_SPEED (2)
#define NORTH 3.0/2 * PI
#define SOUTH 1/2.0 * PI
#define WEST PI
#define EAST 0.0f

int x = 100;
int y = 100;
typedef struct mlx_and_image
{
  mlx_t *mlx;
  mlx_image_t *bg;
  mlx_image_t *player;
  mlx_image_t *dicky;
  double dir;
    
} mai_t;
int worldMap[9][9]=
{
  {1,1,1,1,1,1,1,1,1},
  {1,0,0,0,1,0,0,0,1},
  {1,0,0,0,1,0,0,0,1},
  {1,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,1},
  {1,0,0,0,1,0,0,0,1},
  {1,1,1,1,1,1,1,1,1}
};




void load_textures(mai_t *mlx)
{
  if(mlx){}
  //Empty space
  mlx->img_arr[1] = mlx_new_image(mlx->mlx, IMG_SIDE, IMG_SIDE);
  int i = 0;
  int j = 0;
  while(i < IMG_SIDE)
  {
    j = 0;
    while(j < IMG_SIDE)
    {
      mlx_put_pixel(mlx->img_arr[1], i, j, 0x0000FF);
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
      mlx_put_pixel(mlx->img_arr[2], i, j, 0xFFFFFF);
      j++;
    }
    i++;
  }
  //Load_colors for now
}


int draw_line(mlx_image_t *img,  int beginX, int beginY, int endX, int endY, int colour);

void draw_grid(mai_t *yes)
{
  yes->bg = mlx_new_image(yes->mlx, IMG_WIDTH, IMG_HEIGHT);
  memset(yes->bg->pixels, 255, IMG_WIDTH * IMG_HEIGHT * sizeof(int));
  for(int i = 0; i < yes->mlx->height; i += IMG_WIDTH + 1)
    for(int j = 0; j < yes->mlx->width; j += IMG_HEIGHT + 1)
      mlx_image_to_window(yes->mlx, yes->bg, j, i);
}

void draw_player(mai_t *mlx_info)
{
	yes->player = mlx_new_image(yes->mlx, IMG_WIDTH, IMG_HEIGHT);
	memset(yes->player->pixels, 99, IMG_WIDTH * IMG_HEIGHT * sizeof(int));
	mlx_image_to_window(yes->mlx, yes->player, 0, 0);
	yes->player->instances->dir = EAST;
	// yes->dicky = mlx_new_image(yes->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void draw_dicky(mai_t *yes)
{
	mlx_delete_image(yes->mlx, yes->dicky);
	yes->dicky = mlx_new_image(yes->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	draw_line(
			yes->dicky,
			IMG_WIDTH / 2 + yes->player->instances->x,
			IMG_HEIGHT / 2 + yes->player->instances->y,
			(IMG_WIDTH / 2 + yes->player->instances->x) + cos(yes->player->instances->dir) * IMG_WIDTH / 2 , 
			(IMG_HEIGHT / 2 + yes->player->instances->y) + sin(yes->player->instances->dir) * IMG_WIDTH / 2 ,
			0xFFFFFF
			);
	mlx_image_to_window(yes->mlx, yes->dicky, 0, 0);
}

void key_w(mai_t *data)
{
	data->player->instances->x += cos(data->player->instances->dir) * MOVEMENT_SPEED;
	data->player->instances->y += sin(data->player->instances->dir) * MOVEMENT_SPEED;
	data->dicky->instances->x += cos(data->player->instances->dir) * MOVEMENT_SPEED;
	data->dicky->instances->y += sin(data->player->instances->dir) * MOVEMENT_SPEED;
}

void key_s(mai_t *data)
{
	data->player->instances->x -= cos(data->player->instances->dir) * MOVEMENT_SPEED;
	data->player->instances->y -= sin(data->player->instances->dir) * MOVEMENT_SPEED;
	data->dicky->instances->x -= cos(data->player->instances->dir) * MOVEMENT_SPEED;
	data->dicky->instances->y -= sin(data->player->instances->dir) * MOVEMENT_SPEED;
}

void key_a(mai_t *data)
{
	double temp_dir;
	temp_dir = data->player->instances->dir - (PI / 2); 
	if (temp_dir >= 2 * PI)
		temp_dir -= 2 * PI;
	data->player->instances->x += cos(temp_dir) * MOVEMENT_SPEED;
	data->player->instances->y += sin(temp_dir) * MOVEMENT_SPEED;
	data->dicky->instances->x += cos(temp_dir) * MOVEMENT_SPEED;
	data->dicky->instances->y += sin(temp_dir) * MOVEMENT_SPEED;
}

void key_d(mai_t *data)
{
	double temp_dir;
	temp_dir = PI / 2 + data->player->instances->dir; 
	if (temp_dir <= 0)
		temp_dir += 2 * PI;
	data->player->instances->x += cos(temp_dir) * MOVEMENT_SPEED;
	data->player->instances->y += sin(temp_dir) * MOVEMENT_SPEED;
	data->dicky->instances->x += cos(temp_dir) * MOVEMENT_SPEED;
	data->dicky->instances->y += sin(temp_dir) * MOVEMENT_SPEED;
}

void key_left_arrow(mai_t *data)
{
	data->player->instances->dir += ROTATION_SPEED;
    if (data->player->instances->dir >= 2 * PI)
      data->player->instances->dir -= 2 * PI;
	draw_dicky(data);
}

void key_right_arrow(mai_t *data)
{
	data->player->instances->dir -= ROTATION_SPEED;
    if (data->player->instances->dir <= 0)
        data->player->instances->dir += 2 * PI;
	draw_dicky(data);
}

void movement_hook(void *x)
{
  mai_t *data;
  
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
}

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

int main(void)
{
	mai_t yes;
	
	yes.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Kurwiszon", true);
	if (!yes.mlx)
		exit(-99);

	draw_grid(&yes);
	draw_player(&yes);
	draw_dicky(&yes);
	mlx_loop_hook(yes.mlx, &movement_hook, &yes);
	mlx_loop(yes.mlx);
	return (0);
}