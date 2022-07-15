/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:43:05 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/15 15:21:27 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cube.h"


void key_W_hook(t_mlx_info *mlx_info)
{
	t_uniq_prop *prop;

	prop = &(mlx_info->unique_prop);	
	if(mlx_info->map[(int)prop->posX + (int)prop->dirX * (int)prop->move_speed][(int)prop->posY] != 1)
	{
		prop->posX += prop->dirX * prop->move_speed;
	}
	if(mlx_info->map[(int)prop->posX][(int)prop->posY - (int)prop->dirY * (int)prop->move_speed] && mlx_info->map[(int)prop->posX][(int)prop->posY - (int)prop->dirY * (int)prop->move_speed] != 1)
	{
		prop->posY += prop->dirY * prop->move_speed;
	}
}

void	key_S(t_mlx_info *mlx_info)
{
	t_uniq_prop *prop;

	prop = &(mlx_info->unique_prop);
	if(mlx_info->map[(int)prop->posX - (int)prop->dirX * (int) prop->move_speed][(int)prop->posY] != 1)
	{
		prop->posX -= prop->dirX * prop->move_speed;
	}
	if(mlx_info->map[(int)prop->posX][(int)prop->posY - (int)prop->dirY * (int)prop->move_speed ] != 1)
	{
		prop->posY -= prop->dirY * prop->move_speed;
	}
}

void	key_A(t_mlx_info *mlx_info)
{
	t_uniq_prop *prop;

	prop = &(mlx_info->unique_prop);
	if(mlx_info->map[(int)prop->posX - (int)prop->planeX * (int)prop->move_speed][(int)prop->posY] != 1)
	{
		prop->posX -= prop->planeX * prop->move_speed;
	}
	if(mlx_info->map[(int)prop->posX][(int)prop->posY - (int)prop->planeY * (int)prop->move_speed ] != 1)
	{
		prop->posY -= prop->planeY * prop->move_speed;
	}
}

void	key_D(t_mlx_info *mlx_info)
{
	t_uniq_prop *prop;

	prop = &(mlx_info->unique_prop);
	if(mlx_info->map[(int)prop->posX - (int)prop->planeX * (int)prop->move_speed][(int)prop->posY] != 1)
	{
		prop->posX += prop->planeX * prop->move_speed;
	}
	if(mlx_info->map[(int)prop->posX][(int)prop->posY - (int)prop->planeY * (int)prop->move_speed ] != 1)
	{
		prop->posY += prop->planeY * prop->move_speed;

	}
}
