/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 17:46:08 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/06/28 14:10:28 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube.h"

int	check_if_right_characs(char **arr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (arr[i][j])
	{
		j = 0;
		while (arr[i][j])
		{
			if (arr[i][j] != '1' && arr[i][j] != '0' && arr[i][j] != 'P' && arr[i][j] != '\n' )
			{
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_map(char **argv,  t_mlx *mlx_info)
{
	int fd = open(argv[1], O_RDONLY);
	if(fd < 0 )
	{
		printf("File doesn't exists or we don't have right to open it\n");
		return 0;
	}
	if(!mlx_info){}
	char *line = get_next_line(fd);
	int counter = 0;
	while(line)
	{
		counter++;
		line = get_next_line(fd);
	}
	close(fd);
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	mlx_info->map_width = ft_strlen(line);
	mlx_info->map = ft_calloc(counter ,sizeof(char *));
	mlx_info->map_height = counter;
	counter = 0;
	while(line)
	{
		mlx_info->map[counter++] = line;
		line = get_next_line(fd);
	}
 	if(check_if_right_characs(mlx_info->map) == -1)
	 	return 0;
	// counter--;
	// while(counter != 0)
	// {
	// 	printf("%s\n", mlx_info->map[counter]);
	// 	counter--;
	// }
	return 1;
	// if(ft_strncmp())
	// {	
	// }
}
