/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_casting_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:45:54 by kmilchev          #+#    #+#             */
/*   Updated: 2022/08/10 17:23:38 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube.h"

int	tex_x_calculation(int stripe1, t_mlx_info *mlx_info, int i)
{
	int	result;

	if (mlx_info->sprites->sprite_width == 0)
		result = 1;
	else
		result = (256 * (stripe1 - (-mlx_info->sprites->sprite_width / 2
						+ mlx_info->sprites->sprite_screen_x))
				* mlx_info->texture_data[i].width
				/ mlx_info->sprites->sprite_width) / 256;
	return (result);
}

int	tex_y_calculation(t_sprite_loop	l, t_mlx_info *mlx_info, int i)
{
	int	result;

	if (mlx_info->sprites->sprite_height == 0)
	{
		result = 1;
	}
	else
		result = ((l.d * mlx_info->texture_data[i].height)
				/ mlx_info->sprites->sprite_height) / 256;
	return (result);
}

int	d_calculation(t_sprite_loop	l, t_mlx_info *mlx_info)
{
	int	result;

	result = (l.y - mlx_info->sprites->move_screen) * 256
		- mlx_info->window_height * 128
		+ mlx_info->sprites->sprite_height * 128;
	return (result);
}

bool	check_values(t_mlx_info *mlx_info, t_sprite_loop	l)
{
	t_sprite_data	*sprites;

	sprites = mlx_info->sprites;
	return (sprites->transform_y > 0
		&& l.stripe > 0
		&& l.stripe < mlx_info->window_width
		&& sprites->transform_y < sprites->z_buff[l.stripe]);
}
