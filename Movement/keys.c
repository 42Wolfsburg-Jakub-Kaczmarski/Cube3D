/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:43:05 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/16 17:50:24 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cube.h"
#include "../src/input_validation_and_map_creation/map_validation.h"

void	key_W_hook(t_mlx_info *mlx_info)
{
	if (mlx_info->map[(int)(mlx_info->unique_prop.posX +
							mlx_info->unique_prop.dirX *
								mlx_info->unique_prop.move_speed)]
						[(int)mlx_info->unique_prop.posY] != 1)
	{
		mlx_info->unique_prop.posX +=
			mlx_info->unique_prop.dirX * mlx_info->unique_prop.move_speed;
	}
	if (mlx_info->map[(int)(mlx_info->unique_prop.posX)][(
			int)(mlx_info->unique_prop.posY +
					mlx_info->unique_prop.dirY * mlx_info->unique_prop.move_speed)] !=
		1)
	{
		mlx_info->unique_prop.posY +=
			mlx_info->unique_prop.dirY * mlx_info->unique_prop.move_speed;
	}
}

void	key_S(t_mlx_info *mlx_info)
{
	if (mlx_info->map[(int)(mlx_info->unique_prop.posX -
							mlx_info->unique_prop.dirX *
								mlx_info->unique_prop.move_speed)]
						[(int)mlx_info->unique_prop.posY] != 1)
	{
		mlx_info->unique_prop.posX -=
			mlx_info->unique_prop.dirX * mlx_info->unique_prop.move_speed;
	}
	if (mlx_info->map[(int)(mlx_info->unique_prop.posX)][(
			int)(mlx_info->unique_prop.posY -
					mlx_info->unique_prop.dirY * mlx_info->unique_prop.move_speed)] !=
		1)
	{
		mlx_info->unique_prop.posY -=
			mlx_info->unique_prop.dirY * mlx_info->unique_prop.move_speed;
	}
}

void	key_A(t_mlx_info *mlx_info)
{
	if (mlx_info->map[(int)(mlx_info->unique_prop.posX -
							mlx_info->unique_prop.planeX *
								mlx_info->unique_prop.move_speed)]
						[(int)mlx_info->unique_prop.posY] != 1)
	{
		mlx_info->unique_prop.posX -=
			mlx_info->unique_prop.planeX * mlx_info->unique_prop.move_speed;
	}
	if (mlx_info->map[(int)(mlx_info->unique_prop.posX)][(
			int)(mlx_info->unique_prop.posY -
					mlx_info->unique_prop.planeY * mlx_info->unique_prop.move_speed)] !=
		1)
	{
		mlx_info->unique_prop.posY -=
			mlx_info->unique_prop.planeY * mlx_info->unique_prop.move_speed;
	}
}

void	key_D(t_mlx_info *mlx_info)
{
	if (mlx_info->map[(int)(mlx_info->unique_prop.posX -
							mlx_info->unique_prop.planeX * mlx_info->unique_prop.move_speed +
							0.5)][(int)(mlx_info->unique_prop.posY + 0.5)] != 1)
	{
		mlx_info->unique_prop.posX +=
			mlx_info->unique_prop.planeX * mlx_info->unique_prop.move_speed;
	}
	if (mlx_info->map[(int)(mlx_info->unique_prop.posX + 0.5)][(
			int)(mlx_info->unique_prop.posY -
					mlx_info->unique_prop.planeY * mlx_info->unique_prop.move_speed +
					0.5)] != 1)
	{
		mlx_info->unique_prop.posY +=
			mlx_info->unique_prop.planeY * mlx_info->unique_prop.move_speed;
	}
}
