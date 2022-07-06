/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 10:42:55 by kmilchev          #+#    #+#             */
/*   Updated: 2022/07/06 22:03:29 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Cube.h"

///INITIALISATIONS
void ray_init(t_ray_casting *data, int i)
{
	data->cameraX = 2 * i / (double)screenWidth - 1;
	data->rayDirX = data->dirX + data->plane_X * data->cameraX;
	data->rayDirY = data->dirY + data->plane_Y * data->cameraX;
	data->mapX = (int)(data->posX);
	data->mapY = (int)(data->posY);
	if(data->rayDirX == 0)
		data->delta_dist_X = 1e30;//very big number to avoid division by 0
	else
		data->delta_dist_X = fabs(1 / data->rayDirX); //it was the fabs that was missing for me
	if (data->rayDirY == 0)
		data->delta_dist_Y = 1e30;
	else
		data->delta_dist_Y = fabs(1/ data->rayDirY);
	data->hit = false;
}

//calculate step and initial sideDist
void calculate_step(t_ray_casting *data)
{
	if (data->rayDirX < 0)
	{
		data->stepX = -1;
		data->side_dist_X = (data->posX - data->mapX) * data->delta_dist_X;
	}
	else
	{
		data->stepX = 1;
		data->side_dist_X = (data->mapX + 1.0 - data->posX) * data->delta_dist_X;
	}
	if (data->rayDirY < 0)
	{
		data->stepY = -1;
		data->side_dist_Y = (data->posY - data->mapY) * data->delta_dist_Y;
	}
	else
	{
		data->stepY = 1;
		data->side_dist_Y = (data->mapY + 1.0 - data->posY) * data->delta_dist_Y;
	}
}

////DDA
void check_if_hit(t_ray_casting *data)
{
	while(data->hit == false)
	{
		if (data->side_dist_X < data->side_dist_Y)
		{
			data->side_dist_X += data->delta_dist_X;
			data->mapX += data->stepX;
			data->side = 0;
		}
		else
		{
			data->side_dist_Y += data->delta_dist_Y;
			data->mapY += data->stepY;
			data->side = 1;
		}
		if (worldMap[data->mapX][data->mapY] == 1) //char in our case, not int
			data->hit = true; // or just break
	}
}

//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
void calculate_ray_len(t_ray_casting *data)
{
	if (data->side == 0)
		data->perp_wall_dist = data->side_dist_X - data->delta_dist_X;
	else
		data->perp_wall_dist = data->side_dist_Y - data->delta_dist_Y;
}

//Calculate height of line to draw on screen
void get_line_start_end_points(t_ray_casting *data)
{
	data->line_height = (int)(screenHeight / data->perp_wall_dist); //maybe no int
	data->draw_start = -(data->line_height) / 2 + screenHeight / 2;
	if (data->draw_start < 0)
		data->draw_start = 0;
	data->draw_end = data->line_height / 2 + screenHeight / 2;
	if (data->draw_end >= screenHeight)
		data->draw_end = screenHeight - 1;
}