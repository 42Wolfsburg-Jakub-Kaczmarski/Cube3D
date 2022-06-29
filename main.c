/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:08:38 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/06/29 13:50:16 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube.h"

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

    if(argc != 2 || !check_map(argv, &mlx_info))
    {
        printf("Error\n");
        return (0);
    }
    
    init_mlx_thingy(&mlx_info);
	mlx_loop_hook(mlx_info.mlx, &movement_hook, (void*)&mlx_info);
	mlx_loop(mlx_info.mlx);
}