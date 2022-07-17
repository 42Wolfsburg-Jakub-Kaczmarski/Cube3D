/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 15:42:45 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/17 11:26:30 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cube.h"

void	hit_loop(t_mlx_info *mlx_info)
{
	t_draw_prop	*draw_prop;

	draw_prop = &mlx_info->draw_prop;
	while (draw_prop->hit == 0)
	{
		if (draw_prop->sideDistX < draw_prop->sideDistY)
		{
			draw_prop->sideDistX += draw_prop->deltaDistX;
			draw_prop->mapX += draw_prop->stepX;
			draw_prop->side = 0;
		}
		else
		{
			draw_prop->sideDistY += draw_prop->deltaDistY;
			draw_prop->mapY += draw_prop->stepY;
			draw_prop->side = 1;
		}
		if (mlx_info->map[draw_prop->mapX][draw_prop->mapY] > 0)
			draw_prop->hit = 1;
	}
}

void	calculate_wall_dist(t_mlx_info *mlx_info)
{
	t_draw_prop	*prop;

	prop = &mlx_info->draw_prop;
	if (prop->side == 0)
		prop->perpWallDist = prop->sideDistX - prop->deltaDistX;
	else
		prop->perpWallDist = prop->sideDistY - prop->deltaDistY;
	prop->lineHeight = (int)(mlx_info->window_height / prop->perpWallDist);
	prop->drawStart = -prop->lineHeight / 2 + mlx_info->window_height / 2;
	if (prop->drawStart < 0)
		prop->drawStart = 0;
	prop->drawEnd = prop->lineHeight / 2 + mlx_info->window_height / 2;
	if (prop->drawEnd >= mlx_info->window_height)
	{
		prop->drawEnd = mlx_info->window_height - 1;
	}
}

void	calculate_wall_tex_x(t_mlx_info *mlx_info)
{
	t_draw_prop	*prop;

	prop = &mlx_info->draw_prop;
	prop->texture_num = mlx_info->map[prop->mapX][prop->mapY] - 1;
	if (prop->side == 0)
	{
		prop->wall_X = mlx_info->unique_prop.posY
			+ prop->perpWallDist * prop->rayDirY;
	}
	else
	{
		prop->wall_X = mlx_info->unique_prop.posX
			+ prop->perpWallDist * prop->rayDirX;
	}
	prop->wall_X -= floor((prop->wall_X));
	prop->texX = (int)(prop->wall_X * (double)mlx_info->unique_prop.texWidth);
	if (prop->side == 0 && prop->rayDirX > 0)
	{
		prop->texX = mlx_info->unique_prop.texWidth - prop->texX - 1;
	}
	if (prop->side == 1 && prop->rayDirY < 0)
	{
		prop->texX = mlx_info->unique_prop.texWidth - prop->texX - 1;
	}
}

static void	add_transperency_to_colour(t_render_vars *vars)
{
	vars->r = vars->color.r & 0xFF;
	vars->g = vars->color.g & 0xFF;
	vars->b = vars->color.b & 0xFF;
	vars->a = vars->color.a & 0xFF;
}

void	render_textures(t_mlx_info *data, int x)
{
	t_render_vars	v;
	t_draw_prop		*prop;

	prop = &data->draw_prop;
	v.step = 1.0 * data->texture_data[prop->texture_num].height
		/ prop->lineHeight;
	v.tex_pos = (prop->drawStart - data->window_height / 2
			+ prop->lineHeight / 2) * v.step;
	v.y = prop->drawStart;
	while (v.y < prop->drawEnd)
	{
		v.tex_pos += v.step;
		if (v.tex_pos - 1 < 0)
			v.tex_pos = 1;
		else if (v.tex_pos - 1 > data->texture_data[prop->texture_num].height)
			v.tex_pos = data->texture_data[prop->texture_num].height - 1;
		v.color = *data->texture_data[prop->texture_num]
			.arr_color[prop->texX][(int)(v.tex_pos) - 1];
		add_transperency_to_colour(&v);
		v.pix = (v.a << 24) + (v.r << 16) + (v.g << 8) + (v.b);
		better_pixel_put(&data->main_img, x, v.y, v.pix);
		v.y++;
	}
}
