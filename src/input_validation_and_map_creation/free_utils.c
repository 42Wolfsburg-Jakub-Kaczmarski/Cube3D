/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:43:28 by kmilchev          #+#    #+#             */
/*   Updated: 2022/08/03 12:49:19 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube.h"

void	free_sprites(t_mlx_info *mlx_info)
{
	if (mlx_info->free_sprites)
	{
		free(mlx_info->sprites_amount);
		free(mlx_info->sprites->sprite_arr);
		free(mlx_info->sprites);
	}
}

void	free_2d_array(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			arr[i] = NULL;
			i++;
		}
		free(arr);
		arr = NULL;
	}
}

void	free_2d_int_array(int **arr, t_mlx_info	*mlx_info)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < mlx_info->map_height)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_2d_safe(char ***arr)
{
	int	i;

	i = 0;
	if (*arr)
	{
		while ((*arr)[i])
		{
			free((*arr)[i]);
			(*arr)[i] = NULL;
			i++;
		}
		free(*arr);
		*arr = NULL;
	}
}
