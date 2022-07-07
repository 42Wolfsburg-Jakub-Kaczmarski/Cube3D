/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:45:50 by kmilchev          #+#    #+#             */
/*   Updated: 2022/07/07 23:10:56 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Cube.h"
#include "map_validation.h"

int	check_if_file_can_be_opened(char *argv[], t_mlx *mlx_info)
{
	mlx_info->fd = open(argv[1], O_RDONLY);
	if (mlx_info->fd < 0)
	{
		printf("File doesn't exist or we don't have rights to open it\n");
		return (0);
	}
	return (1);
}

int	perform_checks(char *argv[], t_mlx *mlx_info)
{
	if (check_if_file_can_be_opened(argv, mlx_info) == 0)
		return (0);
	get_number_of_lines(mlx_info);
	if (mlx_info->file_height == 0)
		return (0);
	mlx_info->fd = open(argv[1], O_RDONLY);
	if (textures_to_arr(mlx_info) == 0)
		return (0);
	if (check_textures_amount(mlx_info) == 0)
		return (0);
	if (str_to_char_arr(mlx_info) == 0)
		return (0);
	if (check_if_right_characs(mlx_info) == 0)
		return (0);
	if (check_if_zeroes_and_player_are_placed_correctly(mlx_info) == 0)
		return (0);
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
}

int	main(int argc, char *argv[])
{
	t_mlx	mlx_info;

	init_element_booleans(&mlx_info);
	mlx_info.file_height = 0;
	mlx_info.map_height = 0;
	if (argc != 2 || perform_checks(argv, &mlx_info) == 0)
	{
		printf("Error___________________XXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
		if (mlx_info.textures)
			free_2d_array(mlx_info.textures);
		if (mlx_info.map_s)
			free_2d_array(mlx_info.map_s);
		return (0);
	}
	else
	{
		print_2d_array(mlx_info.map_s);
		fill_map_with_0(&mlx_info, -1, -1);
		char_to_int_map(&mlx_info);
		print_int_map(mlx_info.map, &mlx_info);
		free_2d_array(mlx_info.textures);
		free_2d_array(mlx_info.map_s);
		free_2d_int_array(mlx_info.map, &mlx_info);
	}
	return (0);
}

//the player will be N = 30
// E = 21
// W = 39
// S = 35
