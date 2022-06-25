/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:14:43 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/06/25 13:46:16 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "MLX42/include/MLX42/MLX42.h"

int worldMap[24][24]=
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


// void	hook(void *param)
// {
// 	mlx_t	*mlx;

// 	mlx = param;
// 	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
// 		mlx_close_window(param);
// 	if (mlx_is_key_down(param, MLX_KEY_UP))
// 		img->instances[0].y -= 5;
// 	if (mlx_is_key_down(param, MLX_KEY_DOWN))
// 		img->instances[0].y += 5;
// 	if (mlx_is_key_down(param, MLX_KEY_LEFT))
// 		img->instances[0].x -= 5;
// 	if (mlx_is_key_down(param, MLX_KEY_RIGHT))
// 		img->instances[0].x += 5;
// }


#include <string.h>
#include <stdlib.h>
#define IMG_SIDE 80
#define ROWS 12
#define COLS 6
#define WINDOW_WIDTH ((ROWS * IMG_SIDE) + ROWS - 1)
#define WINDOW_HEIGHT ((COLS * IMG_SIDE) + COLS - 1)

typedef struct mlx_and_image
{
  mlx_t *mlx;
  mlx_image_t *img;
    
} mai_t;

void draw_grid(mai_t *mlx)
{
  mlx->img = mlx_new_image(mlx->mlx, IMG_SIDE, IMG_SIDE);
  memset(mlx->img->pixels, 255, IMG_SIDE * IMG_SIDE * sizeof(int));
  for(int i = 0; i < mlx->mlx->height; i += IMG_SIDE + 1)
    for(int j = 0; j < mlx->mlx->width; j += IMG_SIDE + 1)
      mlx_image_to_window(mlx->mlx, mlx->img, j, i);
}

void draw_player(mai_t *yes)
{
  yes->img = mlx_new_image(yes->mlx, IMG_SIDE, IMG_SIDE);
  memset(yes->img->pixels, 99, IMG_SIDE * IMG_SIDE * sizeof(int));  
  mlx_image_to_window(yes->mlx, yes->img, 0, 0);
}

void movement_hook(void *x)
{
  mai_t *yes;
  
  yes = x;
  if (mlx_is_key_down(yes->mlx, MLX_KEY_ESCAPE))
    mlx_close_window(yes->mlx);
  if (mlx_is_key_down(yes->mlx, MLX_KEY_UP))
		yes->img->instances->y -= 5;
  if (mlx_is_key_down(yes->mlx, MLX_KEY_DOWN))
		yes->img->instances->y += 5;
  if (mlx_is_key_down(yes->mlx, MLX_KEY_LEFT))
		yes->img->instances->x -= 5;
  if (mlx_is_key_down(yes->mlx, MLX_KEY_RIGHT))
		yes->img->instances->x += 5;
}


int main(void)
{
  mai_t yes;
  
	yes.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Kurwiszon", true);
  if (!yes.mlx)
		exit(-99);
  draw_grid(&yes);
  draw_player(&yes);
  mlx_loop_hook(yes.mlx, &movement_hook, &yes);
	mlx_loop(yes.mlx);
	return (0);
}