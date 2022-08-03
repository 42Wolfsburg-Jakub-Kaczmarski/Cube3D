/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 15:39:16 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/08/03 14:31:06 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube.h"

void	init_img(t_mlx_info *mlx_info)
{
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

int	tex_x_calculation(int stripe1, t_mlx_info *mlx_info, int i)
{
	int	result;

	result = (256 * (stripe1 - (-mlx_info->sprites->sprite_width / 2
					+ mlx_info->sprites->sprite_screen_x))
			* mlx_info->texture_data[i].width
			/ mlx_info->sprites->sprite_width) / 256;
	return (result);
}

int	tex_y_calculation(t_sprite_loop	l, t_mlx_info *mlx_info, int i)
{
	int	result;

	result = ((l.d * mlx_info->texture_data[i].height)
			/ mlx_info->sprites->sprite_height) / 256;
	return (result);
}

int	d_calculation(t_sprite_loop	l, t_mlx_info *mlx_info)
{
	int	result;

	result = (l.y - mlx_info->sprites->move_screen) * 256
		- mlx_info->window_height * 128
		+ mlx_info->sprites->sprite_height * 128;
	return (result);
}

bool	check_values(t_mlx_info *mlx_info, t_sprite_loop	l)
{
	t_sprite_data	*sprites;

	sprites = mlx_info->sprites;
	return (sprites->transform_y > 0
		&& l.stripe > 0
		&& l.stripe < mlx_info->window_width
		&& sprites->transform_y < sprites->z_buff[l.stripe]);
}

void	sprite_loop_ctd(t_mlx_info	*m, t_sprite_loop	*l,
	int i, t_render_vars	*v)
{
	while (l->y < m->sprites->draw_end_y)
	{
		l->d = d_calculation(*l, m);
		l->tex_y = tex_y_calculation(*l, m, i);
		v->color = *m->texture_data[i].arr_color[l->tex_x][l->tex_y];
		add_transperency_to_colour(v);
		v->pix = (v->a << 24) + (v->r << 16) + (v->g << 8) + (v->b);
		if (l->y >= m->window_height || l->y < 0)
			l->y++;
		else if ((v->pix != PIX1 && v->pix != PIX2 && v->pix != PIX3))
			better_pixel_put(&m->main_img, l->stripe, l->y, v->pix);
		l->y++;
	}
}

void	sprite_loop(t_mlx_info *m, int i)
{
	t_render_vars	v;
	t_sprite_loop	l;

	l.stripe = m->sprites->draw_start_x;
	while (l.stripe < m->sprites->draw_end_x)
	{
		l.tex_x = tex_x_calculation(l.stripe, m, i);
		if (check_values(m, l))
		{
			l.y = m->sprites->draw_start_y;
			sprite_loop_ctd(m, &l, i, &v);
		}
		l.stripe++;
	}
}

void	sprite_init_loop(t_mlx_info	*mlx_info, int i)
{
	t_sprite_data	*s;
	double			tmp;

	s = mlx_info->sprites;
	s->sprite_x = s->sprite_arr[s->sprite_order[i]].x
		- mlx_info->unique_prop.pos_x;
	s->sprite_y = s->sprite_arr[s->sprite_order[i]].y
		- mlx_info->unique_prop.pos_y;
	s->inv_det = 1.0 / (mlx_info->unique_prop.plane_x
			* mlx_info->unique_prop.dir_y
			- mlx_info->unique_prop.dir_x * mlx_info->unique_prop.plane_y);
	s->transform_x = s->inv_det * (mlx_info->unique_prop.dir_y * s->sprite_x
			- mlx_info->unique_prop.dir_x * s->sprite_y);
	s->transform_y = s->inv_det * (-mlx_info->unique_prop.plane_y * s->sprite_x
			+ mlx_info->unique_prop.plane_x * s->sprite_y);
	tmp = s->transform_x / s->transform_y;
	s->sprite_screen_x = (int)((mlx_info->window_width / 2) * (1 + tmp));
	s->u_div = 1;
	s->v_div = 1;
	s->v_move = 0.00;
	s->move_screen = (int)(s->v_move / s->transform_y);
	calc_sprite_height(mlx_info);
	calculate_sprite_width(mlx_info);
	sprite_loop(mlx_info, s->sprite_arr[s->sprite_order[i]].tex_num);
}

void	sprite_casting(t_mlx_info *mlx_info)
{
	int	i;

	i = 0;
	sort_sprites(mlx_info);
	while (i < mlx_info->sprites->sprite_count)
	{
		sprite_init_loop(mlx_info, i);
		i++;
	}
}

void	render(t_mlx_info *m)
{
	int	x;
	int	w;

	x = 0;
	w = m->window_width;
	init_img(m);
	floor_casting(m);
	while (x < w)
	{
		init_for_drawing(m, x, w);
		check_side_xy(m);
		hit_loop(m);
		calculate_wall_dist(m);
		calculate_wall_tex_x(m);
		get_which_tex(m);
		render_textures(m, x);
		m->sprites->z_buff[x] = m->draw_prop.perp_wall_dist;
		x++;
	}
	sprite_casting(m);
	mlx_put_image_to_window(
		m->mlx, m->main_win, m->main_img.img, 0, 0);
	mlx_put_image_to_window(m->mlx, m->main_win, m->mlx_imgs[9],
		m->window_width / 2 - m->texture_data[9].width / 2,
		m->window_height - m->texture_data[9].height);
}
