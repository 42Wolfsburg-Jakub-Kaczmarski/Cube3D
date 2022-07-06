/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 10:42:55 by kmilchev          #+#    #+#             */
/*   Updated: 2022/07/06 22:46:33 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Cube.h"

#define mapWidth 24
#define mapHeight 24


void cast_rays(t_ray_casting* data, t_mlx* mlx_info);
void draw_line(mlx_image_t *img, int x, int beginY, int endY, int colour)
{
	while(beginY < endY)
	{
		mlx_put_pixel(img, x, beginY, colour);
		beginY++;
	}	
}


int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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

void key_w(t_mlx *big_struct)
{
	t_ray_casting *data;

	data = &big_struct->data;
	if (worldMap[(int)(data->posX + data->dirX * MOVEMENT_SPEED)][(int)(data->posY )] == false)
	{
		data->posX += data->dirX * MOVEMENT_SPEED;
	}
	if (worldMap[(int)(data->posX)][(int)(data->posY + data->dirY * MOVEMENT_SPEED)] == false)
	{	
		data->posY += data->dirY * MOVEMENT_SPEED;
	}
}

void key_s(t_mlx *big_struct)
{
	t_ray_casting *data;

	data = &big_struct->data;
	if (worldMap[(int)(data->posX - data->dirX * MOVEMENT_SPEED)][(int)(data->posY)] == false)
	{
		data->posX -= data->dirX * MOVEMENT_SPEED;
	}
	if (worldMap[(int)(data->posX)][(int)(data->posY - data->dirY * MOVEMENT_SPEED)] == false)
	{	
		data->posY -= data->dirY * MOVEMENT_SPEED;
	}
}

void key_d(t_mlx *big_struct)
{
	t_ray_casting *data;

	data = &big_struct->data;
	if (worldMap[(int)(data->posX + data->plane_X * MOVEMENT_SPEED)][(int)(data->posY )] == false)
	{
		data->posX += data->plane_X * MOVEMENT_SPEED;
	}
	if (worldMap[(int)(data->posX)][(int)(data->posY + data->plane_Y * MOVEMENT_SPEED)] == false)
	{	
		data->posY += data->plane_Y * MOVEMENT_SPEED;
	}
}

void key_a(t_mlx *big_struct)
{
	t_ray_casting *data;

	data = &big_struct->data;
	if (worldMap[(int)(data->posX - data->plane_X * MOVEMENT_SPEED)][(int)(data->posY)] == false)
	{
		data->posX -= data->plane_X * MOVEMENT_SPEED;
	}
	if (worldMap[(int)(data->posX)][(int)(data->posY - data->plane_Y * MOVEMENT_SPEED)] == false)
	{	
		data->posY -= data->plane_Y * MOVEMENT_SPEED;
	}
}

void key_left_arrow(t_mlx *big_struct)
{
	t_ray_casting *data;
	double	old_dir_X;
	double old_plane_X;
	
	printf("Position X: %f\n", data->posX);
	printf("Position Y: %f\n", data->posY);
	data = &big_struct->data;
	old_dir_X = data->dirX;
	old_plane_X = data->plane_X;
	data->dirX = data->dirX * cos(ROTATION_SPEED) - data->dirY * sin(ROTATION_SPEED);
	data->dirY = old_dir_X * sin(ROTATION_SPEED) + data->dirY * cos(ROTATION_SPEED);
	data->plane_X = data->plane_X * cos(ROTATION_SPEED) - data->plane_Y * sin(ROTATION_SPEED);
	data->plane_Y = old_plane_X * sin(ROTATION_SPEED) + data->plane_Y * cos(ROTATION_SPEED);
	
}

void key_right_arrow(t_mlx *big_struct)
{
	t_ray_casting *data;
	double	old_dir_X;
	double old_plane_X;
	
	data = &big_struct->data;
	old_dir_X = data->dirX;
	old_plane_X = data->plane_X;
	data->dirX = data->dirX * cos(-ROTATION_SPEED) - data->dirY * sin(-ROTATION_SPEED);
	data->dirY = old_dir_X * sin(-ROTATION_SPEED) + data->dirY * cos(-ROTATION_SPEED);
	data->plane_X = data->plane_X * cos(-ROTATION_SPEED) - data->plane_Y * sin(-ROTATION_SPEED);
	data->plane_Y = old_plane_X * sin(-ROTATION_SPEED) + data->plane_Y * cos(-ROTATION_SPEED);
}

void  movement_hook(void *x)
{
  t_mlx *data;
  
  data = x;
	mlx_delete_image(data->mlx, data->img_arr[ALL]);
	data->img_arr[ALL] = mlx_new_image(data->mlx, screenWidth, screenHeight);
	// mlx_set_instance_depth(data->img_arr[ALL], 900);
	// data->img_arr[ALL]->instances->z
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		key_w(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		key_s(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		key_d(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		key_a(data);
	if(mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		key_left_arrow(data);
	if(mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		key_right_arrow(data);
	
	cast_rays(&data->data, data);
}

void init_data_for_ray_cast(t_ray_casting *data)
{
	data->posX = 22;
	data->posY = 12;
	data->dirX = -1;
	data->dirY = 0;
	data->plane_X = 0;
	data->plane_Y = 0.66;
	data->time = 0;
}



void cast_rays(t_ray_casting* data, t_mlx* mlx_info)
{
	static int i = 0;
	// printf("Take %d\n", i);
	for(int x = 0; x < screenWidth; x++)
	{	
		ray_init(data, x);
		calculate_step(data);
		check_if_hit(data);
		calculate_ray_len(data);
		get_line_start_end_points(data);
		draw_line(mlx_info->img_arr[ALL], x, data->draw_start, data->draw_end, 0xFF0000FF);
		// draw_line(mlx_info->img_arr[ALL], 2, 100, 200, 0xFF0000FF);
		// printf("%d ", x);
	}
	mlx_image_to_window(mlx_info->mlx, mlx_info->img_arr[ALL], 0, 0);
}
int main(int argc, char *argv[])
{
	// t_ray_casting data;
	t_mlx mlx_info;
	mlx_info.data.colour = 0xFF0000FF;//RED
	init_data_for_ray_cast(&mlx_info.data);
	mlx_info.mlx = mlx_init( screenWidth,screenHeight, "Cat shooter", 1);

	mlx_info.img_arr[ALL] = mlx_new_image(mlx_info.mlx, screenWidth, screenHeight);
	cast_rays(&mlx_info.data, &mlx_info);
	mlx_loop_hook(mlx_info.mlx, &movement_hook, (void*)&mlx_info);
	mlx_loop(mlx_info.mlx);
}