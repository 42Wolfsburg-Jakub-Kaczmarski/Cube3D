/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 15:45:59 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/16 15:46:25 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cube.h"

void	load_images(t_mlx_info *mlx_info)
{
	t_temp_img	img;
	t_temp_img	img1;
	t_temp_img	img2;
	t_temp_img	img3;

	mlx_info->mlx_imgs = calloc(10, sizeof(void *));
	mlx_info->texture_data = calloc(7, sizeof(*mlx_info->texture_data));
	mlx_info->mlx_imgs[0] =
		mlx_xpm_file_to_image(mlx_info->mlx,
								mlx_info->texture_paths[0],
								&mlx_info->texture_data[0].width,
								&mlx_info->texture_data[0].height);
	mlx_info->mlx_imgs[1] =
		mlx_xpm_file_to_image(mlx_info->mlx,
								mlx_info->texture_paths[1],
								&mlx_info->texture_data[1].width,
								&mlx_info->texture_data[1].height);
	mlx_info->mlx_imgs[2] =
		mlx_xpm_file_to_image(mlx_info->mlx,
								mlx_info->texture_paths[2],
								&mlx_info->texture_data[2].width,
								&mlx_info->texture_data[2].height);
	mlx_info->mlx_imgs[3] =
		mlx_xpm_file_to_image(mlx_info->mlx,
								mlx_info->texture_paths[3],
								&mlx_info->texture_data[3].width,
								&mlx_info->texture_data[3].height);
	img.img_data = mlx_get_data_addr(
		mlx_info->mlx_imgs[0], &img.img_bp, &img.img_sl, &img.img_e);
	img1.img_data = mlx_get_data_addr(
		mlx_info->mlx_imgs[1], &img1.img_bp, &img1.img_sl, &img1.img_e);
	img2.img_data = mlx_get_data_addr(
		mlx_info->mlx_imgs[2], &img2.img_bp, &img2.img_sl, &img2.img_e);
	img3.img_data = mlx_get_data_addr(
		mlx_info->mlx_imgs[3], &img3.img_bp, &img3.img_sl, &img3.img_e);
	mlx_info->texture_data[0].arr_color = create_color_arr(
		&img, mlx_info->texture_data[0].height, mlx_info->texture_data[0].width);
	mlx_info->texture_data[1].arr_color = create_color_arr(
		&img1, mlx_info->texture_data[1].height, mlx_info->texture_data[1].width);
	mlx_info->texture_data[2].arr_color = create_color_arr(
		&img2, mlx_info->texture_data[2].height, mlx_info->texture_data[2].width);
	mlx_info->texture_data[3].arr_color = create_color_arr(
		&img3, mlx_info->texture_data[3].height, mlx_info->texture_data[3].width);
	mlx_info->texture_data[0].img_h = mlx_info->mlx_imgs[0];
	mlx_info->texture_data[1].img_h = mlx_info->mlx_imgs[1];
	mlx_info->texture_data[2].img_h = mlx_info->mlx_imgs[2];
	mlx_info->texture_data[3].img_h = mlx_info->mlx_imgs[3];
}

void	prep_floor(t_mlx_info *mlx_info, int y)
{
	mlx_info->floor_info.rayDirX0 =
		mlx_info->unique_prop.dirX - mlx_info->unique_prop.planeX;
	mlx_info->floor_info.rayDirY0 =
		mlx_info->unique_prop.dirY - mlx_info->unique_prop.planeY;
	mlx_info->floor_info.rayDirX1 =
		mlx_info->unique_prop.dirX + mlx_info->unique_prop.planeX;
	mlx_info->floor_info.rayDirY1 =
		mlx_info->unique_prop.dirY + mlx_info->unique_prop.planeY;
	mlx_info->floor_info.p = y - mlx_info->window_height / 2;
	mlx_info->floor_info.posZ = 0.5 * mlx_info->window_height;
	mlx_info->floor_info.rowDistance =
		mlx_info->floor_info.posZ / mlx_info->floor_info.p;
	mlx_info->floor_info.floorStepX = mlx_info->floor_info.rowDistance *
		(mlx_info->floor_info.rayDirX1 - mlx_info->floor_info.rayDirX0) /
		mlx_info->window_width;
	mlx_info->floor_info.floorStepY = mlx_info->floor_info.rowDistance *
		(mlx_info->floor_info.rayDirY1 - mlx_info->floor_info.rayDirY0) /
		mlx_info->window_width;
	mlx_info->floor_info.floorX = mlx_info->unique_prop.posX +
		mlx_info->floor_info.rowDistance * mlx_info->floor_info.rayDirX0;
	mlx_info->floor_info.floorY = mlx_info->unique_prop.posY +
		mlx_info->floor_info.rowDistance * mlx_info->floor_info.rayDirY0;
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
