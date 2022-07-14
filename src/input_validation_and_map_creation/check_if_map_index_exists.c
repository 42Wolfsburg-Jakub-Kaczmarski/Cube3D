/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_map_index_exists.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 20:13:33 by kmilchev          #+#    #+#             */
/*   Updated: 2022/07/14 19:04:40 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube.h"

//universal but with the others it is easier to read
bool	square_exists(t_mlx *mlx_info, int i, int j)
{
	if ((i > 0 && i < mlx_info->map_height - 1)
		&& (j > 0 && j < (int)ft_strlen(mlx_info->map_s[i])))
		return (true);
	return (false);
}

bool	square_below_exists(t_mlx *mlx_info, int i, int j)
{
	if ((i + 1 > 0 && i + 1 <= mlx_info->map_height - 1)
		&& (j > 0 && j < (int)ft_strlen(mlx_info->map_s[i + 1]) - 1))
		return (true);
	return (false);
}

bool	square_above_exists(t_mlx *mlx_info, int i, int j)
{
	if ((i - 1 >= 0 && i - 1 <= mlx_info->map_height - 1)
		&& (j < (int)ft_strlen(mlx_info->map_s[i - 1])))
		return (true);
	return (false);
}

bool	square_left_exists(t_mlx *mlx_info, int i, int j)
{
	if ((i > 0 && i < mlx_info->map_height - 1)
		&& (j - 1 >= 0 && j - 1 <= (int)ft_strlen(mlx_info->map_s[i - 1]) - 1))
		return (true);
	return (false);
}

bool	square_right_exists(t_mlx *mlx_info, int i, int j)
{
	if ((i > 0 && i < mlx_info->map_height - 1)
		&& (j + 1 > 0 && j + 1 < (int)ft_strlen(mlx_info->map_s[i - 1])))
		return (true);
	return (false);
}
