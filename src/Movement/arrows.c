/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:54:46 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/19 21:40:10 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/Cube.h"

void	key_right_arr(t_mlx_info *mlx_info, int diff_x)
{
	double		old_dir_x;
	double		old_plane_x;
	double		rotation;
	t_uniq_prop	*unique_prop;

	unique_prop = &mlx_info->unique_prop;
	rotation = unique_prop->rot_speed * diff_x;
	old_dir_x = unique_prop->dir_x;
	unique_prop->dir_x = unique_prop->dir_x * cos(-rotation)
		- unique_prop->dir_y * sin(-rotation);
	unique_prop->dir_y = old_dir_x * sin(-rotation)
		+ unique_prop->dir_y * cos(-rotation);
	old_plane_x = unique_prop->plane_x;
	unique_prop->plane_x = unique_prop->plane_x * cos(-rotation)
		- unique_prop->plane_y * sin(-rotation);
	unique_prop->plane_y = old_plane_x * sin(-rotation)
		+ unique_prop->plane_y * cos(-rotation);
}

void	key_left_arr(t_mlx_info *mlx_info, int diff_x)
{
	double		old_dir_x;
	double		old_plane_x;
	double		rotation;
	t_uniq_prop	*unique_prop;

	unique_prop = &mlx_info->unique_prop;
	rotation = unique_prop->rot_speed * diff_x;
	old_dir_x = unique_prop->dir_x;
	unique_prop->dir_x = old_dir_x * cos(rotation)
		- unique_prop->dir_y * sin(rotation);
	unique_prop->dir_y = old_dir_x * sin(rotation)
		+ unique_prop->dir_y * cos(rotation);
	old_plane_x = unique_prop->plane_x;
	unique_prop->plane_x = unique_prop->plane_x * cos(rotation)
		- unique_prop->plane_y * sin(rotation);
	unique_prop->plane_y = old_plane_x * sin(rotation)
		+ unique_prop->plane_y * cos(rotation);
}

int	ft_mouse_tracker(t_mlx_info *mlx_info)
{
	int	x;
	int	y;

	if (mlx_info->mouse == true)
	{
		mlx_mouse_hide(mlx_info->mlx, mlx_info->main_win);
		mlx_mouse_get_pos(mlx_info->main_win, &x, &y);
		if (x > mlx_info->window_width / 2)
		{
			key_right_arr(mlx_info, x - mlx_info->window_width / 2);
			mlx_clear_window(mlx_info->mlx, mlx_info->main_win);
			render(mlx_info);
		}
		else if (x < mlx_info->window_width / 2)
		{
			key_left_arr(mlx_info, mlx_info->window_width / 2 - x);
			mlx_clear_window(mlx_info->mlx, mlx_info->main_win);
			render(mlx_info);
		}
		mlx_mouse_move(mlx_info->main_win, mlx_info->window_width / 2,
			- mlx_info->window_width / 2 - 50);
	}
	else
		mlx_mouse_show();
	return(0);
}
