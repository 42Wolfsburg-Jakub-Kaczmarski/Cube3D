/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 15:35:32 by kmilchev          #+#    #+#             */
/*   Updated: 2022/08/03 15:41:15 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube.h"
#include "../../src/input_validation_and_map_creation/map_validation.h"

void	print_and_free(char *message, t_mlx_info *mlx_info)
{
	printf("%s\n", message);
	free_2d_array(mlx_info->textures);
	free_2d_int_array(mlx_info->map, mlx_info);
	free_sprites(mlx_info);
	free_2d_array(mlx_info->texture_paths);
}
