/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:43:05 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/17 17:10:55 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube.h"
#include "../../src/input_validation_and_map_creation/map_validation.h"

void	key_W_hook(t_mlx_info *mlx_info)
{
	t_uniq_prop *m;

	m = &mlx_info->unique_prop;
	
	int map_x0 = m->pos_x + (m->dir_x * (m->move_speed ));
	int map_y0 = m->pos_y + (m->dir_y * (m->move_speed ));
	int map_x1 = m->pos_x + 1 + (m->dir_x * (m->move_speed ));
	int map_y1 = m->pos_y + 1 + (m->dir_y * (m->move_speed ));

	if (mlx_info->map[map_x0][map_y0] != 1 &&
		mlx_info->map[map_x1][map_y1] != 1 &&
		mlx_info->map[map_x0][map_y1] != 1 &&
		mlx_info->map[map_x1][map_y0] != 1)
	{
		m->pos_y += m->dir_y * m->move_speed;
		m->pos_x += m->dir_x * m->move_speed;
	}
}

void	key_S(t_mlx_info *mlx_info)
{
	t_uniq_prop *m;

	m = &mlx_info->unique_prop;
	
	int map_x0 = m->pos_x - m->dir_x * m->move_speed;
	int map_y0 = m->pos_y - m->dir_y * m->move_speed;
	int map_x1 = m->pos_x + 1 - m->dir_x * m->move_speed;
	int map_y1 = m->pos_y + 1 - m->dir_y * m->move_speed;
	
	if (mlx_info->map[map_x0][map_y0] != 1 &&
		mlx_info->map[map_x1][map_y1] != 1 &&
		mlx_info->map[map_x0][map_y1] != 1 &&
		mlx_info->map[map_x1][map_y0] != 1)
	{
		m->pos_x -= m->dir_x * m->move_speed;
		m->pos_y -= m->dir_y * m->move_speed;
	}
}
void	key_A(t_mlx_info *mlx_info)
{
	t_uniq_prop *m;

	m = &mlx_info->unique_prop;
	
	int map_x0 = m->pos_x - m->plane_x * m->move_speed;
	int map_y0 = m->pos_y - m->plane_y * m->move_speed;
	int map_x1 = m->pos_x + 1 - m->plane_x * m->move_speed;
	int map_y1 = m->pos_y + 1 - m->plane_y * m->move_speed;
	
	if (mlx_info->map[map_x0][map_y0] != 1 &&
		mlx_info->map[map_x1][map_y1] != 1 &&
		mlx_info->map[map_x0][map_y1] != 1 &&
		mlx_info->map[map_x1][map_y0] != 1)
	{
		m->pos_x -= m->plane_x * m->move_speed;
		m->pos_y -= m->plane_y * m->move_speed;
	}
}

void	key_D(t_mlx_info *mlx_info)
{
	t_uniq_prop *m;

	m = &mlx_info->unique_prop;
		
	int map_x0 = m->pos_x + m->plane_x * m->move_speed;
	int map_y0 = m->pos_y + m->plane_y * m->move_speed;
	int map_x1 = m->pos_x + 1 + m->plane_x * m->move_speed;
	int map_y1 = m->pos_y + 1 + m->plane_y * m->move_speed;
	
	if (mlx_info->map[map_x0][map_y0] != 1 &&
		mlx_info->map[map_x1][map_y1] != 1 &&
		mlx_info->map[map_x0][map_y1] != 1 &&
		mlx_info->map[map_x1][map_y0] != 1)
	{
		m->pos_x += m->plane_x * m->move_speed;
		m->pos_y += m->plane_y * m->move_speed;
	}
}