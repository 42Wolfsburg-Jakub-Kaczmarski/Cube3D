/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:08:38 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/06/29 15:01:29 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube.h"


int draw_rays(t_mlx *mlx_info)
{
	int i = 0;
	int dof = 0;
	int mx;
	int my;
	int mp;
	float ra;
	float rx;
	float ry;
	float yo;
	float xo;
	ra = mlx_info->pa;
	while(i < 1)
	{
		dof = 0;
		float a_tan = -1/tan(ra);
		if(ra>PI)
		{
			ry = (((int)mlx_info->py >> 6) << 6) - 0.0001;
			rx = (mlx_info->py - ry) * a_tan + mlx_info->px;
			yo = -64;
			xo = -yo * a_tan;
		}
		if(ra<PI)
		{
			ry = (((int)mlx_info->py >> 6) << 6) + 64;
			rx = (mlx_info->py - ry) * a_tan + mlx_info->px;
			yo = 64;
			xo = -yo * a_tan;
		}
		if(ra == 0 || ra == PI)
		{
			rx = mlx_info->px;
			ry = mlx_info->py;
			dof = 8;
		}
		while(dof < 8)
		{
			mx = (int) (rx) >> 6;
			my = (int) (ry) >> 6;
			mp = my * mlx_info->map_height + mx;
			if( mlx_info->map[mlx_info->map_height][mlx_info->map_width] == '1')
			{
				dof = 8;
			}else{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		printf("RX value %f\n", rx);
		draw_line(mlx_info->img_arr[WAND],mlx_info->px, mlx_info->py, rx, ry, 255);
		mlx_image_to_window(mlx_info->mlx, mlx_info->img_arr[WAND], 50, 50);
		i++;
	}
	return 0;
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





void    init_mlx_thingy(t_mlx *mlx_info)
{
	mlx_info->px = 100;
    mlx_info->py = 100;
	mlx_info->wx = 0;
	mlx_info->wy = 0;
	mlx_info->dir = SOUTH;
    mlx_info->mlx = mlx_init((mlx_info->map_width - 1 )* IMG_SIDE, (mlx_info->map_height) * IMG_SIDE, "Cat shooter", 1);
    mlx_info->img_arr = ft_calloc(6,sizeof(mlx_image_t));
	draw_grid(mlx_info);
	draw_player(mlx_info);
	draw_rays(mlx_info);
}

bool check_movement(t_mlx *data)
{
	int x_pos = (data->pdx + data->px) / IMG_SIDE;
	int y_pos = (data->pdy + data->py) / IMG_SIDE;
	if (data->map[y_pos][x_pos] == '1')
		return (true);
	return (false);
}

void  movement_hook(void *x)
{
  t_mlx *data;
  
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
	mlx_delete_image(data->mlx, data->img_arr[PLAYER]);
	draw_player(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		key_right_arrow(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		key_left_arrow(data);  
}

int main(int argc, char **argv)
{
    t_mlx   mlx_info;

    if(argc != 2 || check_map(argv, &mlx_info) == 0)
    {
        printf("Error\n");
        return (0);
    }
    
    init_mlx_thingy(&mlx_info);
	mlx_loop_hook(mlx_info.mlx, &movement_hook, (void*)&mlx_info);
	mlx_loop(mlx_info.mlx);
}