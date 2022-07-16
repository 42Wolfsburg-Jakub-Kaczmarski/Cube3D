/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:43:05 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/16 15:38:58 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cube.h"
#include "../src/input_validation_and_map_creation/map_validation.h"

void key_W_hook(t_mlx_info *mlx_info)
{
	t_uniq_prop *prop;
	prop = &(mlx_info->unique_prop);
	
	int x = (int)prop->posX + (int)(prop->dirX * prop->move_speed);
	int y = (int)prop->posY - (int)(prop->dirY * prop->move_speed);
	int temp_X = prop->posX + prop->dirX * prop->move_speed;
	int temp_Y = prop->posY + prop->dirY * prop->move_speed;
	if( temp_X > 1 && temp_X < mapWidth - 1 && temp_Y > 1 && temp_Y < mapHeight - 1)
	{
		if (mlx_info->map[x][y] != 1)
		{
			prop->posX += prop->dirX * prop->move_speed;
			prop->posY += prop->dirY * prop->move_speed;
		}
	}

}

void	key_S(t_mlx_info *mlx_info)
{
	t_uniq_prop *prop;

	prop = &(mlx_info->unique_prop);
	int x = (int)prop->posX - (int)prop->dirX * (int) prop->move_speed;
	int y = (int)prop->posY - (int)prop->dirY * (int)prop->move_speed ;
	double temp_X = prop->posX - prop->dirX * prop->move_speed;
	double temp_Y = prop->posY - prop->dirY * prop->move_speed;

	if( temp_X > 1 && temp_X < mapWidth - 1 && temp_Y > 1 && temp_Y < mapHeight - 1 &&
		mlx_info->map[x][y] != 1)
	{
		prop->posX -= prop->dirX * prop->move_speed;
		prop->posY -= prop->dirY * prop->move_speed;
	}
}

void	key_A(t_mlx_info *mlx_info)
{
	t_uniq_prop *prop;

	prop = &(mlx_info->unique_prop);
	int x = (int)prop->posX - (int)prop->planeX * (int)prop->move_speed;
	int y = (int)prop->posY - (int)prop->planeY * (int)prop->move_speed;
	double temp_X = prop->posX - prop->planeX * prop->move_speed;
	double temp_Y = prop->posY - prop->planeY * prop->move_speed;
	
	if(temp_X > 1 && temp_X < mapWidth - 1 && temp_Y > 1 && temp_Y < mapHeight - 1 &&
		mlx_info->map[x][y] != 1)
	{
		prop->posX -= prop->planeX * prop->move_speed;
		prop->posY -= prop->planeY * prop->move_speed;
	}
}

void	key_D(t_mlx_info *mlx_info)
{
	t_uniq_prop *prop;
	prop = &(mlx_info->unique_prop);
	int x = prop->posX - (int)prop->planeX * (int)prop->move_speed;
	int y = prop->posY - (int)prop->planeY * (int)prop->move_speed;
	double temp_X = prop->posX + prop->planeX * prop->move_speed;
	double temp_Y = prop->posY + prop->planeY * prop->move_speed;
	
	if(temp_X > 1 && temp_X < mapWidth - 1 && temp_Y > 1 && temp_Y < mapHeight - 1 &&
		mlx_info->map[x][y] != 1)
	{
		prop->posX += prop->planeX * prop->move_speed;
		prop->posY += prop->planeY * prop->move_speed;

	}
}
