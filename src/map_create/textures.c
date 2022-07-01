/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 21:28:11 by kmilchev          #+#    #+#             */
/*   Updated: 2022/07/01 22:33:30 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Cube.h"
#include "map_validation.h"

//Gets the first 6 lines which are not empty (empty == "\n")
//returns 0 if there aren't 6 lines
int	textures_to_arr(t_mlx *mlx_info)
{
	int		i;
	char	*line;

	mlx_info->textures = malloc((TEXTURES + 1) * sizeof(char *));
	i = 0;
	while (i < TEXTURES)
	{
		line = get_next_line(mlx_info->fd);
		if (line == NULL)
		{
			printf("Not enough textures\n");
			return (0);
		}
		if (ft_strncmp(line, "\n", 2) == 0)
		{
			free(line);
			continue ;
		}
		mlx_info->textures[i] = line;
		i++;
	}
	mlx_info->textures[i] = NULL;
	printf("GOT FIRST 6 LINES\n");
	return (1);
}

//checks if three colour dimensions are given and if they fall between 0 and 255
int	check_texture_colours(char *colours, t_mlx *mlx_info)
{
	char	**three_colours;
	int		len_arr;
	int		i;

	three_colours = ft_split(colours, ',');
	len_arr = arr_len(three_colours);
	if (len_arr != 3)
		return (0);
	if (ft_strlen(three_colours[0]) > 3
		|| ft_strlen(three_colours[1]) > 3
		|| ft_strlen(three_colours[2]) > 3)
		return (0);
	i = 0;
	while (i < len_arr)
	{
		if (ft_strncmp(three_colours[i], "0", 1) == 0)
		{
			i++;
			continue ;
		}
		if (ft_atoi(three_colours[i]) > 255 || ft_atoi(three_colours[i]) <= 0)
			return (0);
		i++;
	}	
	return (1);
}

//checks how many elements there are in each texture instruction
//regardless of 'spaces'
int	check_textures_amount(t_mlx *mlx_info)
{
	int		i;
	char	**elements;
	int		el_nums;

	i = 0;
	while (i < TEXTURES)
	{
		elements = ft_split(mlx_info->textures[i], ' ');
		el_nums = arr_len(elements);
		if (el_nums < 2 || (el_nums == 3 && elements[el_nums - 1][0] != '\n')
			|| (el_nums == 2 && elements[el_nums - 1][0] == '\n'))
		{
			return (perror("Textures input hsould be 2 elements only"), 0);
		}
		check_textures_names(elements[0], mlx_info);
		if (((ft_strncmp(elements[0], "F", 1) == 0)
				|| (ft_strncmp(elements[0], "C", 1) == 0))
			&& check_texture_colours(elements[1], mlx_info) == 0)
			return (0);
		free_2d_array(elements);
		i++;
	}
	printf("CHECKED ALL THE NAMES\n");
	return (all_textures_are_present(mlx_info));
}

//Checks if the instruction is one of the needed ones
//and sets it's flag to true
void	check_textures_names(char *texture_name, t_mlx *mlx_info)
{
	if (ft_strncmp(texture_name, "NO", 2) == 0)
		mlx_info->elements.no = true;
	else if (ft_strncmp(texture_name, "SO", 2) == 0)
		mlx_info->elements.so = true;
	else if (ft_strncmp(texture_name, "EA", 2) == 0)
		mlx_info->elements.ea = true;
	else if (ft_strncmp(texture_name, "WE", 2) == 0)
		mlx_info->elements.we = true;
	else if (ft_strncmp(texture_name, "F", 1) == 0)
		mlx_info->elements.f = true;
	else if (ft_strncmp(texture_name, "C", 1) == 0)
		mlx_info->elements.c = true;
}

int	all_textures_are_present(t_mlx *mlx_info)
{
	// printf("%d\n", mlx_info->elements.we);
	// printf("SO %d\n",	mlx_info->elements.so );
	// printf("%d\n",	mlx_info->elements.ea );
	// printf("%d\n",	mlx_info->elements.we );
	// printf("%d\n",	mlx_info->elements.f );
	// printf("%d\n",	mlx_info->elements.c);
	// printf("TRUE: %d\n", true);
	return (mlx_info->elements.we
		&& mlx_info->elements.so
		&& mlx_info->elements.ea
		&& mlx_info->elements.we
		&& mlx_info->elements.f
		&& mlx_info->elements.c);
}