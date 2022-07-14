/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:53:02 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/14 19:01:26 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cube.h"


int	key_hook(int keycode,void *mlx)
{
	t_mlx_info *mlx_info = (t_mlx_info *) mlx;
	if(keycode == 13)
		key_W_hook(mlx_info);
	if (keycode == 1)
		key_S(mlx_info);
	if(keycode == 0)
		key_A(mlx_info);
	if(keycode == 2)
		key_D(mlx_info);
	if(keycode == 124)
		key_right_arr(mlx_info);
	if(keycode == 123)
		key_left_arr(mlx_info);
	if(keycode == 53)
	{
		mlx_destroy_window(mlx_info->mlx, mlx_info->main_win);
		exit(1);
	}
	mlx_clear_window(mlx_info->mlx, mlx_info->main_win);
	render(mlx_info);
	return 0;
}