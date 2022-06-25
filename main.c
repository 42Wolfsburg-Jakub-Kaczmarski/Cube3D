/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:14:43 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/06/26 00:45:25 by kmilchev         ###   ########.fr       */
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
#define MOVEMENT_SPEED (20)

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
  draw_line(yes, yes->bg->instances->x + IMG_SIDE / 2, yes->bg->instances->x + IMG_SIDE / 2, IMG_SIDE/2, IMG_SIDE + IMG_SIDE/2, 0xFFFFFF);
}


void movement_hook(void *x)
{
  mai_t *yes;
  
  yes = x;
  if (mlx_is_key_down(yes->mlx, MLX_KEY_ESCAPE))
    mlx_close_window(yes->mlx);
  if (mlx_is_key_down(yes->mlx, MLX_KEY_W))
  {
		yes->bg->instances->y -= 5;
		yes->dicky->instances->y -= 5;
  }
  if (mlx_is_key_down(yes->mlx, MLX_KEY_S))
  {
		yes->bg->instances->y += 5;
		yes->dicky->instances->y += 5;
  }
  if (mlx_is_key_down(yes->mlx, MLX_KEY_A))
	{	
    yes->bg->instances->x -= 5;
    yes->dicky->instances->x -= 5;
  }
  if (mlx_is_key_down(yes->mlx, MLX_KEY_D))
  {
		yes->bg->instances->x += 5;
		yes->dicky->instances->x += 5;


    // x += d
    
    
  }
  if (mlx_is_key_down(yes->mlx, MLX_KEY_RIGHT))
  {
    // int x = yes->dicky->instances->x;
    // int y = yes->dicky->instances->y;
    
		// yes->dicky->instances->x = x*cos(PI/180) - y*sin(PI/180);
		// yes->dicky->instances->y = x*sin(PI/180) - y*cos(PI/180);
    yes->bg->instances->dir -= ROTATION_SPEED;
    if (yes->bg->instances->dir <= 0)
        yes->bg->instances->dir += 2 * PI;



  }
  if (mlx_is_key_down(yes->mlx, MLX_KEY_LEFT))
  {
    printf("Left key\n ");
    // yes->bg->instances->dir += 10;
    yes->bg->instances->dir += ROTATION_SPEED;
    if (yes->bg->instances->dir >= 2 * PI) ///do I need the =
      yes->bg->instances->dir -= 2 * PI;
      // if(cehck if not inbetwen zeor and two pi)
      //   change so it is 
  }
  

  printf("Current position: x = %f, y = %f, dir = %f\n", yes->bg->instances->x, yes->bg->instances->y, yes->bg->instances->dir);
  
}

int draw_line(mai_t *yes, int beginX, int beginY, int endX, int endY, int colour)
{
	double	deltaX;
	double	deltaY;
	int 	pixels;
	double 	pixelX;
	double 	pixelY;

  yes->dicky = mlx_new_image(yes->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
  mlx_image_to_window(yes->mlx, yes->dicky, 0, 0);
	deltaX = endX - beginX;
	deltaY = endY - beginY;
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	pixelX = beginX;
	pixelY = beginY;
	deltaX /= pixels;
	deltaY /= pixels;
	while (pixels)
	{
		mlx_put_pixel(yes->dicky, pixelX, pixelY, colour);
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