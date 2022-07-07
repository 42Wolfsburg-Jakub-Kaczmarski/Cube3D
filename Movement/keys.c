/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:43:05 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/07 14:54:58 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cube.h"


void key_W_hook(t_mlx_info *mlx_info)
{
	if(worldMap[(int)mlx_info->unique_prop.posX + (int)mlx_info->unique_prop.dirX * (int)mlx_info->unique_prop.move_speed][(int)mlx_info->unique_prop.posY] != 1)
		{
			mlx_info->unique_prop.posX += mlx_info->unique_prop.dirX * mlx_info->unique_prop.move_speed;
		}
		if(worldMap[(int)mlx_info->unique_prop.posX][(int)mlx_info->unique_prop.posY - (int)mlx_info->unique_prop.dirY * (int)mlx_info->unique_prop.move_speed ] != 1)
		{
			mlx_info->unique_prop.posY += mlx_info->unique_prop.dirY * mlx_info->unique_prop.move_speed;
		}
		mlx_clear_window(mlx_info->mlx, mlx_info->main_win);
		render(mlx_info);
}

void	key_S(t_mlx_info *mlx_info)
{
	if(worldMap[(int)mlx_info->unique_prop.posX - (int)mlx_info->unique_prop.dirX * (int) mlx_info->unique_prop.move_speed][(int)mlx_info->unique_prop.posY] != 1)
	{
		mlx_info->unique_prop.posX -= mlx_info->unique_prop.dirX * mlx_info->unique_prop.move_speed;
	}
	if(worldMap[(int)mlx_info->unique_prop.posX][(int)mlx_info->unique_prop.posY - (int)mlx_info->unique_prop.dirY * (int)mlx_info->unique_prop.move_speed ] != 1)
	{
		mlx_info->unique_prop.posY -= mlx_info->unique_prop.dirY * mlx_info->unique_prop.move_speed;
	}
	mlx_clear_window(mlx_info->mlx, mlx_info->main_win);
	render(mlx_info);
}

void	key_A(t_mlx_info *mlx_info)
{
		if(worldMap[(int)mlx_info->unique_prop.posX - (int)mlx_info->unique_prop.planeX * (int)mlx_info->unique_prop.move_speed][(int)mlx_info->unique_prop.posY] != 1)
		{
			mlx_info->unique_prop.posX -= mlx_info->unique_prop.planeX * mlx_info->unique_prop.move_speed;
		}
		if(worldMap[(int)mlx_info->unique_prop.posX][(int)mlx_info->unique_prop.posY - (int)mlx_info->unique_prop.planeY * (int)mlx_info->unique_prop.move_speed ] != 1)
		{
			mlx_info->unique_prop.posY -= mlx_info->unique_prop.planeY * mlx_info->unique_prop.move_speed;
		}
		mlx_clear_window(mlx_info->mlx, mlx_info->main_win);
		render(mlx_info);
}

void	key_D(t_mlx_info *mlx_info)
{
		if(worldMap[(int)mlx_info->unique_prop.posX - (int)mlx_info->unique_prop.planeX * (int)mlx_info->unique_prop.move_speed][(int)mlx_info->unique_prop.posY] != 1)
		{
			mlx_info->unique_prop.posX += mlx_info->unique_prop.planeX * mlx_info->unique_prop.move_speed;
		}
		if(worldMap[(int)mlx_info->unique_prop.posX][(int)mlx_info->unique_prop.posY - (int)mlx_info->unique_prop.planeY * (int)mlx_info->unique_prop.move_speed ] != 1)
		{
			mlx_info->unique_prop.posY += mlx_info->unique_prop.planeY * mlx_info->unique_prop.move_speed;

		}
		mlx_clear_window(mlx_info->mlx, mlx_info->main_win);
		render(mlx_info);
}
