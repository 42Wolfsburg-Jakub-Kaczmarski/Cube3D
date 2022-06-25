/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:14:43 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/06/25 15:47:53 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "MLX42/include/MLX42/MLX42.h"
#define WIDTH 1280
#define HEIGHT 768
#define IMG_SIDE 80
#define ROWS 12
#define COLS 6
#define PLAYER_SIZE 20
#include <string.h>
// #include "Cube.h"/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define WINDOW_WIDTH ((ROWS * IMG_SIDE) + ROWS - 1)
#define WINDOW_HEIGHT ((COLS * IMG_SIDE) + COLS - 1)
typedef struct mlx_and_image
{
  mlx_t *mlx;
  //Index 0 reserved for the player
  mlx_image_t **img_arr;
    
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
  //Load_colors for now
}


void draw_grid(mai_t *mlx)
{
  load_textures(mlx);
  //Loop through the map
  int i = 0;
  int j = 0;
  int y = 0;
  int x = 0;;
  while(i < 9)
  {
    j = 0;
    y = 0;
    while(j < 9)
    {
        if(worldMap[i][j] == 1)
          mlx_image_to_window(mlx->mlx ,mlx->img_arr[1],x, y);
        y += IMG_SIDE;
        j++;
    }
    x += IMG_SIDE;
    i++;
  }
}

void draw_player(mai_t *mlx_info)
{
  mlx_info->img_arr[0] = mlx_new_image(mlx_info->mlx, PLAYER_SIZE, PLAYER_SIZE);
  memset(mlx_info->img_arr[0]->pixels, 255, PLAYER_SIZE * PLAYER_SIZE * sizeof(int));  
  mlx_image_to_window(mlx_info->mlx, mlx_info->img_arr[0], 0, 0);
}

void movement_hook(void *x)
{
  mai_t *mlx_info;
  
  mlx_info = x;
  if (mlx_is_key_down(mlx_info->mlx, MLX_KEY_ESCAPE))
    mlx_close_window(mlx_info->mlx);
  if (mlx_is_key_down(mlx_info->mlx, MLX_KEY_UP))
		mlx_info->img_arr[0]->instances->y -= 5;
  if (mlx_is_key_down(mlx_info->mlx, MLX_KEY_DOWN))
		mlx_info->img_arr[0]->instances->y += 5;
  if (mlx_is_key_down(mlx_info->mlx, MLX_KEY_LEFT))
		mlx_info->img_arr[0]->instances->x -= 5;
  if (mlx_is_key_down(mlx_info->mlx, MLX_KEY_RIGHT))
		mlx_info->img_arr[0]->instances->x += 5;
}

int	main(void)
{
  //Before rendering get the map dimensions
  int x = 9;
  int y = 9;
  int texture_ammout = 5;
  mai_t mlx_info;
	mlx_info.mlx = mlx_init(x * IMG_SIDE, y * IMG_SIDE, "Kurwiszon", true);
  if (!mlx_info.mlx)
		exit(-99);
  mlx_info.img_arr = calloc(texture_ammout ,sizeof(mlx_image_t));
  draw_grid(&mlx_info);
  draw_player(&mlx_info);
  mlx_loop_hook(mlx_info.mlx, &movement_hook, &mlx_info);
	mlx_loop(mlx_info.mlx);
	return (0);
}