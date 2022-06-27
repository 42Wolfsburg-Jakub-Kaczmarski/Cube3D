/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 17:46:08 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/06/27 21:43:36 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube.h"

int	check_map(char **argv,  mai_t *mlx_info)
{
	int fd = open(argv[1], O_RDONLY);
	if(fd < 0)
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
	mlx_info->map = ft_calloc(counter ,sizeof(char *));
	counter = 0;
	while(line)
	{
		mlx_info->map[counter++] = line;
		line = get_next_line(fd);
	}
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