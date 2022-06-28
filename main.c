/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:08:38 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/06/28 21:05:30 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube.h"

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
void draw_wand(t_mlx *mlx_info)
{
	mlx_delete_image(mlx_info->mlx, mlx_info->img_arr[WAND]);
	mlx_info->img_arr[WAND] = mlx_new_image(mlx_info->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	draw_line(
			mlx_info->img_arr[WAND],
			(IMG_SIDE / 2 + mlx_info->px),
			(IMG_SIDE / 2 + mlx_info->py),
			(IMG_SIDE / 2 + mlx_info->px) + cos(mlx_info->dir) * IMG_SIDE / 2 , 
			(IMG_SIDE / 2 + mlx_info->py) + sin(mlx_info->dir) * IMG_SIDE / 2 ,
			0xFFFFFF
			);
	mlx_image_to_window(mlx_info->mlx, mlx_info->img_arr[WAND], 0, 0);
	// mlx_image_to_window(mlx_info->mlx, mlx_info->img_arr[WAND], 20, 20);
}

void draw_grid(t_mlx *mlx)
{
	load_textures(mlx);
	//Loop through the map
	int i = 0;
	int j = 0;
	int y = 0;
	int x = 0;;
	while(i < mlx->map_height )
	{
		j = 0;
		y = 0;
		while(j < mlx->map_width)
		{
				if(mlx->map[i][j] == '1')
					mlx_image_to_window(mlx->mlx ,mlx->img_arr[1],x, y);
				else if(mlx->map[i][j] == '0' || mlx->map[i][j] == 'P')
					mlx_image_to_window(mlx->mlx, mlx->img_arr[2], x, y);
				y += IMG_SIDE + 1;
				j++;
		}
		x += IMG_SIDE + 1;
		i++;
	}
}

void draw_player(t_mlx *mlx_info)
{
	mlx_info->img_arr[PLAYER] = mlx_new_image(mlx_info->mlx, IMG_SIDE, IMG_SIDE);
	memset(mlx_info->img_arr[PLAYER]->pixels, 99, IMG_SIDE * IMG_SIDE * sizeof(int));
	mlx_image_to_window(mlx_info->mlx, mlx_info->img_arr[PLAYER], mlx_info->px, mlx_info->py);
	mlx_info->dir = EAST;
	draw_wand(mlx_info);
}
void    init_mlx_thingy(t_mlx *mlx_info)
{
    mlx_info->mlx = mlx_init((mlx_info->map_width - 1)* 80, (mlx_info->map_height - 1) * 80, "Cat shooter", 1);
    mlx_info->img_arr = ft_calloc(6,sizeof(mlx_image_t));
    draw_grid(mlx_info);
	draw_player(mlx_info);
}
void key_w(t_mlx *data)
{
	printf("X : %d", data->img_arr[PLAYER]->instances->x  );
	printf("Y : %d", data->img_arr[PLAYER]->instances->y  );
	data->px += (double)cos(data->dir) * MOVEMENT_SPEED;
	data->py += (double)sin(data->dir) * MOVEMENT_SPEED;
	data->wx += (double)cos(data->dir) * MOVEMENT_SPEED;
	data->wy += (double)sin(data->dir) * MOVEMENT_SPEED;
	mlx_delete_image(data->mlx, data->img_arr[PLAYER]);
	draw_player(data);
}

void key_s(t_mlx *data)
{
	data->px -= (double)cos(data->dir) * MOVEMENT_SPEED;
	data->py -= (double)sin(data->dir) * MOVEMENT_SPEED;
	data->wx -= (double)cos(data->dir) * MOVEMENT_SPEED;
	data->wy -= (double)sin(data->dir) * MOVEMENT_SPEED;
	printf("X : %f", 	data->px  );
	printf("Y : %f", 	data->py  );
	mlx_delete_image(data->mlx, data->img_arr[PLAYER]);
	// data->img_arr[PLAYER] = calloc(sizeof(mlx_image_t), 1);
	draw_player(data);
}

void key_a(t_mlx *data)
{
	double temp_dir;
	temp_dir = data->dir - (PI / 2); 
	if (temp_dir >= 2 * PI)
		temp_dir -= 2 * PI;
	data->px += cos(temp_dir) * MOVEMENT_SPEED;
	data->py += sin(temp_dir) * MOVEMENT_SPEED;
	data->wx += cos(temp_dir) * MOVEMENT_SPEED;
	data->wy += sin(temp_dir) * MOVEMENT_SPEED;
	mlx_delete_image(data->mlx, data->img_arr[PLAYER]);
	draw_player(data);
}

void key_d(t_mlx *data)
{
	double temp_dir;
	temp_dir = PI / 2 + data->dir; 
	if (temp_dir <= 0)
		temp_dir += 2 * PI;
	data->px += cos(temp_dir) * MOVEMENT_SPEED;
	data->py += sin(temp_dir) * MOVEMENT_SPEED;
	data->wx += cos(temp_dir) * MOVEMENT_SPEED;
	data->wy += sin(temp_dir) * MOVEMENT_SPEED;
	mlx_delete_image(data->mlx, data->img_arr[PLAYER]);
	draw_player(data);
}

void key_left_arrow(t_mlx *data)
{
	data->dir += ROTATION_SPEED;
    if (data->dir >= 2 * PI)
      data->dir -= 2 * PI;
	// ft_putnbr_fd(data->dir, 2);
	draw_wand(data);
}

void key_right_arrow(t_mlx *data)
{
	data->dir -= ROTATION_SPEED;
    if (data->dir <= 0)
        data->dir += 2 * PI;
	draw_wand(data);
}

void  movement_hook(void *x)
{
  t_mlx *data;
  
  data = x;

  if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	mlx_close_window(data->mlx);
  if (mlx_is_key_down(data->mlx, MLX_KEY_W))
  {
	key_w(data);
  }
  if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	key_s(data);
  if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	key_a(data);
  if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	key_d(data);
  if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	key_right_arrow(data);
//   if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
// 	key_left_arrow(data);  
}
int main(int argc, char **argv)
{
    t_mlx   mlx_info;

    if(argc != 2 || !check_map(argv, &mlx_info))
    {
        printf("Error\n");
        return (0);
    }
    mlx_info.px = 0;
    mlx_info.py = 0;
	mlx_info.wx = 0;
	mlx_info.wy = 0;
    init_mlx_thingy(&mlx_info);
	mlx_info.dir = PI;
	mlx_loop_hook(mlx_info.mlx, &movement_hook, (void*)&mlx_info);
	mlx_loop(mlx_info.mlx);
}