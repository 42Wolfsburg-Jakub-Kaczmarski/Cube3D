/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:08:38 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/06/29 22:07:49 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube.h"

bool	epsilon_function(double target, double patient, double offset)
{
	if (patient < target + offset && patient > target - offset)
		return (true);
	return (false);
}

void fix_rounding_errors(double *ra)
{
	if (epsilon_function(0, *ra, rotationfix) || epsilon_function(2 * PI, *ra, rotationfix))
		*ra = 0;
	else if (epsilon_function(PI, *ra, rotationfix))
		*ra = PI;
	if (epsilon_function(SOUTH, *ra, rotationfix))
		*ra = SOUTH;
	else if (epsilon_function(NORTH, *ra, rotationfix))
		*ra = NORTH;
}

int draw_rays(t_mlx *mlx_info)
{
	int r;
	int dof;
	int mx;
	int my;
	double ra;
	double rx;
	double ry;
	double yo;
	double xo;
	// ra = mlx_info->dir;
	ra = mlx_info->dir - DR * 30;
	if (ra < 0)
	{
		ra += 2 * PI;
	}
	if (ra > 2 * PI)
	{
		ra -= 2 * PI;
	}
	// printf("%f\n", ra);
	fix_rounding_errors(&ra);
	printf("%f\n", ra);
	for (r = 0;r < 1; r++)
	{
		dof = 0;
		double aTan = -1/tan(ra);
		if (ra > PI)
		{
			ry = (int)(mlx_info->py/IMG_SIDE) * IMG_SIDE - 0.0001;
			rx = (mlx_info->py - ry) * aTan + mlx_info->px;
			yo = -IMG_SIDE;
			xo = -yo * aTan;
		}
		if (ra < PI)
		{
			ry = (int)(mlx_info->py/IMG_SIDE) * IMG_SIDE + IMG_SIDE;
			rx = (mlx_info->py - ry) * aTan + mlx_info->px;
			yo = IMG_SIDE;
			xo = -yo * aTan;
		}
		
		// if (ra == 0 || ra == PI)
		if (ra == 0 || ra == PI)
		{
			rx = mlx_info->px;
			ry = mlx_info->py;
			dof = 8;
		}
		while(dof < 8)
		{
			mx = (int)(rx / IMG_SIDE);
			my = (int)(ry / IMG_SIDE);
			
			if (mx > 0 && my > 0 && mx < mlx_info->map_width && my < mlx_info->map_height && mlx_info->map[my][mx] == '1')
				dof = 8;
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		mlx_delete_image(mlx_info->mlx, mlx_info->img_arr[6]);
		mlx_info->img_arr[6] = mlx_new_image(mlx_info->mlx, mlx_info->map_width * IMG_SIDE, mlx_info->map_height * IMG_SIDE);
		// if (rx > mlx_info->map_width * IMG_SIDE)
		// 	rx = mlx_info->map_width * IMG_SIDE - 1;
		// if (ry > mlx_info->map_height * IMG_SIDE)
		// 	ry = mlx_info->map_height * IMG_SIDE - 1;
		draw_line(mlx_info->img_arr[6], mlx_info->px + PLAYER_SIZE / 2, mlx_info->py + PLAYER_SIZE / 2, rx, ry, 0x00FF00FF);
		mlx_image_to_window(mlx_info->mlx, mlx_info->img_arr[6], 0, 0);


		// ////////////////VERTICAL
		dof = 0;
		double nTan = -tan(ra);
		if (ra > SOUTH && ra < NORTH)
		{
			rx = (int)(mlx_info->py/IMG_SIDE) * IMG_SIDE - 0.0001;
			ry = (mlx_info->px - rx) * nTan + mlx_info->py;
			xo = -IMG_SIDE;
			yo = -xo * nTan;
		}
		if (ra < SOUTH || ra > NORTH)
		{
			rx = (int)(mlx_info->px/IMG_SIDE) * IMG_SIDE + IMG_SIDE;
			ry = (mlx_info->px - rx) * nTan + mlx_info->py;
			xo = IMG_SIDE;
			yo = -xo * nTan;
		}
		if (ra == 0 || ra == PI)
		{
			rx = mlx_info->px;
			ry = mlx_info->py;
			dof = 8;
		}
		while(dof < 8)
		{
			mx = (int)(rx / IMG_SIDE);
			my = (int)(ry / IMG_SIDE);
			if (mx > 0 && my > 0 && mx < mlx_info->map_width && my < mlx_info->map_height && mlx_info->map[my][mx] == '1')
				dof = 8;
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		mlx_delete_image(mlx_info->mlx, mlx_info->img_arr[5]);
		mlx_info->img_arr[5] = mlx_new_image(mlx_info->mlx, mlx_info->map_width * IMG_SIDE, mlx_info->map_height * IMG_SIDE);
		// if (rx > mlx_info->map_width * IMG_SIDE)
		// 	rx = mlx_info->map_width * IMG_SIDE - 1;
		// if (ry > mlx_info->map_height * IMG_SIDE)
		// 	ry = mlx_info->map_height * IMG_SIDE - 1;
		draw_line(mlx_info->img_arr[5], mlx_info->px + PLAYER_SIZE / 2, mlx_info->py + PLAYER_SIZE / 2, rx, ry, 0xFF0000FF);
		mlx_image_to_window(mlx_info->mlx, mlx_info->img_arr[5], 0, 0);
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
	perror("INIT MLX THINGY");
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
	draw_rays(data);
	
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

/////SET Z later = ask Djaisin how