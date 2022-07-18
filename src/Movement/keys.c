/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:43:05 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/18 13:16:32 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube.h"
#include "../../src/input_validation_and_map_creation/map_validation.h"

void	key_w_hook(t_mlx_info *mlx_info)
{
	t_uniq_prop	*m;
	int			map_x0;
	int			map_y0;

	m = &mlx_info->unique_prop;
	map_x0 = m->pos_x + (m->dir_x * (m->move_speed));
	map_y0 = m->pos_y + (m->dir_y * (m->move_speed));
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
	map_x0 = m->pos_x - m->dir_x * m->move_speed;
	map_y0 = m->pos_y - m->dir_y * m->move_speed;
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

	m = &mlx_info->unique_prop;
	map_x0 = m->pos_x - m->plane_x * m->move_speed;
	map_y0 = m->pos_y - m->plane_y * m->move_speed;
	if (mlx_info->map[map_x0][map_y0] != 1)
	{
		m->pos_x -= m->plane_x * m->move_speed;
		m->pos_y -= m->plane_y * m->move_speed;
	}
}

void	key_d(t_mlx_info *mlx_info)
{
	t_uniq_prop	*m;
	int			map_x0;
	int			map_y0;

	m = &mlx_info->unique_prop;
	map_x0 = m->pos_x + m->plane_x * m->move_speed;
	map_y0 = m->pos_y + m->plane_y * m->move_speed;
	if (mlx_info->map[map_x0][map_y0] != 1)
	{
		m->pos_x += m->plane_x * m->move_speed;
		m->pos_y += m->plane_y * m->move_speed;
	}
}
