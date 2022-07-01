/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:45:50 by kmilchev          #+#    #+#             */
/*   Updated: 2022/07/01 22:19:17 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Cube.h"
#include "map_validation.h"

int	check_if_file_can_be_opened(char *argv[], t_mlx *mlx_info)
{
	mlx_info->fd = open(argv[1], O_RDONLY);
	if (mlx_info->fd < 0)
	{
		printf("File doesn't exists or we don't have right to open it\n");
		return (0);
	}
	printf("FILE WAS SUCCESSFULLY OPENED\n");
	return (1);
}



int	map_checks(char *argv[], t_mlx *mlx_info)
{
	if (check_if_file_can_be_opened(argv, mlx_info) == 0)
	{
		printf("check_if_file_can_be_opened\n");
		return (0);
	}
	if (textures_to_arr(mlx_info) == 0)
	{
		printf("textures_to_arr\n");
		return (0);
	}
	if (check_textures_amount(mlx_info) == 0)
	{	
		printf("check_textures_amount\n");
		return (0);
	}
	return (1);
}

void	init_element_booleans(t_mlx *mlx_info)
{
	mlx_info->elements.c = false;
	mlx_info->elements.f = false;
	mlx_info->elements.no = false;
	mlx_info->elements.so = false;
	mlx_info->elements.ea = false;
	mlx_info->elements.we = false;
	printf("INITIALISED BOOLEANS\n");
}

int	main(int argc, char *argv[])
{
	t_mlx	mlx_info;

	init_element_booleans(&mlx_info);
	if (argc != 2 || map_checks(argv, &mlx_info) == 0)
	{
		printf("Error\n");
		return (0);
	}
	print_2d_array(mlx_info.textures);
	free_2d_array(mlx_info.textures);
	return (0);
}

