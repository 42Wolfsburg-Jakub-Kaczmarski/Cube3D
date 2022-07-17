/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 15:39:16 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/17 12:39:55 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube.h"

void	init_img(t_mlx_info *mlx_info)
{
	// IF there is a leak it's hereeee :)
	mlx_info->main_img.img = mlx_new_image(
			mlx_info->mlx, mlx_info->window_width, mlx_info->window_height);
	mlx_info->main_img.addr = mlx_get_data_addr(mlx_info->main_img.img,
			&mlx_info->main_img.bits_per_pixel,
			&mlx_info->main_img.line_length,
			&mlx_info->main_img.endian);
}

void	floor_casting(t_mlx_info *data)
{
	int	y;
	int	t;

	y = -1;
	while (++y < data->window_height)
	{
		prep_floor(data, y);
		t = -1;
		while (++t < data->window_width)
		{
			data->floor_info.cellX = (int)data->floor_info.floorX;
			data->floor_info.cellY = (int)data->floor_info.floorY;
			data->floor_info.tx = (int)(data->texture_data->width
					* (data->floor_info.floorX - data->floor_info.cellX))
				& (data->texture_data->width - 1);
			data->floor_info.ty = (int)(data->texture_data->height
					* (data->floor_info.floorY - data->floor_info.cellY))
				& (data->texture_data->height - 1);
			data->floor_info.floorX += data->floor_info.floorStepX;
			data->floor_info.floorY += data->floor_info.floorStepY;
			better_pixel_put(&data->main_img, t, y, data->floor_color);
			better_pixel_put(&data->main_img, t, data->window_height - y - 1,
				data->celling_color);
		}
	}
}

static void	check_side_y(t_mlx_info *mlx_info)
{
	if (mlx_info->draw_prop.rayDirY < 0)
	{
		mlx_info->draw_prop.stepY = -1;
		mlx_info->draw_prop.sideDistY = mlx_info->draw_prop.deltaDistY
			* (mlx_info->unique_prop.posY - mlx_info->draw_prop.mapY);
	}
	else
	{
		mlx_info->draw_prop.stepY = 1;
		mlx_info->draw_prop.sideDistY = mlx_info->draw_prop.deltaDistY
			* (mlx_info->draw_prop.mapY + 1.0 - mlx_info->unique_prop.posY);
	}
}

void	check_side_xy(t_mlx_info *mlx_info)
{
	if (mlx_info->draw_prop.rayDirX < 0)
	{
		mlx_info->draw_prop.stepX = -1;
		mlx_info->draw_prop.sideDistX = mlx_info->draw_prop.deltaDistX
			* (mlx_info->unique_prop.posX - mlx_info->draw_prop.mapX);
	}
	else
	{
		mlx_info->draw_prop.stepX = 1;
		mlx_info->draw_prop.sideDistX = mlx_info->draw_prop.deltaDistX
			* (mlx_info->draw_prop.mapX + 1.0 - mlx_info->unique_prop.posX);
	}
	check_side_y(mlx_info);
}

void	render(t_mlx_info *mlx_info)
{
	int	x;
	int	w;

	x = 0;
	w = mlx_info->window_width;
	init_img(mlx_info);
	floor_casting(mlx_info);
	while (x < w)
	{
		init_for_drawing(mlx_info, x, w);
		check_side_xy(mlx_info);
		hit_loop(mlx_info);
		calculate_wall_dist(mlx_info);
		calculate_wall_tex_x(mlx_info);
		get_which_tex(mlx_info);
		render_textures(mlx_info, x);
		x++;
	}
	mlx_put_image_to_window(
		mlx_info->mlx, mlx_info->main_win, mlx_info->main_img.img, 0, 0);
}
