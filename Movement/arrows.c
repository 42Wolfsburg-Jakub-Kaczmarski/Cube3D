/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:54:46 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/17 12:34:42 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cube.h"

void	key_right_arr(t_mlx_info *mlx_info)
{
	double		old_dir_x;
	double		old_plane_x;
	t_uniq_prop	*unique_prop;

	unique_prop = &mlx_info->unique_prop;
	old_dir_x = unique_prop->dirX;
	unique_prop->dirX = unique_prop->dirX * cos(-unique_prop->rotSpeed)
		- unique_prop->dirY * sin(-unique_prop->rotSpeed);
	unique_prop->dirY = old_dir_x * sin(-unique_prop->rotSpeed)
		+ unique_prop->dirY * cos(-unique_prop->rotSpeed);
	old_plane_x = unique_prop->planeX;
	unique_prop->planeX = unique_prop->planeX * cos(-unique_prop->rotSpeed)
		- unique_prop->planeY * sin(-unique_prop->rotSpeed);
	unique_prop->planeY = old_plane_x * sin(-unique_prop->rotSpeed)
		+ unique_prop->planeY * cos(-unique_prop->rotSpeed);
}

void	key_left_arr(t_mlx_info *mlx_info)
{
	double		old_dir_x;
	double		old_plane_x;
	t_uniq_prop	*unique_prop;

	unique_prop = &mlx_info->unique_prop;
	old_dir_x = unique_prop->dirX;
	unique_prop->dirX = unique_prop->dirX * cos(unique_prop->rotSpeed)
		- unique_prop->dirY * sin(unique_prop->rotSpeed);
	unique_prop->dirY = old_dir_x * sin(unique_prop->rotSpeed)
		+ unique_prop->dirY * cos(unique_prop->rotSpeed);
	old_plane_x = unique_prop->planeX;
	unique_prop->planeX = unique_prop->planeX * cos(unique_prop->rotSpeed)
		- unique_prop->planeY * sin(unique_prop->rotSpeed);
	unique_prop->planeY = old_plane_x * sin(unique_prop->rotSpeed)
		+ unique_prop->planeY * cos(unique_prop->rotSpeed);
}
