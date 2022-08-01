/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 21:24:21 by kmilchev          #+#    #+#             */
/*   Updated: 2022/08/02 01:24:53 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube.h"

void	print_2d_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

void	free_2d_array(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			arr[i] = NULL;
			i++;
		}
		free(arr);
		arr = NULL;
	}
}

void	free_2d_int_array(int **arr, t_mlx_info	*mlx_info)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < mlx_info->map_height)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	print_int_map(t_mlx_info	*mlx_info)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	
	while (i < mlx_info->map_height)
	{
		while (j < mlx_info->longest_row)
		{
			printf("%d", mlx_info->map[i][j]);
			j++;
		}
		j = 0;
		i++;
		printf("\n");
	}
}

void	free_2d_safe(char ***arr)
{
	int	i;
	
	i = 0;
	if (*arr)
	{
		while ((*arr)[i])
		{
			free((*arr)[i]);
			(*arr)[i] = NULL;
			i++;
		}
		free(*arr);
		*arr = NULL;
	}
}
