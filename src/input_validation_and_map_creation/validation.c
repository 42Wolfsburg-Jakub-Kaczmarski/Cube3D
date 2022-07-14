/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:45:50 by kmilchev          #+#    #+#             */
/*   Updated: 2022/07/14 19:02:44 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube.h"
#include "map_validation.h"

int	check_if_file_can_be_opened(char *argv[], t_mlx *mlx_info)
{
	mlx_info->fd = open(argv[1], O_RDONLY);
	if (mlx_info->fd < 0)
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

int	perform_checks(char *argv[], t_mlx *mlx_info)
{
	if (check_if_file_can_be_opened(argv, mlx_info) == 0)
		return (set_error_code(mlx_info, FILE_CANNOT_BE_OPENED), 0);
	get_number_of_lines(mlx_info);
	if (mlx_info->file_height == 0)
		return (set_error_code(mlx_info, EMPTY_FILE), 0);
	mlx_info->fd = open(argv[1], O_RDONLY);
	if (textures_to_arr(mlx_info) == 0)
		return (0);
	if (check_textures_amount(mlx_info) == 0)
		return (set_error_code(mlx_info, WRONG_TEXTURE_DATA), 0);
	if (str_to_char_arr(mlx_info) == 0)
		return (0);
	if (check_if_right_characs(mlx_info) == 0)
		return (0);
	if (check_if_zeroes_and_player_are_placed_correctly(mlx_info) == 0)
		return (0);
	return (1);
}

void	print_error(int error_code)
{
	if (error_code == FILE_CANNOT_BE_OPENED)
		printf("The file cannot be opened\n");
	else if (error_code == EMPTY_FILE)
		printf("The file is empty\n");
	else if (error_code == NOT_ENOUGH_TEXTURES)
		printf("Not enough textures\n");
	else if (error_code == WRONG_TEXTURE_DATA)
		printf("The texture data is wrong\n");
	else if (error_code == EMPTY_MAP)
		printf("The map is empty\n");
	else if (error_code == NEW_LINE_WITHIN_MAP)
		printf("New line within map is not allowed\n");
	else if (error_code == ONLY_ONE_PLAYER_ALLOWED)
		printf("Exactly one player is allowed\n");
	else if (error_code == UNKNOWN_SYMBOL)
		printf("The only allowed symbols are: 0, 1, W, E, S, N, space and NL\n");
	else if (error_code == NOT_ENCLOSED)
		printf("The map is not closed\n");
	else if (error_code == ELEMENT_POSITIONED_WRONG)
		printf("Please check the map, an element is positioned wrong\n");
	else if (error_code == WRONG_AMOUNT_OF_ARGUMENTS)
		printf("Please provide a map\n");
	else
		printf("Unknown error\n");
}

///if it returns 0, everything will have been freed
//if it returns 1, the map is valid
//textures and int array need to be freed in the end
int	file_input_is_okay(int argc, char *argv[], t_mlx *mlx_info)
{
	init_element_booleans(mlx_info);
	mlx_info->file_height = 0;
	mlx_info->map_height = 0;
	mlx_info->error_code = WRONG_AMOUNT_OF_ARGUMENTS;
	if (argc != 2 || perform_checks(argv, mlx_info) == 0)
	{
		print_error(mlx_info->error_code);
		free_2d_array(mlx_info->map_s);
		free_2d_array(mlx_info->textures);
		return (0);
	}
	else
	{
		fill_map_with_0(mlx_info, -1, -1);
		char_to_int_map(mlx_info);
		free_2d_array(mlx_info->map_s);
	}
	return (1);
}

// int	main(int argc, char *argv[])
// {
// 	t_mlx	mlx_info;

// 	if (file_input_is_okay(argc, argv, &mlx_info))
// 	{
// 		////do stuff and then free these two
// 		free_2d_int_array(mlx_info.map, &mlx_info);
// 		free_2d_array(mlx_info.textures);
// 	}
// 	return (0);
// }

// //the player will be N = 30
// // E = 21
// W = 39
// S = 35
