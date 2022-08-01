/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:43:05 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/08/01 12:56:56 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube.h"
#include "../../src/input_validation_and_map_creation/map_validation.h"

//first check if for diagonal movement
//second check is for wall collision
bool	movement_is_allowed(t_mlx_info *mlx_info, int x1, int y1)
{
	if (mlx_info->map[x1][(int)mlx_info->unique_prop.pos_y] == 1
		&& mlx_info->map[(int)mlx_info->unique_prop.pos_x][y1] == 1)
		return (false);
	else if (mlx_info->map[x1][y1] == 1)
		return (false);
	return (true);
}

void	key_w(t_mlx_info *mlx_info)
{
	t_uniq_prop	*m;
	int			map_x0;
	int			map_y0;

	m = &mlx_info->unique_prop;
	map_x0 = m->pos_x + m->dir_x * m->move_speed;
	map_y0 = m->pos_y + m->dir_y * m->move_speed;
	if (movement_is_allowed(mlx_info, map_x0, map_y0))
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
	if (movement_is_allowed(mlx_info, map_x0, map_y0))
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
	if (movement_is_allowed(mlx_info, map_x0, map_y0))
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

	m = &mlx_info->unique_prop;
	map_x0 = m->pos_x + m->plane_x * m->move_speed;
	map_y0 = m->pos_y + m->plane_y * m->move_speed;
	if (movement_is_allowed(mlx_info, map_x0, map_y0))
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
