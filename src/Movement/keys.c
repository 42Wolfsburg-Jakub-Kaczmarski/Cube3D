/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:43:05 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/17 13:48:21 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube.h"
#include "../../src/input_validation_and_map_creation/map_validation.h"

void	key_W_hook(t_mlx_info *mlx_info)
{
	if (mlx_info->map[(int)(mlx_info->unique_prop.pos_x +
							mlx_info->unique_prop.dir_x *
								mlx_info->unique_prop.move_speed)]
						[(int)mlx_info->unique_prop.pos_y] != 1)
	{
		mlx_info->unique_prop.pos_x +=
			mlx_info->unique_prop.dir_x * mlx_info->unique_prop.move_speed;
	}
	if (mlx_info->map[(int)(mlx_info->unique_prop.pos_x)][(
			int)(mlx_info->unique_prop.pos_y +
					mlx_info->unique_prop.dir_y * mlx_info->unique_prop.move_speed)] !=
		1)
	{
		mlx_info->unique_prop.pos_y +=
			mlx_info->unique_prop.dir_y * mlx_info->unique_prop.move_speed;
	}
}

void	key_S(t_mlx_info *mlx_info)
{
	if (mlx_info->map[(int)(mlx_info->unique_prop.pos_x -
							mlx_info->unique_prop.dir_x *
								mlx_info->unique_prop.move_speed)]
						[(int)mlx_info->unique_prop.pos_y] != 1)
	{
		mlx_info->unique_prop.pos_x -=
			mlx_info->unique_prop.dir_x * mlx_info->unique_prop.move_speed;
	}
	if (mlx_info->map[(int)(mlx_info->unique_prop.pos_x)][(
			int)(mlx_info->unique_prop.pos_y -
					mlx_info->unique_prop.dir_y * mlx_info->unique_prop.move_speed)] !=
		1)
	{
		mlx_info->unique_prop.pos_y -=
			mlx_info->unique_prop.dir_y * mlx_info->unique_prop.move_speed;
	}
}

void	key_A(t_mlx_info *mlx_info)
{
	if (mlx_info->map[(int)(mlx_info->unique_prop.pos_x -
							mlx_info->unique_prop.plane_x *
								mlx_info->unique_prop.move_speed)]
						[(int)mlx_info->unique_prop.pos_y] != 1)
	{
		mlx_info->unique_prop.pos_x -=
			mlx_info->unique_prop.plane_x * mlx_info->unique_prop.move_speed;
	}
	if (mlx_info->map[(int)(mlx_info->unique_prop.pos_x)][(
			int)(mlx_info->unique_prop.pos_y -
					mlx_info->unique_prop.plane_y * mlx_info->unique_prop.move_speed)] !=
		1)
	{
		mlx_info->unique_prop.pos_y -=
			mlx_info->unique_prop.plane_y * mlx_info->unique_prop.move_speed;
	}
}

void	key_D(t_mlx_info *mlx_info)
{
	if (mlx_info->map[(int)(mlx_info->unique_prop.pos_x -
							mlx_info->unique_prop.plane_x * mlx_info->unique_prop.move_speed +
							0.5)][(int)(mlx_info->unique_prop.pos_y + 0.5)] != 1)
	{
		mlx_info->unique_prop.pos_x +=
			mlx_info->unique_prop.plane_x * mlx_info->unique_prop.move_speed;
	}
	if (mlx_info->map[(int)(mlx_info->unique_prop.pos_x + 0.5)][(
			int)(mlx_info->unique_prop.pos_y -
					mlx_info->unique_prop.plane_y * mlx_info->unique_prop.move_speed +
					0.5)] != 1)
	{
		mlx_info->unique_prop.pos_y +=
			mlx_info->unique_prop.plane_y * mlx_info->unique_prop.move_speed;
	}
}
