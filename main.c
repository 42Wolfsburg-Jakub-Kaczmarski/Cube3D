/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:08:38 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/06/29 20:17:13 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube.h"


int draw_rays(t_mlx *mlx_info)
{
	int r;
	int dof;
	int mx;
	int my;
	// int mp;
	float ra;
	float rx;
	float ry;
	float yo;
	float xo;
	
	perror("DRAW RAYS BEFORE FOR");
	ra = mlx_info->dir;
	ra = mlx_info->dir - DR * 30;
	if (ra < 0)
	{
		ra += 2 * PI;
	}
	if (ra > 2 * PI)
	{
		ra -= 2 * PI;
	}
	for (r = 0;r < 1; r++)
	{
		dof = 0;
		float aTan = -1/tan(ra);
		printf("aTan: %f\n", aTan);
		if (ra > PI)
		{
			ry = (int)(mlx_info->py/IMG_SIDE) * IMG_SIDE - 0.0001;
			printf("ra > PI rx: %f ry %f\n", rx, ry);
			rx = (mlx_info->py - ry) * aTan + mlx_info->px;
			yo = -IMG_SIDE;
			xo = -yo * aTan;
		}
		// perror("AFTER FIRST IF");
		if (ra < PI)
		{
			printf("ra < PI rx: %f ry %f\n", rx, ry);
			ry = (int)(mlx_info->py/IMG_SIDE) * IMG_SIDE + IMG_SIDE;
			rx = (mlx_info->py - ry) * aTan + mlx_info->px;
			yo = IMG_SIDE;
			xo = -yo * aTan;
		}
		// perror("AFTER SECOND IF");
		printf("ra: %f\n", ra);
		if (ra == 0 || ra == PI)
		{
			rx = mlx_info->px;
			ry = mlx_info->py;
			dof = 8;
		}
		// perror("BEFORE WHILE");
		printf("dof*************************: %d\n", dof);
		while(dof < 8)
		{
			mx = (int)(rx / IMG_SIDE);
			my = (int)(ry / IMG_SIDE);
			
			// printf("posX: %f posY %f\n", mlx_info->px, mlx_info->py);
			printf("rx: %f ry %f\n", rx, ry);
			// printf("xo: %f yo %f\n", xo, yo);
			// printf("idxX: %d idxY %d\n", mx, my);
			// printf("___________________\n");
			// perror("BEFORE IF CHECK");
			if (mx > 0 && my > 0 && mx < mlx_info->map_width && my < mlx_info->map_height && mlx_info->map[my][mx] == '1')
			{
				//// a few more checks
				printf("In here?????\n");
				dof = 8;
				// break ;
			}
			else
			{
				rx += xo;
				ry += yo;
				printf("xo: %f yo %f\n", xo, yo);
				dof += 1;
			}
		}
		perror("HERE");
		mlx_delete_image(mlx_info->mlx, mlx_info->img_arr[5]);
		mlx_info->img_arr[5] = mlx_new_image(mlx_info->mlx, mlx_info->map_width * IMG_SIDE, mlx_info->map_height * IMG_SIDE);
		printf("BEFORE DRAW LINE rx: %f ry %f\n", rx, ry);
		draw_line(mlx_info->img_arr[5], mlx_info->px + PLAYER_SIZE / 2, mlx_info->py + PLAYER_SIZE / 2, rx, ry, 0xFF0000FF);
		mlx_image_to_window(mlx_info->mlx, mlx_info->img_arr[5], 0, 0);
		perror("AND HERE?");
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