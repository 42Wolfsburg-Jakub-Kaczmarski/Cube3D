/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 15:42:45 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/16 15:43:54 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cube.h"

void	hit_loop(t_mlx_info *mlx_info)
{
	while (mlx_info->draw_prop.hit == 0)
	{
		if (mlx_info->draw_prop.sideDistX < mlx_info->draw_prop.sideDistY)
		{
			mlx_info->draw_prop.sideDistX += mlx_info->draw_prop.deltaDistX;
			mlx_info->draw_prop.mapX += mlx_info->draw_prop.stepX;
			mlx_info->draw_prop.side = 0;
		}
		else
		{
			mlx_info->draw_prop.sideDistY += mlx_info->draw_prop.deltaDistY;
			mlx_info->draw_prop.mapY += mlx_info->draw_prop.stepY;
			mlx_info->draw_prop.side = 1;
		}
		if (mlx_info->map[mlx_info->draw_prop.mapX][mlx_info->draw_prop.mapY] > 0)
			mlx_info->draw_prop.hit = 1;
	}
}

void	calculate_wall_dist(t_mlx_info *mlx_info)
{
	if (mlx_info->draw_prop.side == 0)
	{
		mlx_info->draw_prop.perpWallDist =
			mlx_info->draw_prop.sideDistX - mlx_info->draw_prop.deltaDistX;
	}
	else
	{
		mlx_info->draw_prop.perpWallDist =
			(mlx_info->draw_prop.sideDistY - mlx_info->draw_prop.deltaDistY);
	}
	mlx_info->draw_prop.lineHeight =
		(int)(mlx_info->window_height / mlx_info->draw_prop.perpWallDist);
	mlx_info->draw_prop.drawStart =
		-mlx_info->draw_prop.lineHeight / 2 + mlx_info->window_height / 2;
	if (mlx_info->draw_prop.drawStart < 0)
	{
		mlx_info->draw_prop.drawStart = 0;
	}
	mlx_info->draw_prop.drawEnd =
		mlx_info->draw_prop.lineHeight / 2 + mlx_info->window_height / 2;
	if (mlx_info->draw_prop.drawEnd >= mlx_info->window_height)
	{
		mlx_info->draw_prop.drawEnd = mlx_info->window_height - 1;
	}
}

void	color_walls(t_mlx_info *mlx_info, int x)
{
	int	color;

	if (mlx_info->map[mlx_info->draw_prop.mapX][mlx_info->draw_prop.mapY] == 1)
		color = 0x00FFFFFF;
	else if (mlx_info->map[mlx_info->draw_prop.mapX][mlx_info->draw_prop.mapY] ==
				2)
		color = 0x00FF00FF;
	else if (mlx_info->map[mlx_info->draw_prop.mapX][mlx_info->draw_prop.mapY] ==
				0)
		color = 0;
	else if (mlx_info->map[mlx_info->draw_prop.mapX][mlx_info->draw_prop.mapY] ==
				3)
		color = 0x0000FFFF;
	else if (mlx_info->map[mlx_info->draw_prop.mapX][mlx_info->draw_prop.mapY] ==
				4)
		color = 0x00FFF0FF;
	else
		color = 0;
	if (mlx_info->draw_prop.side == 1)
		color = color / 2;
	draw_line(mlx_info,
				x,
				mlx_info->draw_prop.drawStart,
				mlx_info->draw_prop.drawEnd,
				color);
}

void	calculate_wall_texX(t_mlx_info *mlx_info)
{
	mlx_info->draw_prop.texture_num =
		mlx_info->map[mlx_info->draw_prop.mapX][mlx_info->draw_prop.mapY] - 1;
	if (mlx_info->draw_prop.side == 0)
	{
		mlx_info->draw_prop.wall_X = mlx_info->unique_prop.posY +
			mlx_info->draw_prop.perpWallDist * mlx_info->draw_prop.rayDirY;
	}
	else
	{
		mlx_info->draw_prop.wall_X = mlx_info->unique_prop.posX +
			mlx_info->draw_prop.perpWallDist * mlx_info->draw_prop.rayDirX;
	}
	mlx_info->draw_prop.wall_X -= floor((mlx_info->draw_prop.wall_X));
	// X texture coord
	mlx_info->draw_prop.texX = (int)(mlx_info->draw_prop.wall_X *
										(double)mlx_info->unique_prop.texWidth);
	if (mlx_info->draw_prop.side == 0 && mlx_info->draw_prop.rayDirX > 0)
	{
		mlx_info->draw_prop.texX =
			mlx_info->unique_prop.texWidth - mlx_info->draw_prop.texX - 1;
	}
	if (mlx_info->draw_prop.side == 1 && mlx_info->draw_prop.rayDirY < 0)
	{
		mlx_info->draw_prop.texX =
			mlx_info->unique_prop.texWidth - mlx_info->draw_prop.texX - 1;
	}
}

void	render_textures(t_mlx_info *mlx_info, int x)
{
	int	y;
	int	r;
	int	g;
	int	b;
	int	a;
	int	pix;

	double step = 1.0 *
		mlx_info->texture_data[mlx_info->draw_prop.texture_num].height /
		mlx_info->draw_prop.lineHeight;
	double texPos = (mlx_info->draw_prop.drawStart - mlx_info->window_height / 2 +
						mlx_info->draw_prop.lineHeight / 2) *
		step;
	y = mlx_info->draw_prop.drawStart;
	while (y < mlx_info->draw_prop.drawEnd)
	{
		texPos += step;
		if (texPos - 1 < 0)
		{
			texPos = 1;
		}
		else if (texPos - 1 >
					mlx_info->texture_data[mlx_info->draw_prop.texture_num].height)
		{
			texPos =
				mlx_info->texture_data[mlx_info->draw_prop.texture_num].height -
				1;
		}
		t_color color =
			*mlx_info->texture_data[mlx_info->draw_prop.texture_num]
					.arr_color[mlx_info->draw_prop.texX][(int)(texPos)-1];
		r = color.r & 0xFF;
		g = color.g & 0xFF;
		b = color.b & 0xFF;
		a = color.a & 0xFF;
		pix = (a << 24) + (r << 16) + (g << 8) + (b);
		better_pixel_put(&mlx_info->main_img, x, y, pix);
		y++;
	}
}
