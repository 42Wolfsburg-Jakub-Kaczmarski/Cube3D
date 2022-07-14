/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:54:46 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/14 19:01:22 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cube.h"

void	key_right_arr(t_mlx_info *mlx_info)
{
	double oldDirX = mlx_info->unique_prop.dirX;
	mlx_info->unique_prop.dirX = mlx_info->unique_prop.dirX * cos(-mlx_info->unique_prop.rotSpeed) - mlx_info->unique_prop.dirY * sin(-mlx_info->unique_prop.rotSpeed);
	mlx_info->unique_prop.dirY = oldDirX * sin(-mlx_info->unique_prop.rotSpeed)  + mlx_info->unique_prop.dirY * cos(-mlx_info->unique_prop.rotSpeed);
	double oldplaneX = mlx_info->unique_prop.planeX;
	mlx_info->unique_prop.planeX = mlx_info->unique_prop.planeX * cos(-mlx_info->unique_prop.rotSpeed) - mlx_info->unique_prop.planeY * sin(-mlx_info->unique_prop.rotSpeed);
	mlx_info->unique_prop.planeY = oldplaneX * sin(-mlx_info->unique_prop.rotSpeed) + mlx_info->unique_prop.planeY * cos(-mlx_info->unique_prop.rotSpeed);
	mlx_clear_window(mlx_info->mlx, mlx_info->main_win);
	render(mlx_info);
}

void	key_left_arr(t_mlx_info *mlx_info)
{
	double oldDirX = mlx_info->unique_prop.dirX;
	mlx_info->unique_prop.dirX = mlx_info->unique_prop.dirX * cos(mlx_info->unique_prop.rotSpeed) - mlx_info->unique_prop.dirY * sin(mlx_info->unique_prop.rotSpeed);
	mlx_info->unique_prop.dirY = oldDirX * sin(mlx_info->unique_prop.rotSpeed)  + mlx_info->unique_prop.dirY * cos(mlx_info->unique_prop.rotSpeed);
	double oldplaneX = mlx_info->unique_prop.planeX;
	mlx_info->unique_prop.planeX = mlx_info->unique_prop.planeX * cos(mlx_info->unique_prop.rotSpeed) - mlx_info->unique_prop.planeY * sin(mlx_info->unique_prop.rotSpeed);
	mlx_info->unique_prop.planeY = oldplaneX * sin(mlx_info->unique_prop.rotSpeed) + mlx_info->unique_prop.planeY * cos(mlx_info->unique_prop.rotSpeed);
	mlx_clear_window(mlx_info->mlx, mlx_info->main_win);
	render(mlx_info);
}
