/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_map_index_exists.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 20:13:33 by kmilchev          #+#    #+#             */
/*   Updated: 2022/07/07 20:57:56 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Cube.h"

//universal but with the others it is easier to read
bool	square_exists(t_mlx *mlx_info, int i, int j)
{
	if ((i > 0 && i < mlx_info->map_height - 1)
		&& (j > 0 && j < ft_strlen(mlx_info->map[i])))
		return (true);
	return (false);
}

bool	square_below_exists(t_mlx *mlx_info, int i, int j)
{
	// printf("FALSE BELOW Idx i = %d", i);
	// printf("FALSE BELOW Idx j = %d", j);
	// printf("Row length = %d\n", ft_strlen(mlx_info->map[i + 1]));
	if ((i + 1 > 0 && i + 1 <= mlx_info->map_height - 1)
		&& (j > 0 && j < ft_strlen(mlx_info->map[i + 1]) - 1))
		return (true);
	// printf("false below\n");
	return (false);
}

bool	square_above_exists(t_mlx *mlx_info, int i, int j)
{
	if ((i - 1 >= 0 && i - 1 <= mlx_info->map_height - 1)
		&& (j < ft_strlen(mlx_info->map[i - 1])))
		return (true);
	// printf("i = %d\n", i - 1);
	// printf("Map-height = %d\n", mlx_info->map_height - 1);
	// printf("j = %d\n", j);
	// if (i > 0)
	// 	printf("Row-length = %zu\n", ft_strlen(mlx_info->map[i - 1]));
	// printf("false above\n");
	return (false);
}

bool	square_left_exists(t_mlx *mlx_info, int i, int j)
{
	if ((i > 0 && i < mlx_info->map_height - 1)
		&& (j - 1 >= 0 && j - 1 <= ft_strlen(mlx_info->map[i - 1]) - 1))
		return (true);
	// printf("i = %d\n", i);
	// printf("Map-height = %d\n", mlx_info->map_height - 1);
	// printf("j = %d\n", j - 1);
	// if (i > 0)
	// 	printf("Row-length = %zu\n", ft_strlen(mlx_info->map[i - 1]));
	// printf("false left\n");
	return (false);
}

bool	square_right_exists(t_mlx *mlx_info, int i, int j)
{
	if ((i > 0 && i < mlx_info->map_height - 1)
		&& (j + 1 > 0 && j + 1 < ft_strlen(mlx_info->map[i - 1])))
		return (true);
	// printf("false right\n");
	return (false);
}
