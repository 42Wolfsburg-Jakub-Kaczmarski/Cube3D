/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_rendering.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 21:09:50 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/08/03 14:38:56 by kmilchev         ###   ########.fr       */
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
	free(arr);
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
	mlx_info->sprites->sprite_height = abs((int)(mlx_info->window_height / (mlx_info->sprites->transform_y))) / mlx_info->sprites->v_div;
	
	mlx_info->sprites->draw_start_y = -mlx_info->sprites->sprite_height / 2 + mlx_info->window_height / 2 + mlx_info->sprites->move_screen;
	if(mlx_info->sprites->draw_start_y < 0)
	{
		mlx_info->sprites->draw_start_y = 0;
	}
	mlx_info->sprites->draw_end_y = mlx_info->sprites->sprite_height / 2 + mlx_info->window_height / 2 + mlx_info->sprites->move_screen;
	if(mlx_info->sprites->draw_end_y >= mlx_info->window_width)
	{
		mlx_info->sprites->draw_end_y = mlx_info->window_height - 1;		
	}
}

void	calculate_sprite_width(t_mlx_info *mlx_info)
{
	mlx_info->sprites->sprite_width = abs((int)(mlx_info->window_height / mlx_info->sprites->transform_y)) / mlx_info->sprites->u_div;
	mlx_info->sprites->draw_start_x = -mlx_info->sprites->sprite_width / 2 + mlx_info->sprites->sprite_screen_x;
	if(mlx_info->sprites->draw_start_x < 0)
		mlx_info->sprites->draw_start_x = 0;

	mlx_info->sprites->draw_end_x = mlx_info->sprites->sprite_width / 2 + mlx_info->sprites->sprite_screen_x;
	if(mlx_info->sprites->draw_end_x >= mlx_info->window_width)
		mlx_info->sprites->draw_end_x  = mlx_info->window_width - 1;
}