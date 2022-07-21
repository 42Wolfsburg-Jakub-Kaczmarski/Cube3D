/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 15:45:59 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/21 21:20:02 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube.h"

void	init_for_drawing(t_mlx_info *mlx_info, int x, int w)
{
	mlx_info->draw_prop.camera_x = 2 * x / (double)w - 1;
	mlx_info->draw_prop.ray_dir_x = mlx_info->unique_prop.dir_x
		+ mlx_info->unique_prop.plane_x * mlx_info->draw_prop.camera_x;
	mlx_info->draw_prop.ray_dir_y = mlx_info->unique_prop.dir_y
		+ mlx_info->unique_prop.plane_y * mlx_info->draw_prop.camera_x;
	mlx_info->draw_prop.map_x = (int)mlx_info->unique_prop.pos_x;
	mlx_info->draw_prop.map_y = (int)mlx_info->unique_prop.pos_y;
	mlx_info->draw_prop.hit = 0;
	if (mlx_info->draw_prop.ray_dir_x == 0)
		mlx_info->draw_prop.delta_dist_x = 1e30;
	else
		mlx_info->draw_prop.delta_dist_x = fabs(1 / mlx_info->draw_prop.ray_dir_x);
	if (mlx_info->draw_prop.ray_dir_y == 0)
		mlx_info->draw_prop.delta_dist_y = 1e30;
	else
		mlx_info->draw_prop.delta_dist_y = fabs(1 / mlx_info->draw_prop.ray_dir_y);
}

void	load_images(t_mlx_info *mlx_info)
{
	int	i;

	i = 0;
	mlx_info->mlx_imgs = calloc(12, sizeof(void *));
	mlx_info->texture_data = calloc(12, sizeof(*mlx_info->texture_data));
	mlx_info->im = malloc(12 * sizeof(t_temp_img));
	// printf("Img thingy %d", mlx_info->texture_data.);
	while (i < 4)
	{
		mlx_info->mlx_imgs[i] = mlx_xpm_file_to_image(mlx_info->mlx,
				mlx_info->texture_paths[i],
				&mlx_info->texture_data[i].width,
				&mlx_info->texture_data[i].height);
		mlx_info->im[i].img_data = mlx_get_data_addr(mlx_info->mlx_imgs[i],
				&mlx_info->im[i].img_bp,
				&mlx_info->im[i].img_sl,
				&mlx_info->im[i].img_e);
		mlx_info->texture_data[i].arr_color = create_color_arr(&mlx_info->im[i],
				mlx_info->texture_data[i].height,
				mlx_info->texture_data[i].width);
		mlx_info->texture_data[i].img_h = mlx_info->mlx_imgs[i];
		i++;
	}
	// 9  is sword
	i = 9;
		mlx_info->mlx_imgs[i] = mlx_xpm_file_to_image(mlx_info->mlx,
				"./assets/sword.xpm",
				&mlx_info->texture_data[i].width,
				&mlx_info->texture_data[i].height);
		mlx_info->im[i].img_data = mlx_get_data_addr(mlx_info->mlx_imgs[i],
				&mlx_info->im[i].img_bp,
				&mlx_info->im[i].img_sl,
				&mlx_info->im[i].img_e);
		mlx_info->texture_data[i].arr_color = create_color_arr(&mlx_info->im[i],
				mlx_info->texture_data[i].height,
				mlx_info->texture_data[i].width);
		mlx_info->texture_data[i].img_h = mlx_info->mlx_imgs[i];

}


void	prep_floor(t_mlx_info *mlx_info, int y)
{
	t_floor_vars	floor_info;
	t_uniq_prop		unique_prop;

	floor_info = mlx_info->floor_info;
	unique_prop = mlx_info->unique_prop;
	floor_info.ray_dir_x0 = unique_prop.dir_x - unique_prop.plane_x;
	floor_info.ray_dir_y0 = unique_prop.dir_y - unique_prop.plane_y;
	floor_info.ray_dir_x1 = unique_prop.dir_x + unique_prop.plane_x;
	floor_info.ray_dir_y1 = unique_prop.dir_y + unique_prop.plane_y;
	floor_info.p = y - mlx_info->window_height / 2;
	floor_info.pos_z = 0.5 * mlx_info->window_height;
	floor_info.row_distance = floor_info.pos_z / floor_info.p;
	floor_info.floor_step_x = floor_info.row_distance
		* (floor_info.ray_dir_x1 - floor_info.ray_dir_x0)
		/ mlx_info->window_width;
	floor_info.floor_step_y = floor_info.row_distance
		* (floor_info.ray_dir_y1 - floor_info.ray_dir_y0)
		/ mlx_info->window_width;
	floor_info.floor_x = unique_prop.pos_x
		+ floor_info.row_distance * floor_info.ray_dir_x0;
	floor_info.floor_y = unique_prop.pos_y
		+ floor_info.row_distance * floor_info.ray_dir_y0;
}

void	get_which_tex(t_mlx_info *mlx_info)
{
	if (mlx_info->draw_prop.side == 0 && mlx_info->draw_prop.ray_dir_x > 0)
	{
		mlx_info->draw_prop.texture_num = EAST;
	}
	else if (mlx_info->draw_prop.side == 0)
	{
		mlx_info->draw_prop.texture_num = WEST;
	}
	else if (mlx_info->draw_prop.side == 1 && mlx_info->draw_prop.ray_dir_y > 0)
	{
		mlx_info->draw_prop.texture_num = SOUTH;
	}
	else
	{
		mlx_info->draw_prop.texture_num = NORTH;
	}
}
