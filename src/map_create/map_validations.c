/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:45:50 by kmilchev          #+#    #+#             */
/*   Updated: 2022/07/03 18:45:00 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Cube.h"
#include "map_validation.h"

int	map_to_arr(t_mlx *mlx_info)
{
	int		i;
	char	*line;
	bool	triggered;

	mlx_info->map = malloc((mlx_info->file_height - TEXTURES - mlx_info->new_lines + 1) * sizeof(char *));
	triggered = false;
	line = get_next_line(mlx_info->fd);
	while (ft_strncmp(line, "\n", 1) == 0)
	{
		free(line);
		line = get_next_line(mlx_info->fd);
	}
	i = 0;
	while (line != NULL)
	{
		if (ft_strncmp(line, "\n", 1) == 0)
			triggered = true;
		else if (triggered)
		{
			free_2d_array(mlx_info->map);
			return (perror("No new line within map"), 0);
		}
		else
		{
			mlx_info->map_height++; //I might actually not use it 
			mlx_info->map[i] = line;
		}
		line = get_next_line(mlx_info->fd);
		i++;
	}
	mlx_info->map[i] = NULL;
	printf("GOT MAP\n");
	return (1);
}

int	check_if_right_characs(char **arr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (arr[i] != NULL) //rows
	{
		j = 0;
		while (arr[i][j] && arr[i][j] != '\n')
		{
			if (ft_strchr(ALLOWED_SYMBOLS, arr[i][j]) == NULL)
			{
				return (0);
			}
			// printf("i = %d, j = %d\n", i, j);
			j++;
		}
		i++;
	}
	printf("CHECKED ALL THE CHARACTERS IN THE MAP\n");
	return (1);
}