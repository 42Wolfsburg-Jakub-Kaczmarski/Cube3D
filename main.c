/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:08:38 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/07 22:20:42 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube.h"
void cast_rays(t_mlx *data);

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
			mlx_put_pixel(mlx->img_arr[1], i, j, 0xFFFFFF);
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
			mlx_put_pixel(mlx->img_arr[2], i, j, 0x0000FF);
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
	cast_rays(mlx_info);
	
}

bool check_movement(t_mlx *data)
{
	int x_pos = (data->pdx + data->px) / IMG_SIDE;
	int y_pos = (data->pdy + data->py) / IMG_SIDE;
	if (data->map_s[y_pos][x_pos] == '1')
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


void cast_rays(t_mlx *data)
{
	ft_putstr_fd("here\n", 2);
	int r;
	int mx;
	int my;
	// int mp;
	int dof;

	double rx;
	double ry;
	double r_dir;
	double xo;
	double yo;
	double a_Tan;
	
	// r_dir = data->dir - DR * 30;
	// if (r_dir < 0)
	// 	r_dir += 2 * PI;
	// if (r_dir > 2 * PI)
	// 	r_dir -= 2 * PI;

	r_dir = data->dir;
	r = 0;
	while(r < 1)
	{
		r++;
		dof = 0;
		a_Tan = -1/tan(r_dir);
		if (r_dir > PI) //ray looking down r_dir < PI?? 'y' flipped
		{
			ry = (int)(data->py / IMG_SIDE) * IMG_SIDE;
			rx = (data->px - ry) * a_Tan + data->px;
			yo = -IMG_SIDE;
			xo = -yo * a_Tan;
		}
		if (r_dir < PI)
		{
			ry = (int)(data->py / IMG_SIDE) * IMG_SIDE + IMG_SIDE;
			rx = (data->px - ry) * a_Tan + data->px;
			yo = IMG_SIDE;
			xo = -yo * a_Tan;
		}
		if (r_dir == 0 || r_dir == PI)
		{
			rx = data->px;
			ry = data->py;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx / IMG_SIDE);
			my = (int)(ry / IMG_SIDE);
			if (mx > 0 &&
				mx < data->map_width &&
				my > 0 &&
				my < data->map_height &&
				data->map_s[my][mx] == '1')
			{
				dof = 8;
			}
			else
			{
				rx += xo;
				ry += yo;
			}
		}
		data->img_arr[5] = mlx_new_image(data->mlx, data->map_width * IMG_SIDE, data->map_height * IMG_SIDE);
		draw_line(	data->img_arr[5],
					data->px,
					data->py,
					rx,
					ry,
					0xFF0000);
		mlx_image_to_window(data->mlx, data->img_arr[5], 0, 0);
		
	}
	
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