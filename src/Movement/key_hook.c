/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:53:02 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/18 18:36:29 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube.h"

int	key_hook(int keycode, void *mlx)
{
	t_mlx_info	*mlx_info;

	mlx_info = (t_mlx_info *)mlx;
	if (keycode == 13)
		key_w_hook(mlx_info);
	if (keycode == 1)
		key_s(mlx_info);
	if (keycode == 0)
		key_a(mlx_info);
	if (keycode == 2)
		key_d(mlx_info);
	if (keycode == 124)
		key_right_arr(mlx_info, 1);
	if (keycode == 123)
		key_left_arr(mlx_info, 1);
	if (keycode == 53)
	{
		mlx_destroy_window(mlx_info->mlx, mlx_info->main_win);
		exit(1);
	}
	// else
		// ft_mouse_tracker(mlx_info->main_win);
	mlx_clear_window(mlx_info->mlx, mlx_info->main_win);
	render(mlx_info);
	return (0);
}
