/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:53:02 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/08/03 12:50:30 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube.h"
#include "../input_validation_and_map_creation/map_validation.h"

int	movement(t_mlx_info *mlx_info)
{
	key_movement(mlx_info);
	mouse_tracker(mlx_info);
	mlx_clear_window(mlx_info->mlx, mlx_info->main_win);
	render(mlx_info);
	return (0);
}

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

int	key_is_pressed(int keycode, void *mlx)
{
	t_mlx_info	*mlx_info;

	mlx_info = (t_mlx_info *)mlx;
	if (keycode == 13)
		mlx_info->keys.w = true;
	if (keycode == 1)
		mlx_info->keys.s = true;
	if (keycode == 0)
		mlx_info->keys.a = true;
	if (keycode == 2)
		mlx_info->keys.d = true;
	if (keycode == 49)
		key_space(mlx_info);
	if (keycode == 124)
		mlx_info->keys.right_arrow = true;
	if (keycode == 123)
		mlx_info->keys.left_arrow = true;
	if (keycode == 53)
	{
		mlx_destroy_window(mlx_info->mlx, mlx_info->main_win);
		kill(mlx_info->pid, SIGKILL);
		exit(1);
	}
	return (0);
}

int	key_is_released(int keycode, void *mlx)
{
	t_mlx_info	*mlx_info;

	mlx_info = (t_mlx_info *)mlx;
	if (keycode == 13)
		mlx_info->keys.w = false;
	if (keycode == 1)
		mlx_info->keys.s = false;
	if (keycode == 0)
		mlx_info->keys.a = false;
	if (keycode == 2)
		mlx_info->keys.d = false;
	if (keycode == 124)
		mlx_info->keys.right_arrow = false;
	if (keycode == 123)
		mlx_info->keys.left_arrow = false;
	return (0);
}

int	key_movement(t_mlx_info *mlx_info)
{
	if (mlx_info->keys.w == true)
		key_w(mlx_info);
	if (mlx_info->keys.s == true)
		key_s(mlx_info);
	if (mlx_info->keys.a == true)
		key_a(mlx_info);
	if (mlx_info->keys.d == true)
		key_d(mlx_info);
	if (mlx_info->keys.right_arrow == true)
		key_right_arr(mlx_info, 1);
	if (mlx_info->keys.left_arrow == true)
		key_left_arr(mlx_info, 1);
	return (0);
}
