/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:53:02 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/21 17:43:45 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube.h"

int	key_hook(int keycode, void *mlx)
{
	t_mlx_info	*mlx_info;

	mlx_info = (t_mlx_info *)mlx;
	if (keycode == 13)
		key_w(mlx_info);
	if (keycode == 49)
		key_space(mlx_info);
	if (keycode == 1)
		key_s(mlx_info);
	if (keycode == 0)
		key_a(mlx_info);
	if (keycode == 2)
		key_d(mlx_info);
	if (keycode == 124)
		key_right_arr(mlx_info, 2);
	if (keycode == 123)
		key_left_arr(mlx_info, 2);
	if (keycode == 53)
	{
		mlx_destroy_window(mlx_info->mlx, mlx_info->main_win);
		kill(mlx_info->pid, SIGKILL);
		exit(1);
	}
	mlx_clear_window(mlx_info->mlx, mlx_info->main_win);
	render(mlx_info);
	return (0);
}
