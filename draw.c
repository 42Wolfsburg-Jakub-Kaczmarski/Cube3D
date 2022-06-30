/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 21:17:12 by kmilchev          #+#    #+#             */
/*   Updated: 2022/06/30 20:28:32 by kmilchev         ###   ########.fr       */
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

void draw_wand(t_mlx *mlx_info)
{
	mlx_delete_image(mlx_info->mlx, mlx_info->img_arr[WAND]);
	mlx_info->img_arr[WAND] = mlx_new_image(mlx_info->mlx, mlx_info->map_width * IMG_SIDE, mlx_info->map_height * IMG_SIDE);
	mlx_info->wx = (PLAYER_SIZE / 2 + mlx_info->px) + cos(mlx_info->dir) * WAND_LEN;
	mlx_info->wy = (PLAYER_SIZE / 2 + mlx_info->py) + sin(mlx_info->dir) * WAND_LEN;
	draw_line(
			mlx_info->img_arr[WAND],
			(PLAYER_SIZE / 2 + mlx_info->px),
			(PLAYER_SIZE / 2 + mlx_info->py),
			mlx_info->wx, 
			mlx_info->wy,
			0xFFFFFF
			);
	mlx_image_to_window(mlx_info->mlx, mlx_info->img_arr[WAND], 0, 0);
	mlx_set_instance_depth(mlx_info->img_arr[WAND]->instances, 200);
	// mlx_image_to_window(mlx_info->mlx, mlx_info->img_arr[WAND], mlx_info->wx, mlx_info->wy);
}

void draw_grid(t_mlx *mlx)
{
	load_textures(mlx);
	//Loop through the map
	int i = 0;
	int j = 0;
	int y = 0;
	int x = 0;
	while(i < mlx->map_height )
	{
		j = 0;
		y = 0;
		while(j < mlx->map_width)
		{
				if(mlx->map[i][j] == '1')
					mlx_image_to_window(mlx->mlx ,mlx->img_arr[1],y, x);
				else if(mlx->map[i][j] == '0' || mlx->map[i][j] == 'P')
				{
					mlx_image_to_window(mlx->mlx, mlx->img_arr[2], y, x);
				}
				y += IMG_SIDE + 1;
				j++;
		}
		x += IMG_SIDE + 1;
		i++;
	}
}

void draw_player(t_mlx *mlx_info)
{
	mlx_info->img_arr[PLAYER] = mlx_new_image(mlx_info->mlx, PLAYER_SIZE, PLAYER_SIZE);
	memset(mlx_info->img_arr[PLAYER]->pixels, 99, PLAYER_SIZE * PLAYER_SIZE * sizeof(int));
	mlx_image_to_window(mlx_info->mlx, mlx_info->img_arr[PLAYER], mlx_info->px, mlx_info->py);
	mlx_set_instance_depth(mlx_info->img_arr[PLAYER]->instances, 995);
	draw_wand(mlx_info);
}