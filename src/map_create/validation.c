/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:45:50 by kmilchev          #+#    #+#             */
/*   Updated: 2022/07/03 21:21:11 by kmilchev         ###   ########.fr       */
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
	printf("FILE WAS SUCCESSFULLY OPENED\n");
	return (1);
}


void get_number_of_lines(t_mlx *mlx_info)
{
	int	i;
	char *line;

	i = 0;
	while(1)
	{
		line = get_next_line(mlx_info->fd);
		if (line == NULL)
		{
			mlx_info->file_height = i;
			printf("GOT NUMBER OF LINES: %d\n", i);
			return ;
		}
		i++;
		free(line);
	}
	close(mlx_info->fd);
}

int	map_checks(char *argv[], t_mlx *mlx_info)
{
	if (check_if_file_can_be_opened(argv, mlx_info) == 0)
	{
		printf("check_if_file_can_be_opened\n");
		return (0);
	}
	get_number_of_lines(mlx_info);
	if (mlx_info->file_height == 0)
	{
		printf("Empty file\n");
		return (0);
	}
	mlx_info->fd = open(argv[1], O_RDONLY);
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
	if (map_to_arr(mlx_info) == 0)
	{
		printf("map_to_arr\n");
		return (0);
	}
	if(check_if_right_characs(mlx_info) == 0)
	{
		printf("check_if_right_characs\n");
		return (0);
	}
	if(check_if_spaces_are_placed_correctly(mlx_info) == 0)
	{
		printf("check_if_spaces_are_placed_correctly\n");
		return (0);
	}
	if(check_boarders(mlx_info) == 0)
	{
		printf("check_boarders\n");
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
	mlx_info.file_height = 0;
	mlx_info.map_height = 0;
	if (argc != 2 || map_checks(argv, &mlx_info) == 0)
	{
		printf("Error___________________XXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
		return (0);
	}
	// print_2d_array(mlx_info.textures);
	// print_2d_array(mlx_info.map);
	// free_2d_array(mlx_info.textures);
	// free_2d_array(mlx_info.map);
	// char *string = ft_strchr("hello", 'k');
	// if (string == NULL)
	// 	printf("%s\n", string);
	return (0);
}
