/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:43:05 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/07 14:50:44 by jkaczmar         ###   ########.fr       */
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
		// mlx_destroy_image(mlx_info->mlx, mlx_info->main_img.img);
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
	// mlx_destroy_image(mlx_info->mlx, mlx_info->main_img.img);
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

int	key_hook(int keycode,void *mlx)
{
	t_mlx_info *mlx_info = (t_mlx_info *) mlx;
	if(keycode == 13)
	{	
		key_W_hook(mlx_info);
	}
	if (keycode == 1)
	{
		key_S(mlx_info);
	}
	if(keycode == 0)
	{
		key_A(mlx_info);
	}
	if(keycode == 2)
	{
		key_D(mlx_info);
	}
	if(keycode == 124)
	{
		key_right_arr(mlx_info);
	}
	if(keycode == 123)
	{
		key_left_arr(mlx_info);
	}
	if(keycode == 53)
	{
		mlx_destroy_window(mlx_info->mlx, mlx_info->main_win);
		exit(1);
	}
	return 0;
}