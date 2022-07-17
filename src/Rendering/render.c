/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 15:39:16 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/17 17:20:58 by jkaczmar         ###   ########.fr       */
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
			data->floor_info.cell_x = (int)data->floor_info.floor_x;
			data->floor_info.cell_y = (int)data->floor_info.floor_y;
			data->floor_info.tx = (int)(data->texture_data->width
					* (data->floor_info.floor_x - data->floor_info.cell_x))
				& (data->texture_data->width - 1);
			data->floor_info.ty = (int)(data->texture_data->height
					* (data->floor_info.floor_y - data->floor_info.cell_y))
				& (data->texture_data->height - 1);
			data->floor_info.floor_x += data->floor_info.floor_step_x;
			data->floor_info.floor_y += data->floor_info.floor_step_y;
			better_pixel_put(&data->main_img, t, y, data->floor_color);
			better_pixel_put(&data->main_img, t, data->window_height - y - 1,
				data->celling_color);
		}
	}
}

static void	check_side_y(t_mlx_info *mlx_info)
{
	if (mlx_info->draw_prop.ray_dir_y < 0)
	{
		mlx_info->draw_prop.step_y = -1;
		mlx_info->draw_prop.side_dist_y = mlx_info->draw_prop.delta_dist_y
			* (mlx_info->unique_prop.pos_y - mlx_info->draw_prop.map_y);
	}
	else
	{
		mlx_info->draw_prop.step_y = 1;
		mlx_info->draw_prop.side_dist_y = mlx_info->draw_prop.delta_dist_y
			* (mlx_info->draw_prop.map_y + 1.0 - mlx_info->unique_prop.pos_y);
	}
}

void	check_side_xy(t_mlx_info *mlx_info)
{
	if (mlx_info->draw_prop.ray_dir_x < 0)
	{
		mlx_info->draw_prop.step_x = -1;
		mlx_info->draw_prop.side_dist_x = mlx_info->draw_prop.delta_dist_x
			* (mlx_info->unique_prop.pos_x - mlx_info->draw_prop.map_x);
	}
	else
	{
		mlx_info->draw_prop.step_x = 1;
		mlx_info->draw_prop.side_dist_x = mlx_info->draw_prop.delta_dist_x
			* (mlx_info->draw_prop.map_x + 1.0 - mlx_info->unique_prop.pos_x);
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
		mlx_info->sprites->z_buff[x] = mlx_info->draw_prop.perp_wall_dist;
		x++;
	}
	mlx_put_image_to_window(
		mlx_info->mlx, mlx_info->main_win, mlx_info->main_img.img, 0, 0);
}
