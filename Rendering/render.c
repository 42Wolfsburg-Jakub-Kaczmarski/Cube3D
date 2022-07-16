/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 15:39:16 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/16 15:42:05 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cube.h"

void	init_img(t_mlx_info *mlx_info)
{
	// IF there is a leak it's hereeee :)
	mlx_info->main_img.img = mlx_new_image(
		mlx_info->mlx, mlx_info->window_width, mlx_info->window_height);
	mlx_info->main_img.addr =
		mlx_get_data_addr(mlx_info->main_img.img,
							&mlx_info->main_img.bits_per_pixel,
							&mlx_info->main_img.line_length,
							&mlx_info->main_img.endian);
}

void	floor_casting(t_mlx_info *mlx_info)
{
	int	y;
	int	t;

	y = 0;
	while (y < mlx_info->window_height)
	{
		prep_floor(mlx_info, y);
		t = 0;
		while (t < mlx_info->window_width)
		{
			mlx_info->floor_info.cellX = (int)mlx_info->floor_info.floorX;
			mlx_info->floor_info.cellY = (int)mlx_info->floor_info.floorY;
			mlx_info->floor_info.tx =
				(int)(mlx_info->texture_data->width *
						(mlx_info->floor_info.floorX - mlx_info->floor_info.cellX)) &
				(mlx_info->texture_data->width - 1);
			mlx_info->floor_info.ty =
				(int)(mlx_info->texture_data->height *
						(mlx_info->floor_info.floorY - mlx_info->floor_info.cellY)) &
				(mlx_info->texture_data->height - 1);
			mlx_info->floor_info.floorX += mlx_info->floor_info.floorStepX;
			mlx_info->floor_info.floorY += mlx_info->floor_info.floorStepY;
			// int floor_texture = 2;
			// int ceiling_texture = 1;
			// int color;
			better_pixel_put(&mlx_info->main_img, t, y, mlx_info->floor_color);
			better_pixel_put(&mlx_info->main_img,
								t,
								mlx_info->window_height - y - 1,
								mlx_info->celling_color);
			t++;
		}
		y++;
	}
}

void	init_for_drawing(t_mlx_info *mlx_info, int x, int w)
{
	mlx_info->draw_prop.cameraX = 3 * x / (double)w - 1;
	mlx_info->draw_prop.rayDirX = mlx_info->unique_prop.dirX +
		mlx_info->unique_prop.planeX * mlx_info->draw_prop.cameraX;
	mlx_info->draw_prop.rayDirY = mlx_info->unique_prop.dirY +
		mlx_info->unique_prop.planeY * mlx_info->draw_prop.cameraX;
	mlx_info->draw_prop.mapX = (int)mlx_info->unique_prop.posX;
	mlx_info->draw_prop.mapY = (int)mlx_info->unique_prop.posY;
	mlx_info->draw_prop.hit = 0;
	if (mlx_info->draw_prop.rayDirX == 0)
		mlx_info->draw_prop.deltaDistX = 1e30;
	else
		mlx_info->draw_prop.deltaDistX = fabs(1 / mlx_info->draw_prop.rayDirX);
	if (mlx_info->draw_prop.rayDirY == 0)
		mlx_info->draw_prop.deltaDistY = 1e30;
	else
		mlx_info->draw_prop.deltaDistY = fabs(1 / mlx_info->draw_prop.rayDirY);
}

void	check_sideXY(t_mlx_info *mlx_info)
{
	if (mlx_info->draw_prop.rayDirX < 0)
	{
		mlx_info->draw_prop.stepX = -1;
		mlx_info->draw_prop.sideDistX =
			(mlx_info->unique_prop.posX - mlx_info->draw_prop.mapX) *
			mlx_info->draw_prop.deltaDistX;
	}
	else
	{
		mlx_info->draw_prop.stepX = 1;
		mlx_info->draw_prop.sideDistX =
			(mlx_info->draw_prop.mapX + 1.0 - mlx_info->unique_prop.posX) *
			mlx_info->draw_prop.deltaDistX;
	}
	if (mlx_info->draw_prop.rayDirY < 0)
	{
		mlx_info->draw_prop.stepY = -1;
		mlx_info->draw_prop.sideDistY =
			(mlx_info->unique_prop.posY - mlx_info->draw_prop.mapY) *
			mlx_info->draw_prop.deltaDistY;
	}
	else
	{
		mlx_info->draw_prop.stepY = 1;
		mlx_info->draw_prop.sideDistY =
			(mlx_info->draw_prop.mapY + 1.0 - mlx_info->unique_prop.posY) *
			mlx_info->draw_prop.deltaDistY;
	}
}

void	render(t_mlx_info *mlx_info)
{
	int	x;
	int	w;

	x = 0;
	w = mlx_info->window_width;
	init_img(mlx_info);
	// mlx_clear_window(mlx_info->mlx, mlx_info->main_win);
	floor_casting(mlx_info);
	while (x < w)
	{
		init_for_drawing(mlx_info, x, w);
		check_sideXY(mlx_info);
		hit_loop(mlx_info);
		calculate_wall_dist(mlx_info);
		calculate_wall_texX(mlx_info);
		get_which_tex(mlx_info);
		render_textures(mlx_info, x);
		// color_walls(mlx_info, x);
		x++;
	};
	mlx_put_image_to_window(
		mlx_info->mlx, mlx_info->main_win, mlx_info->main_img.img, 0, 0);
}
