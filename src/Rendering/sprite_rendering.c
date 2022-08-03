/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_rendering.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 21:09:50 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/08/03 15:25:43 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube.h"

void	run_bubble_sort(t_mlx_info *mlx_info, t_pair *arr)
{
	int		i;
	int		j;
	t_pair	temp;

	i = 0;
	while (i < mlx_info->sprites->sprite_count - 1)
	{
		j = 0;
		while (j < mlx_info->sprites->sprite_count - i -1)
		{
			if (arr[j].first + arr[j].second
				> arr[j + 1].first + arr[j + 1].second)
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
	t_pair			*arr;
	int				i;
	t_sprite_data	*s;

	s = mlx_info->sprites;
	i = 0;
	arr = ft_calloc(s->sprite_count, sizeof(t_pair));
	while (i < s->sprite_count)
	{
		arr[i].first = s->sprite_distance[i];
		arr[i].second = s->sprite_order[i];
		i++;
	}
	run_bubble_sort(mlx_info, arr);
	i = 0;
	while (i < s->sprite_count)
	{
		s->sprite_distance[i] = arr[s->sprite_count - i - 1].first;
		s->sprite_order[i] = arr[s->sprite_count - i - 1].second;
		i++;
	}
	free(arr);
}

void	sort_sprites(t_mlx_info	*m)
{
	int				i;
	t_sprite_data	*s;

	i = 0;
	s = m->sprites;
	while (i < s->sprite_count)
	{
		s->sprite_order[i] = i;
		s->sprite_distance[i] = ((m->unique_prop.pos_x - s->sprite_arr[i].x)
				* (m->unique_prop.pos_x - s->sprite_arr[i].x)
				+ (m->unique_prop.pos_y - s->sprite_arr[i].y)
				* (m->unique_prop.pos_y - s->sprite_arr[i].y));
		i++;
	}
	sorting_sprite_set(m);
}

void	calc_sprite_height(t_mlx_info *mlx_info)
{
	t_sprite_data	*s;

	s = mlx_info->sprites;
	s->sprite_height = abs((int)(mlx_info->window_height
				/ (s->transform_y))) / s->v_div;
	s->draw_start_y = -s->sprite_height / 2 + mlx_info->window_height
		/ 2 + s->move_screen;
	if (s->draw_start_y < 0)
		s->draw_start_y = 0;
	s->draw_end_y = s->sprite_height / 2 + mlx_info->window_height
		/ 2 + s->move_screen;
	if (s->draw_end_y >= mlx_info->window_width)
		s->draw_end_y = mlx_info->window_height - 1;
}

void	calculate_sprite_width(t_mlx_info *mlx_info)
{
	t_sprite_data	*s;

	s = mlx_info->sprites;
	s->sprite_width = abs((int)(mlx_info->window_height / s->transform_y))
		/ s->u_div;
	s->draw_start_x = -s->sprite_width / 2 + s->sprite_screen_x;
	if (s->draw_start_x < 0)
		s->draw_start_x = 0;
	s->draw_end_x = s->sprite_width / 2 + s->sprite_screen_x;
	if (s->draw_end_x >= mlx_info->window_width)
		s->draw_end_x = mlx_info->window_width - 1;
}
