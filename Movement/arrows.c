/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:54:46 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/16 21:52:34 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cube.h"

void	key_right_arr(t_mlx_info *mlx_info)
{
	double	oldDirX;
	double	oldplaneX;

	oldDirX = mlx_info->unique_prop.dirX;
	mlx_info->unique_prop.dirX =
		mlx_info->unique_prop.dirX * cos(-mlx_info->unique_prop.rotSpeed) -
		mlx_info->unique_prop.dirY * sin(-mlx_info->unique_prop.rotSpeed);
	mlx_info->unique_prop.dirY = oldDirX * sin(-mlx_info->unique_prop.rotSpeed) +
		mlx_info->unique_prop.dirY * cos(-mlx_info->unique_prop.rotSpeed);
	oldplaneX = mlx_info->unique_prop.planeX;
	mlx_info->unique_prop.planeX =
		mlx_info->unique_prop.planeX * cos(-mlx_info->unique_prop.rotSpeed) -
		mlx_info->unique_prop.planeY * sin(-mlx_info->unique_prop.rotSpeed);
	mlx_info->unique_prop.planeY =
		oldplaneX * sin(-mlx_info->unique_prop.rotSpeed) +
		mlx_info->unique_prop.planeY * cos(-mlx_info->unique_prop.rotSpeed);
}

void	key_left_arr(t_mlx_info *mlx_info)
{
	double	oldDirX;
	double	oldplaneX;

	oldDirX = mlx_info->unique_prop.dirX;
	mlx_info->unique_prop.dirX =
		mlx_info->unique_prop.dirX * cos(mlx_info->unique_prop.rotSpeed) -
		mlx_info->unique_prop.dirY * sin(mlx_info->unique_prop.rotSpeed);
	mlx_info->unique_prop.dirY = oldDirX * sin(mlx_info->unique_prop.rotSpeed) +
		mlx_info->unique_prop.dirY * cos(mlx_info->unique_prop.rotSpeed);
	oldplaneX = mlx_info->unique_prop.planeX;
	mlx_info->unique_prop.planeX =
		mlx_info->unique_prop.planeX * cos(mlx_info->unique_prop.rotSpeed) -
		mlx_info->unique_prop.planeY * sin(mlx_info->unique_prop.rotSpeed);
	mlx_info->unique_prop.planeY =
		oldplaneX * sin(mlx_info->unique_prop.rotSpeed) +
		mlx_info->unique_prop.planeY * cos(mlx_info->unique_prop.rotSpeed);
}
