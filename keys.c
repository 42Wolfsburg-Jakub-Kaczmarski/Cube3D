/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 21:14:56 by kmilchev          #+#    #+#             */
/*   Updated: 2022/06/30 14:45:22 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube.h"

void move(t_mlx *data)
{
	data->px += data->pdx;
	data->py += data->pdy;
}

void key_w(t_mlx *data)
{
	data->pdx = cos(data->dir) * MOVEMENT_SPEED;
	data->pdy = sin(data->dir) * MOVEMENT_SPEED;
	
	if (check_movement(data))
		return ;
	move(data);
}

void key_s(t_mlx *data)
{
	data->pdx = -(cos(data->dir) * MOVEMENT_SPEED);
	data->pdy = -(sin(data->dir) * MOVEMENT_SPEED);
	if (check_movement(data))
		return ;
	move(data);
}

void key_a(t_mlx *data)
{
	double temp_dir;
	temp_dir = data->dir - (PI / 2); 
	if (temp_dir >= 2 * PI)
		temp_dir -= 2 * PI;
	
	data->pdx = cos(temp_dir) * MOVEMENT_SPEED;
	data->pdy = sin(temp_dir) * MOVEMENT_SPEED;
	if (check_movement(data))
		return ;
	move(data);
}

void key_d(t_mlx *data)
{
	double temp_dir;
	temp_dir = PI / 2 + data->dir; 
	if (temp_dir <= 0)
		temp_dir += 2 * PI;
	data->pdx = cos(temp_dir) * MOVEMENT_SPEED;
	data->pdy = sin(temp_dir) * MOVEMENT_SPEED;
	if (check_movement(data))
		return ;
	move(data);
}

void key_left_arrow(t_mlx *data)
{
	data->dir -= ROTATION_SPEED;
    if (data->dir < 0)
        data->dir += 2 * PI;
	draw_wand(data);
	draw_rays(data);
}

void key_right_arrow(t_mlx *data)
{
	data->dir += ROTATION_SPEED;
    if (data->dir > 2 * PI)
      data->dir -= 2 * PI;
	draw_wand(data);
	draw_rays(data);
}