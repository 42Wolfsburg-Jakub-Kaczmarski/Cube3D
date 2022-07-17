/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:54:46 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/17 13:48:07 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube.h"

void	key_right_arr(t_mlx_info *mlx_info)
{
	double		old_dir_x;
	double		old_plane_x;
	t_uniq_prop	*unique_prop;

	unique_prop = &mlx_info->unique_prop;
	old_dir_x = unique_prop->dir_x;
	unique_prop->dir_x = unique_prop->dir_x * cos(-unique_prop->rot_speed)
		- unique_prop->dir_y * sin(-unique_prop->rot_speed);
	unique_prop->dir_y = old_dir_x * sin(-unique_prop->rot_speed)
		+ unique_prop->dir_y * cos(-unique_prop->rot_speed);
	old_plane_x = unique_prop->plane_x;
	unique_prop->plane_x = unique_prop->plane_x * cos(-unique_prop->rot_speed)
		- unique_prop->plane_y * sin(-unique_prop->rot_speed);
	unique_prop->plane_y = old_plane_x * sin(-unique_prop->rot_speed)
		+ unique_prop->plane_y * cos(-unique_prop->rot_speed);
}

void	key_left_arr(t_mlx_info *mlx_info)
{
	double		old_dir_x;
	double		old_plane_x;
	t_uniq_prop	*unique_prop;

	unique_prop = &mlx_info->unique_prop;
	old_dir_x = unique_prop->dir_x;
	unique_prop->dir_x = unique_prop->dir_x * cos(unique_prop->rot_speed)
		- unique_prop->dir_y * sin(unique_prop->rot_speed);
	unique_prop->dir_y = old_dir_x * sin(unique_prop->rot_speed)
		+ unique_prop->dir_y * cos(unique_prop->rot_speed);
	old_plane_x = unique_prop->plane_x;
	unique_prop->plane_x = unique_prop->plane_x * cos(unique_prop->rot_speed)
		- unique_prop->plane_y * sin(unique_prop->rot_speed);
	unique_prop->plane_y = old_plane_x * sin(unique_prop->rot_speed)
		+ unique_prop->plane_y * cos(unique_prop->rot_speed);
}
