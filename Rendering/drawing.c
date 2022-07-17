/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 15:45:59 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/17 10:58:00 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cube.h"

void	load_images(t_mlx_info *mlx_info)
{
	int	i;

	i = 0;
	mlx_info->mlx_imgs = calloc(10, sizeof(void *));
	mlx_info->texture_data = calloc(7, sizeof(*mlx_info->texture_data));
	mlx_info->im = malloc(4 * sizeof(t_temp_img));
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
}

void	prep_floor(t_mlx_info *mlx_info, int y)
{
	t_floor_vars	floor_info;
	t_uniq_prop		unique_prop;

	floor_info = mlx_info->floor_info;
	unique_prop = mlx_info->unique_prop;
	floor_info.rayDirX0 = unique_prop.dirX - unique_prop.planeX;
	floor_info.rayDirY0 = unique_prop.dirY - unique_prop.planeY;
	floor_info.rayDirX1 = unique_prop.dirX + unique_prop.planeX;
	floor_info.rayDirY1 = unique_prop.dirY + unique_prop.planeY;
	floor_info.p = y - mlx_info->window_height / 2;
	floor_info.posZ = 0.5 * mlx_info->window_height;
	floor_info.rowDistance = floor_info.posZ / floor_info.p;
	floor_info.floorStepX = floor_info.rowDistance
		* (floor_info.rayDirX1 - floor_info.rayDirX0)
		/ mlx_info->window_width;
	floor_info.floorStepY = floor_info.rowDistance
		* (floor_info.rayDirY1 - floor_info.rayDirY0)
		/ mlx_info->window_width;
	floor_info.floorX = unique_prop.posX
		+ floor_info.rowDistance * floor_info.rayDirX0;
	floor_info.floorY = unique_prop.posY
		+ floor_info.rowDistance * floor_info.rayDirY0;
}

void	get_which_tex(t_mlx_info *mlx_info)
{
	if (mlx_info->draw_prop.side == 0 && mlx_info->draw_prop.rayDirX > 0)
	{
		mlx_info->draw_prop.texture_num = EAST;
	}
	else if (mlx_info->draw_prop.side == 0)
	{
		mlx_info->draw_prop.texture_num = WEST;
	}
	else if (mlx_info->draw_prop.side == 1 && mlx_info->draw_prop.rayDirY > 0)
	{
		mlx_info->draw_prop.texture_num = SOUTH;
	}
	else
	{
		mlx_info->draw_prop.texture_num = NORTH;
	}
}
