/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 21:14:56 by kmilchev          #+#    #+#             */
/*   Updated: 2022/06/28 22:08:00 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube.h"

void key_w(t_mlx *data)
{
	data->px += cos(data->dir) * MOVEMENT_SPEED;
	data->py += sin(data->dir) * MOVEMENT_SPEED;
	data->wx += cos(data->dir) * MOVEMENT_SPEED;
	data->wy += sin(data->dir) * MOVEMENT_SPEED;
	mlx_delete_image(data->mlx, data->img_arr[PLAYER]);
	draw_player(data);
}

void key_s(t_mlx *data)
{
	data->px -= cos(data->dir) * MOVEMENT_SPEED;
	data->py -= sin(data->dir) * MOVEMENT_SPEED;
	data->wx -= cos(data->dir) * MOVEMENT_SPEED;
	data->wy -= sin(data->dir) * MOVEMENT_SPEED;
	mlx_delete_image(data->mlx, data->img_arr[PLAYER]);
	draw_player(data);
}

void key_a(t_mlx *data)
{
	double temp_dir;
	temp_dir = data->dir - (PI / 2); 
	if (temp_dir >= 2 * PI)
		temp_dir -= 2 * PI;
	data->px += cos(temp_dir) * MOVEMENT_SPEED;
	data->py += sin(temp_dir) * MOVEMENT_SPEED;
	data->wx += cos(temp_dir) * MOVEMENT_SPEED;
	data->wy += sin(temp_dir) * MOVEMENT_SPEED;
	mlx_delete_image(data->mlx, data->img_arr[PLAYER]);
	draw_player(data);
}

void key_d(t_mlx *data)
{
	double temp_dir;
	temp_dir = PI / 2 + data->dir; 
	if (temp_dir <= 0)
		temp_dir += 2 * PI;
	data->px += cos(temp_dir) * MOVEMENT_SPEED;
	data->py += sin(temp_dir) * MOVEMENT_SPEED;
	data->wx += cos(temp_dir) * MOVEMENT_SPEED;
	data->wy += sin(temp_dir) * MOVEMENT_SPEED;
	mlx_delete_image(data->mlx, data->img_arr[PLAYER]);
	draw_player(data);
}

void key_left_arrow(t_mlx *data)
{
	data->dir -= ROTATION_SPEED;
    if (data->dir <= 0)
        data->dir += 2 * PI;
	draw_wand(data);
}

void key_right_arrow(t_mlx *data)
{
	data->dir += ROTATION_SPEED;
    if (data->dir >= 2 * PI)
      data->dir -= 2 * PI;
	draw_wand(data);
}