/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:45:50 by kmilchev          #+#    #+#             */
/*   Updated: 2022/07/07 17:59:47 by kmilchev         ###   ########.fr       */
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
	if(check_borders(mlx_info) == 0)
	{
		printf("check_borders\n");
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

int find_longest_row(char **map, int rows)
{
	int i;
	int longest;
	int curr_len;
	
	i = 0;
	longest = 0;
	while(i < rows)
	{
		curr_len = ft_strlen(map[i]);
		// printf("Cur len: %d\n", curr_len);
		if (curr_len > longest)
			longest = curr_len;
		i++;
	}
	return (longest);
}

void fill_map_with_0(t_mlx *mlx_info)
{
	int i;
	int j;
	char *new_row;

	i = 0;
	j = 0;
	
	mlx_info->longest_row = find_longest_row(mlx_info->map, mlx_info->map_height);
	new_row = malloc(sizeof(char *) * (mlx_info->longest_row + 1));
	while (i < mlx_info->map_height)
	{
		while(j < mlx_info->longest_row)
		{
			if (i <  mlx_info->map_height && j < ft_strlen(mlx_info->map[i]))
			{
				if (mlx_info->map[i][j] == '\n' || mlx_info->map[i][j] == ' ')
					new_row[j] = '0';
				else
					new_row[j] = mlx_info->map[i][j];
			}
			else
				new_row[j] = '0';
			j++;
		}
		free(mlx_info->map[i]);
		mlx_info->map[i] = ft_strdup(new_row);
		free(new_row);
		j = 0;
		i++;
		new_row = malloc(sizeof(char *) * (mlx_info->longest_row + 1));
	}
	free(new_row);
	
}

void char_to_int_map(t_mlx *mlx_info)
{
	mlx_info->numeric_map = ft_calloc(mlx_info->map_height, sizeof(int *));
	int	i;
	int j;
	char c;
	i = 0;
	j = 0;
	printf("Line = %s\n", mlx_info->map[0]);
	printf("Line = %s\n", mlx_info->map[1]);
	printf("Line = %s\n", mlx_info->map[2]);
	printf("Line = %s\n", mlx_info->map[3]);
	

	while(i < mlx_info->map_height)
	{
		// printf("Idx: %d Line in loop = %s\n",i, mlx_info->map[i]);
		// printf("i = %d\n", i);
		mlx_info->numeric_map[i] = ft_calloc(mlx_info->longest_row, sizeof(int));
		while(j < mlx_info->longest_row)
		{
			// printf("Idx: %d Line in the other loop = %s\n",i, mlx_info->map[i]);
			// c = mlx_info->map[i][j];
			// printf("Char c: %d\n", (c) - '0');
			// mlx_info->numeric_map[j] = ft_calloc(1, sizeof(int));
			// c = (mlx_info->map[i][j]);
			mlx_info->numeric_map[i][j] = (mlx_info->map[i][j]) - '0';
			// printf("Char: %c \n", mlx_info->map[i][j]);
			printf("Number: %d ", mlx_info->numeric_map[i][j]);
			j++;
		}
		printf("\n");
		j = 0;
		i++;
	}
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
	fill_map_with_0(&mlx_info);
	printf("______________________________________\n");
	print_2d_array(mlx_info.map);
	printf("______________________________________\n");
	char_to_int_map(&mlx_info);
	print_int_map(mlx_info.numeric_map, &mlx_info);
	free_2d_array(mlx_info.textures);
	// printf("%d", '1' - '0');
	return (0);
}

//the player will be N = 30
// E = 21
// W = 39
// S = 35
