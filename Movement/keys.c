/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:43:05 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/14 19:30:30 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cube.h"
#include "../src/input_validation_and_map_creation/map_validation.h"

void key_W_hook(t_mlx_info *mlx_info)
{
	t_uniq_prop *prop;

	prop = &(mlx_info->unique_prop);
	

	if(square_exists(mlx_info, (int)prop->posX + (int)prop->dirX * (int)prop->move_speed, (int)prop->posY) &&
		worldMap[(int)prop->posX + (int)prop->dirX * (int)prop->move_speed][(int)prop->posY] != 1)
	{
		prop->posX += prop->dirX * prop->move_speed;
	}
	if(worldMap[(int)prop->posX][(int)prop->posY - (int)prop->dirY * (int)prop->move_speed ] != 1)
	{
		prop->posY += prop->dirY * prop->move_speed;
	}
}

void	key_S(t_mlx_info *mlx_info)
{
	t_uniq_prop *prop;

	prop = &(mlx_info->unique_prop);
	if(worldMap[(int)prop->posX - (int)prop->dirX * (int) prop->move_speed][(int)prop->posY] != 1)
	{
		prop->posX -= prop->dirX * prop->move_speed;
	}
	if(worldMap[(int)prop->posX][(int)prop->posY - (int)prop->dirY * (int)prop->move_speed ] != 1)
	{
		prop->posY -= prop->dirY * prop->move_speed;
	}
}

void	key_A(t_mlx_info *mlx_info)
{
	t_uniq_prop *prop;

	prop = &(mlx_info->unique_prop);
	if(worldMap[(int)prop->posX - (int)prop->planeX * (int)prop->move_speed][(int)prop->posY] != 1)
	{
		prop->posX -= prop->planeX * prop->move_speed;
	}
	if(worldMap[(int)prop->posX][(int)prop->posY - (int)prop->planeY * (int)prop->move_speed ] != 1)
	{
		prop->posY -= prop->planeY * prop->move_speed;
	}
}

void	key_D(t_mlx_info *mlx_info)
{
	t_uniq_prop *prop;

	prop = &(mlx_info->unique_prop);
	if(worldMap[(int)prop->posX - (int)prop->planeX * (int)prop->move_speed][(int)prop->posY] != 1)
	{
		prop->posX += prop->planeX * prop->move_speed;
	}
	if(worldMap[(int)prop->posX][(int)prop->posY - (int)prop->planeY * (int)prop->move_speed ] != 1)
	{
		prop->posY += prop->planeY * prop->move_speed;

	}
}
