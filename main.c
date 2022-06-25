/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:14:43 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/06/26 01:38:15 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "MLX42/include/MLX42/MLX42.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.1415926535
#define IMG_SIDE 80
#define ROWS 12
#define THICKNESS 5
#define LENGTH 70
#define COLS 6
#define WINDOW_WIDTH ((ROWS * IMG_SIDE) + ROWS - 1)
#define WINDOW_HEIGHT ((COLS * IMG_SIDE) + COLS - 1)
#define ROTATION_SPEED (PI / 90)
#define MOVEMENT_SPEED (2)

typedef struct mlx_and_image
{
  mlx_t *mlx;
  mlx_image_t *bg;
  mlx_image_t *player;
  mlx_image_t *dicky;
    
} mai_t;
int draw_line(mai_t *yes, int beginX, int beginY, int endX, int endY, int color);

void draw_grid(mai_t *yes)
{
  yes->bg = mlx_new_image(yes->mlx, IMG_SIDE, IMG_SIDE);
  memset(yes->bg->pixels, 255, IMG_SIDE * IMG_SIDE * sizeof(int));
  for(int i = 0; i < yes->mlx->height; i += IMG_SIDE + 1)
    for(int j = 0; j < yes->mlx->width; j += IMG_SIDE + 1)
      mlx_image_to_window(yes->mlx, yes->bg, j, i);
}

void draw_player(mai_t *yes)
{
  //Player square
  
  memset(yes->bg->pixels, 99, IMG_SIDE * IMG_SIDE * sizeof(int));
  mlx_image_to_window(yes->mlx, yes->bg, 0, 0);
  yes->bg->instances->dir = 0.0f;
  
  
  //Player dicky
  
  draw_line(
	  		yes,
  			yes->bg->instances->x + IMG_SIDE / 2,
  			yes->bg->instances->y + IMG_SIDE / 2,
			yes->bg->instances->x + IMG_SIDE / 2 + cos(yes->bg->instances->dir) * 75,
			yes->bg->instances->y + IMG_SIDE / 2 + sin(yes->bg->instances->dir) * 75,
			0xFFFFFF
			);
}


void movement_hook(void *x)
{
  mai_t *yes;
  
  yes = x;
  if (mlx_is_key_down(yes->mlx, MLX_KEY_ESCAPE))
    mlx_close_window(yes->mlx);
  if (mlx_is_key_down(yes->mlx, MLX_KEY_W))
  {
	yes->bg->instances->x += cos(yes->bg->instances->dir) * MOVEMENT_SPEED;
	yes->bg->instances->y += sin(yes->bg->instances->dir) * MOVEMENT_SPEED;
  }
  if (mlx_is_key_down(yes->mlx, MLX_KEY_S))
  {
	yes->bg->instances->x -= cos(yes->bg->instances->dir) * MOVEMENT_SPEED;
	yes->bg->instances->y -= sin(yes->bg->instances->dir) * MOVEMENT_SPEED;
  }
  if (mlx_is_key_down(yes->mlx, MLX_KEY_A))
  {
	double temp_dir;
	temp_dir = PI / 2 + yes->bg->instances->dir; 
	if (temp_dir >= 2 * PI)
		temp_dir -= 2 * PI;
	yes->bg->instances->x += cos(temp_dir) * MOVEMENT_SPEED;
	yes->bg->instances->y += sin(temp_dir) * MOVEMENT_SPEED;
  }

  if (mlx_is_key_down(yes->mlx, MLX_KEY_D))
  {
	double temp_dir;
	temp_dir = yes->bg->instances->dir - PI / 2; 
	if (temp_dir <= 0)
		temp_dir += 2 * PI;
	yes->bg->instances->x += cos(temp_dir) * MOVEMENT_SPEED;
	yes->bg->instances->y += sin(temp_dir) * MOVEMENT_SPEED;
    
  }
  if (mlx_is_key_down(yes->mlx, MLX_KEY_RIGHT))
  {
    yes->bg->instances->dir -= ROTATION_SPEED;
    if (yes->bg->instances->dir <= 0)
        yes->bg->instances->dir += 2 * PI;

  }
  if (mlx_is_key_down(yes->mlx, MLX_KEY_LEFT))
  {
    printf("Left key\n ");
    yes->bg->instances->dir += ROTATION_SPEED;
    if (yes->bg->instances->dir >= 2 * PI) ///do I need the =
      yes->bg->instances->dir -= 2 * PI;
  }
//   draw_line(
// 	  		yes,
//   			yes->bg->instances->x + IMG_SIDE / 2,
//   			yes->bg->instances->y + IMG_SIDE / 2,
// 			yes->bg->instances->x + IMG_SIDE / 2 + cos(yes->bg->instances->dir) * 75,
// 			yes->bg->instances->y + IMG_SIDE / 2 + sin(yes->bg->instances->dir) * 75,
// 			0xFFFFFF
// 			);

  printf("Current position: x = %f, y = %f, dir = %f\n", yes->bg->instances->x, yes->bg->instances->y, yes->bg->instances->dir);
  
}

int draw_line(mai_t *yes, int beginX, int beginY, int endX, int endY, int colour)
{
	double	deltaX;
	double	deltaY;
	int 	pixels;
	double 	pixelX;
	double 	pixelY;

  	printf("SMORT %i %i %i %i\n",beginX,  beginY,  endX,  endY);
	deltaX = endX - beginX;
	deltaY = endY - beginY;
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	pixelX = beginX;
	pixelY = beginY;
	deltaX /= pixels;
	deltaY /= pixels;
	while (pixels)
	{
		mlx_put_pixel(yes->bg, pixelX, pixelY, colour);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
	return (0);
}

int main(void)
{
  mai_t yes;
  // yes.pa = 90;
  // yes.pdx = cos(yes.pa)*5;
  // yes.pdy = sin(yes.pa)*5;
  
	yes.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Kurwiszon", true);
  if (!yes.mlx)
		exit(-99);

  
  draw_grid(&yes);
  yes.bg = mlx_new_image(yes.mlx, IMG_SIDE, IMG_SIDE);
  draw_player(&yes);
  
  mlx_loop_hook(yes.mlx, &movement_hook, &yes);
	mlx_loop(yes.mlx);
	return (0);
}


//"wtf why player = bg"
//draw line whaaat?