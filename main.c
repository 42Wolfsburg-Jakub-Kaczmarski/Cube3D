/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:14:43 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/06/27 23:36:54 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube.h"

// int worldMap[9][9]=
// {
// 	{1,1,1,1,1,1,1,1,1},
// 	{1,0,0,0,1,0,0,0,1},
// 	{1,0,0,0,1,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,1},
// 	{1,0,0,1,1,0,1,0,1},
// 	{1,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,1,0,0,0,1},
// 	{1,1,1,1,1,1,1,1,1}
// };

void load_textures(mai_t *mlx)
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


void draw_grid(mai_t *mlx)
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
void	find_player(mai_t *mlx_info)
{
	int i = 0;
	int j = 0;
	while(mlx_info->map[i][j])
	{
		j = 0;
		while(mlx_info->map[i][j])
		{
			if(mlx_info->map[i][j] == 'P')
			{
				break;
			}
			j++;
		}
		i++;
	}
	mlx_info->img_arr[3] = mlx_new_image(mlx_info->mlx, mlx_info->px, mlx_info->py);
    mlx_image_to_window(mlx_info->mlx, mlx_info->img_arr[3], i * IMG_SIDE, j * IMG_SIDE);
	
}

void draw_player(mai_t *mlx_info, int x, int y)
{
	mlx_info->img_arr[0] = mlx_new_image(mlx_info->mlx, PLAYER_SIZE, PLAYER_SIZE);
	memset(mlx_info->img_arr[0]->pixels, 255, PLAYER_SIZE * PLAYER_SIZE * sizeof(int));  
	mlx_image_to_window(mlx_info->mlx, mlx_info->img_arr[0], ((float)x * IMG_SIDE) / 2, ((float)y * IMG_SIDE) / 2);
	find_player(mlx_info);
    
}

void rotating_player(mai_t  *mlx_info)
{
	if(mlx_is_key_down(mlx_info->mlx, MLX_KEY_W))
	{
        int x = mlx_info->img_arr[3]->instances->x;
        int y = mlx_info->img_arr[3]->instances->y;
        mlx_info->px+=mlx_info->pdx;
        mlx_info->py+=mlx_info->pdy; 
        mlx_info->img_arr[3]->instances->x = x * cos(PI / 180) - y * sin(PI/180);
        mlx_info->img_arr[3]->instances->y = x * sin(PI / 180) - y * cos(PI/180);
	}if(mlx_is_key_down(mlx_info->mlx, MLX_KEY_S))
	{
        mlx_info->px-=mlx_info->pdx;
        mlx_info->py-=mlx_info->pdy;
		//Looking down
	}if(mlx_is_key_down(mlx_info->mlx, MLX_KEY_A))
	{
        mlx_info->pa -= 0.1;
        if(mlx_info->pa < 0)
        {
            mlx_info->pa += 2 * PI;
        }
        mlx_info->pdx = cos(mlx_info->pa) * 5;
        mlx_info->pdy = sin(mlx_info->pa) * 5;
		//rotating left
	}
	if(mlx_is_key_down(mlx_info->mlx, MLX_KEY_D))
	{
        mlx_info->pa += 0.1;
        if(mlx_info->pa < 0)
        {
            mlx_info->pa -= 2 * PI;
        }
        mlx_info->pdx = cos(mlx_info->pa) * 5;
        mlx_info->pdy = sin(mlx_info->pa) * 5;
		//Rotating right
	}
}
void movement_hook(void *x)
{
	mai_t *mlx_info;
	
	mlx_info = x;
	if (mlx_is_key_down(mlx_info->mlx, MLX_KEY_ESCAPE))
    {
        
		mlx_close_window(mlx_info->mlx);
    }
	if (mlx_is_key_down(mlx_info->mlx, MLX_KEY_UP))
    {
		mlx_info->img_arr[0]->instances->y -= 5;
        mlx_info->img_arr[3]->instances->y -= 5;
    }
	if (mlx_is_key_down(mlx_info->mlx, MLX_KEY_DOWN))
    {
		mlx_info->img_arr[0]->instances->y += 5;
		mlx_info->img_arr[3]->instances->y += 5;
    }
	if (mlx_is_key_down(mlx_info->mlx, MLX_KEY_LEFT))
    {
		mlx_info->img_arr[0]->instances->x -= 5;
		mlx_info->img_arr[3]->instances->x -= 5;
    }
	if (mlx_is_key_down(mlx_info->mlx, MLX_KEY_RIGHT))
    {
		mlx_info->img_arr[0]->instances->x += 5;
		mlx_info->img_arr[3]->instances->x += 5;
    }
	rotating_player(mlx_info);
}



int	main(int argc, char **argv)
{
	//Before rendering get the map dimensions
	mai_t mlx_info;
	if(argc != 2 || !check_map(argv, &mlx_info))
	{
		printf("Error\n");
		return 0;
	}
    const char		 	*args[] = {AUDIO, "./song.wav", NULL};
    int pid = fork();
	if (pid == 0)
	{
		execvp(args[0], (char **)args);
		exit(1);
	}else{
	// int x = 9;
	// int y = 9;
	int texture_ammout = 5;
	printf("Height %d\n", mlx_info.map_height);
	printf("Width %d\n", mlx_info.map_width);
	mlx_info.mlx = mlx_init((mlx_info.map_width - 1)* IMG_SIDE, (mlx_info.map_height - 1)* IMG_SIDE, "Kurwiszon", true);
    mlx_info.px = (mlx_info.map_height * IMG_SIDE) / 2;
    printf("X : %f\n", mlx_info.px);
    mlx_info.py = (mlx_info.map_width * IMG_SIDE) / 2;
	printf("XY : %f\n", mlx_info.py);
    mlx_info.pdx = cos(mlx_info.pa) * 5;
    mlx_info.pdy = sin(mlx_info.pa) * 5;
	if (!mlx_info.mlx)
		exit(-99);
	mlx_info.img_arr = calloc(texture_ammout ,sizeof(mlx_image_t));
	draw_grid(&mlx_info);
	draw_player(&mlx_info, mlx_info.map_height ,mlx_info.map_width);
	mlx_loop_hook(mlx_info.mlx, &movement_hook, &mlx_info);
	mlx_loop(mlx_info.mlx);
    }
    return (0);
}
