// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   keys.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/06/28 21:14:56 by kmilchev          #+#    #+#             */
// /*   Updated: 2022/06/28 23:24:46 by kmilchev         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../../includes/Cube.h"

void key_w(t_mlx *big_struct)
{
	t_ray_casting *data;

	data = &big_struct->data;
	if (worldMap[(int)(data->posX + data->dirX * MOVEMENT_SPEED)][(int)(data->posY )] == false)
	{
		data->posX += data->dirX * MOVEMENT_SPEED;
	}
	if (worldMap[(int)(data->posX)][(int)(data->posY + data->dirY * MOVEMENT_SPEED)] == false)
	{	
		data->posY += data->dirY * MOVEMENT_SPEED;
	}
}

void key_s(t_mlx *big_struct)
{
	t_ray_casting *data;

	data = &big_struct->data;
	if (worldMap[(int)(data->posX - data->dirX * MOVEMENT_SPEED)][(int)(data->posY)] == false)
	{
		data->posX -= data->dirX * MOVEMENT_SPEED;
	}
	if (worldMap[(int)(data->posX)][(int)(data->posY - data->dirY * MOVEMENT_SPEED)] == false)
	{	
		data->posY -= data->dirY * MOVEMENT_SPEED;
	}
}

void key_d(t_mlx *big_struct)
{
	t_ray_casting *data;

	data = &big_struct->data;
	if (worldMap[(int)(data->posX + data->plane_X * MOVEMENT_SPEED)][(int)(data->posY )] == false)
	{
		data->posX += data->plane_X * MOVEMENT_SPEED;
	}
	if (worldMap[(int)(data->posX)][(int)(data->posY + data->plane_Y * MOVEMENT_SPEED)] == false)
	{	
		data->posY += data->plane_Y * MOVEMENT_SPEED;
	}
}

void key_a(t_mlx *big_struct)
{
	t_ray_casting *data;

	data = &big_struct->data;
	if (worldMap[(int)(data->posX - data->plane_X * MOVEMENT_SPEED)][(int)(data->posY)] == false)
	{
		data->posX -= data->plane_X * MOVEMENT_SPEED;
	}
	if (worldMap[(int)(data->posX)][(int)(data->posY - data->plane_Y * MOVEMENT_SPEED)] == false)
	{	
		data->posY -= data->plane_Y * MOVEMENT_SPEED;
	}
}

void key_left_arrow(t_mlx *big_struct)
{
	t_ray_casting *data;
	double	old_dir_X;
	double old_plane_X;
	
	data = &big_struct->data;
	old_dir_X = data->dirX;
	old_plane_X = data->plane_X;
	data->dirX = data->dirX * cos(ROTATION_SPEED) - data->dirY * sin(ROTATION_SPEED);
	data->dirY = old_dir_X * sin(ROTATION_SPEED) + data->dirY * cos(ROTATION_SPEED);
	data->plane_X = data->plane_X * cos(ROTATION_SPEED) - data->plane_Y * sin(ROTATION_SPEED);
	data->plane_Y = old_plane_X * sin(ROTATION_SPEED) + data->plane_Y * cos(ROTATION_SPEED);
	
}

void key_right_arrow(t_mlx *big_struct)
{
	t_ray_casting *data;
	double	old_dir_X;
	double old_plane_X;
	
	data = &big_struct->data;
	old_dir_X = data->dirX;
	old_plane_X = data->plane_X;
	data->dirX = data->dirX * cos(-ROTATION_SPEED) - data->dirY * sin(-ROTATION_SPEED);
	data->dirY = old_dir_X * sin(-ROTATION_SPEED) + data->dirY * cos(-ROTATION_SPEED);
	data->plane_X = data->plane_X * cos(-ROTATION_SPEED) - data->plane_Y * sin(-ROTATION_SPEED);
	data->plane_Y = old_plane_X * sin(-ROTATION_SPEED) + data->plane_Y * cos(-ROTATION_SPEED);
}
