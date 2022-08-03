/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_direction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:29:34 by kmilchev          #+#    #+#             */
/*   Updated: 2022/08/03 12:31:20 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube.h"
#include "map_validation.h"

static void	set_direction2(t_mlx_info *mlx_info, char c)
{
	if (c == 'E')
	{
		mlx_info->unique_prop.dir_x = 0;
		mlx_info->unique_prop.dir_y = 1;
		mlx_info->unique_prop.plane_x = 0.66;
		mlx_info->unique_prop.plane_y = 0;
	}
	else if (c == 'S')
	{
		mlx_info->unique_prop.dir_x = 1;
		mlx_info->unique_prop.dir_y = 0;
		mlx_info->unique_prop.plane_x = 0;
		mlx_info->unique_prop.plane_y = -0.66;
	}
}

void	set_direction(t_mlx_info *mlx_info, char c)
{
	if (c == 'N')
	{
		mlx_info->unique_prop.dir_x = -1;
		mlx_info->unique_prop.dir_y = 0;
		mlx_info->unique_prop.plane_x = 0;
		mlx_info->unique_prop.plane_y = 0.66;
	}
	else if (c == 'W')
	{
		mlx_info->unique_prop.dir_x = 0;
		mlx_info->unique_prop.dir_y = -1;
		mlx_info->unique_prop.plane_x = -0.66;
		mlx_info->unique_prop.plane_y = 0;
	}
	set_direction2(mlx_info, c);
}
