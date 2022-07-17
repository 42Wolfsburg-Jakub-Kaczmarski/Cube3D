/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 15:42:45 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/17 13:48:29 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube.h"

void	hit_loop(t_mlx_info *mlx_info)
{
	t_draw_prop	*draw_prop;

	draw_prop = &mlx_info->draw_prop;
	while (draw_prop->hit == 0)
	{
		if (draw_prop->side_dist_x < draw_prop->side_dist_y)
		{
			draw_prop->side_dist_x += draw_prop->delta_dist_x;
			draw_prop->map_x += draw_prop->step_x;
			draw_prop->side = 0;
		}
		else
		{
			draw_prop->side_dist_y += draw_prop->delta_dist_y;
			draw_prop->map_y += draw_prop->step_y;
			draw_prop->side = 1;
		}
		if (mlx_info->map[draw_prop->map_x][draw_prop->map_y] > 0)
			draw_prop->hit = 1;
	}
}

void	calculate_wall_dist(t_mlx_info *mlx_info)
{
	t_draw_prop	*prop;

	prop = &mlx_info->draw_prop;
	if (prop->side == 0)
		prop->perp_wall_dist = prop->side_dist_x - prop->delta_dist_x;
	else
		prop->perp_wall_dist = prop->side_dist_y - prop->delta_dist_y;
	prop->line_height = (int)(mlx_info->window_height / prop->perp_wall_dist);
	prop->draw_start = -prop->line_height / 2 + mlx_info->window_height / 2;
	if (prop->draw_start < 0)
		prop->draw_start = 0;
	prop->draw_end = prop->line_height / 2 + mlx_info->window_height / 2;
	if (prop->draw_end >= mlx_info->window_height)
	{
		prop->draw_end = mlx_info->window_height - 1;
	}
}

void	calculate_wall_tex_x(t_mlx_info *mlx_info)
{
	t_draw_prop	*prop;

	prop = &mlx_info->draw_prop;
	prop->texture_num = mlx_info->map[prop->map_x][prop->map_y] - 1;
	if (prop->side == 0)
	{
		prop->wall_x = mlx_info->unique_prop.pos_y
			+ prop->perp_wall_dist * prop->ray_dir_y;
	}
	else
	{
		prop->wall_x = mlx_info->unique_prop.pos_x
			+ prop->perp_wall_dist * prop->ray_dir_x;
	}
	prop->wall_x -= floor((prop->wall_x));
	prop->tex_x = (int)(prop->wall_x * (double)mlx_info->unique_prop.tex_width);
	if (prop->side == 0 && prop->ray_dir_x > 0)
	{
		prop->tex_x = mlx_info->unique_prop.tex_width - prop->tex_x - 1;
	}
	if (prop->side == 1 && prop->ray_dir_y < 0)
	{
		prop->tex_x = mlx_info->unique_prop.tex_width - prop->tex_x - 1;
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
		/ prop->line_height;
	v.tex_pos = (prop->draw_start - data->window_height / 2
			+ prop->line_height / 2) * v.step;
	v.y = prop->draw_start;
	while (v.y < prop->draw_end)
	{
		v.tex_pos += v.step;
		if (v.tex_pos - 1 < 0)
			v.tex_pos = 1;
		else if (v.tex_pos - 1 > data->texture_data[prop->texture_num].height)
			v.tex_pos = data->texture_data[prop->texture_num].height - 1;
		v.color = *data->texture_data[prop->texture_num]
			.arr_color[prop->tex_x][(int)(v.tex_pos) - 1];
		add_transperency_to_colour(&v);
		v.pix = (v.a << 24) + (v.r << 16) + (v.g << 8) + (v.b);
		better_pixel_put(&data->main_img, x, v.y, v.pix);
		v.y++;
	}
}
