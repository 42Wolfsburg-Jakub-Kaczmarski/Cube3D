/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:43:05 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/20 23:11:35 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube.h"
#include "../../src/input_validation_and_map_creation/map_validation.h"

void	key_w(t_mlx_info *mlx_info)
{
	t_uniq_prop	*m;
	int			map_x0;
	int			map_y0;

	m = &mlx_info->unique_prop;
	map_x0 = m->pos_x + (m->dir_x * ((m->move_speed + 0)));
	map_y0 = m->pos_y + (m->dir_y * ((m->move_speed + 0)));
	if (mlx_info->map[map_x0][map_y0] != 1)
	{
		m->pos_y += m->dir_y * m->move_speed;
		m->pos_x += m->dir_x * m->move_speed;
	}
}

void	key_s(t_mlx_info *mlx_info)
{
	t_uniq_prop	*m;
	int			map_x0;
	int			map_y0;

	m = &mlx_info->unique_prop;
	map_x0 = m->pos_x - m->dir_x * (m->move_speed + 0);
	map_y0 = m->pos_y - m->dir_y * (m->move_speed + 0);
	if (mlx_info->map[map_x0][map_y0] != 1)
	{
		m->pos_x -= m->dir_x * m->move_speed;
		m->pos_y -= m->dir_y * m->move_speed;
	}
}

void	key_a(t_mlx_info *mlx_info)
{
	t_uniq_prop	*m;
	int			map_x0;
	int			map_y0;
	double tmp;

	m = &mlx_info->unique_prop;
	tmp = m->plane_x * m->plane_x + m->plane_y * m->plane_y;
	tmp = sqrt(tmp);
	map_x0 = m->pos_x - (m->plane_x / tmp) * (m->move_speed + 0);
	map_y0 = m->pos_y - (m->plane_y / tmp) * (m->move_speed + 0);
	if (mlx_info->map[map_x0][map_y0] != 1)
	{
		m->pos_x -= m->plane_x * m->move_speed;
		m->pos_y -= m->plane_y * m->move_speed ;
	}
}

void	key_d(t_mlx_info *mlx_info)
{
	t_uniq_prop	*m;
	int			map_x0;
	int			map_y0;
	double tmp;
	m = &mlx_info->unique_prop;
	tmp = m->plane_x * m->plane_x + m->plane_y * m->plane_y;
	tmp = sqrt(tmp);
	map_x0 = m->pos_x +( m->plane_x / tmp) * (m->move_speed + 0);
	map_y0 = m->pos_y + (m->plane_y / tmp) * (m->move_speed + 0);
	if (mlx_info->map[map_x0][map_y0] != 1)
	{
		m->pos_x += m->plane_x * m->move_speed ;
		m->pos_y += m->plane_y * m->move_speed ;
	}
}

void	key_space(t_mlx_info *mlx_info)
{
	if (mlx_info->mouse == true)
	{
		mlx_mouse_move(mlx_info->main_win, mlx_info->window_width / 2,
			- mlx_info->window_width / 2);
		mlx_info->mouse = false;
	}
	else if (mlx_info->mouse == false)
		mlx_info->mouse = true;
}
