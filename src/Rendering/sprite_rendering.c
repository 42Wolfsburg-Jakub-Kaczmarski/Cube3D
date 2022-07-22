/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_rendering.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 21:09:50 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/22 21:13:32 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube.h"



void    run_bubble_sort(t_mlx_info *mlx_info, t_pair *arr)
{
    int i;
    t_pair temp;

    i = 0;
	while(i < mlx_info->sprites->sprite_count - 1)
	{
		int j = 0;
		while(j < mlx_info->sprites->sprite_count - i -1)
		{
			if(arr[j].first + arr[j].second > arr[j + 1].first + arr[j + 1].second)
			{
				temp.first = arr[j + 1].first;
				temp.second = arr[j + 1].second;
				arr[j + 1].first = arr[j].first;
				arr[j + 1].second = arr[j].second;
				arr[j].first = temp.first;
				arr[j].second = temp.second;
			}
			j++;
		}
		i++;
	}
}

void	sorting_sprite_set(t_mlx_info *mlx_info)
{
	t_pair *arr = ft_calloc(mlx_info->sprites->sprite_count,sizeof(t_pair));
	int i = 0;
	while(i < mlx_info->sprites->sprite_count)
	{
		arr[i].first = mlx_info->sprites->sprite_distance[i];
		arr[i].second = mlx_info->sprites->sprite_order[i];
		i++;
	}
	run_bubble_sort(mlx_info, arr);
    i = 0;
	while(i < mlx_info->sprites->sprite_count)
	{
		mlx_info->sprites->sprite_distance[i] = arr[mlx_info->sprites->sprite_count - i - 1].first;
		mlx_info->sprites->sprite_order[i] = arr[mlx_info->sprites->sprite_count - i - 1].second;
		i++;
	}
}

void	sort_sprites(t_mlx_info	*mlx_info)
{
	int i = 0;
	while(i < mlx_info->sprites->sprite_count)
	{
		mlx_info->sprites->sprite_order[i] = i;
		mlx_info->sprites->sprite_distance[i] = ((mlx_info->unique_prop.pos_x - mlx_info->sprites->sprite_arr[i].x) * (mlx_info->unique_prop.pos_x - mlx_info->sprites->sprite_arr[i].x)  + (mlx_info->unique_prop.pos_y - mlx_info->sprites->sprite_arr[i].y) * (mlx_info->unique_prop.pos_y - mlx_info->sprites->sprite_arr[i].y));
		i++;
	}
	sorting_sprite_set(mlx_info);
}

void	calc_sprite_height(t_mlx_info *mlx_info)
{
	mlx_info->sprites->spriteHeight = abs((int)(mlx_info->window_height / (mlx_info->sprites->transformY))) / mlx_info->sprites->vDiv;
	
	mlx_info->sprites->DrawStartY = -mlx_info->sprites->spriteHeight / 2 + mlx_info->window_height / 2 + mlx_info->sprites->move_screen;
	if(mlx_info->sprites->DrawStartY < 0)
	{
		mlx_info->sprites->DrawStartY = 0;
	}
	mlx_info->sprites->DrawEndY = mlx_info->sprites->spriteHeight / 2 + mlx_info->window_height / 2 + mlx_info->sprites->move_screen;
	if(mlx_info->sprites->DrawEndY >= mlx_info->window_width)
	{
		mlx_info->sprites->DrawEndY = mlx_info->window_height - 1;		
	}
}

void	calculate_sprite_width(t_mlx_info *mlx_info)
{
	mlx_info->sprites->spriteWidth = abs((int)(mlx_info->window_height / mlx_info->sprites->transformY)) / mlx_info->sprites->uDiv;
	mlx_info->sprites->drawStartX = -mlx_info->sprites->spriteWidth / 2 + mlx_info->sprites->spriteScreenX;
	if(mlx_info->sprites->drawStartX < 0)
		mlx_info->sprites->drawStartX = 0;

	mlx_info->sprites->drawEndX = mlx_info->sprites->spriteWidth / 2 + mlx_info->sprites->spriteScreenX;
	if(mlx_info->sprites->drawEndX >= mlx_info->window_width)
		mlx_info->sprites->drawEndX  = mlx_info->window_width - 1;
}