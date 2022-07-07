/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:45:50 by kmilchev          #+#    #+#             */
/*   Updated: 2022/07/07 21:02:21 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Cube.h"
#include "map_validation.h"

int	map_to_arr(t_mlx *mlx_info)
{
	int		i;
	char	*line;
	bool	triggered;

	printf("File heihgt: %d\n", mlx_info->file_height);
	mlx_info->map = malloc((mlx_info->file_height - TEXTURES + 10) * sizeof(char *));
	triggered = false;

	while (1)
	{
		line = get_next_line(mlx_info->fd);
		if (ft_strncmp(line, "\n", 1) == 0)
			free(line);
		else
			break ;	
	}
	i = 0;
	while (line != NULL)
	{
		if (ft_strncmp(line, "\n", 1) == 0)
		{
			triggered = true;
			free(line);
		}
		else if (triggered)
		{
			free_2d_array(mlx_info->map);
			return (perror("No new line within map"), 0);
		}
		else
		{
			mlx_info->map_height++;
			mlx_info->map[i] = line;
		}
		line = get_next_line(mlx_info->fd);
		i++;
	}
	mlx_info->map[i] = NULL;
	printf("GOT MAP\n");
	return (1);
}

int	check_if_right_characs(t_mlx *mlx_info)
{
	int	i;
	int	j;
	int	counter;

	counter = 0;
	i = 0;
	j = 0;
	while (mlx_info->map[i] != NULL) //rows
	{
		j = 0;
		while (mlx_info->map[i][j] && mlx_info->map[i][j] != '\n')
		{
			if (ft_strchr(ALLOWED_SYMBOLS, mlx_info->map[i][j]) == NULL)
				return (0);
			if (ft_strchr("WESN", mlx_info->map[i][j]) != NULL && mlx_info->map[i][j] != '\0')
				counter++;
			j++;
		}
		i++;
	}
	if (counter != 1)
	{
		printf("Counter %d\n", counter);
		return (0);
	}
	printf("CHECKED ALL THE CHARACTERS IN THE MAP\n");
	return (1);
}

int check_if_spaces_are_placed_correctly(t_mlx *mlx_info)
{
	int	i;
	int	j;
	int	counter;
	char c;
	
	counter = 0;
	i = 0;
	j = 0;

	while (mlx_info->map[i] != NULL) //rows
	{
		j = 0;
		while (mlx_info->map[i][j] && mlx_info->map[i][j] != '\n')
		{
			if (mlx_info->map[i][j] == ' ')
			{
				// printf("%d\n", j - 1);
				if (   (square_left_exists(mlx_info, i, j) && ft_strchr("1 \n", mlx_info->map[i][j - 1]) == NULL)
					|| (square_right_exists(mlx_info, i, j) && ft_strchr("1 \n", mlx_info->map[i][j + 1]) == NULL)
					|| (square_above_exists(mlx_info, i, j) && ft_strchr("1 \n", mlx_info->map[i - 1][j]) == NULL)
					|| (square_below_exists(mlx_info, i, j) && ft_strchr("1 \n", mlx_info->map[i + 1][j]) == NULL)
					)
				{
					printf("SPACE: wrong char\n");
					return (0);
				}
			}
			j++;
		}
		if (mlx_info->map[i][j - 1] && ft_strchr("1 ", mlx_info->map[i][j - 1]) == NULL)
		{
			printf("NEW_LINE: wrong char %c\n", mlx_info->map[i][j - 1]);
			return (0);
		}
		i++;
	}
	
	return (1);
}

bool character_is_surrounded(t_mlx *mlx_info, int i, int j)
{
	if (!square_left_exists(mlx_info, i, j) || !square_right_exists(mlx_info, i, j)
		|| !square_above_exists(mlx_info, i, j) || !square_below_exists(mlx_info, i, j))
	{
		printf("CHARACTER IS NOT SURROUNDED\n");
		return (false);
	}
	return (true);
}

int check_if_zeroes_are_placed_correctly(t_mlx *mlx_info)
{
	int	i;
	int	j;
	int	counter;
	char c;
	
	counter = 0;
	i = 0;
	j = 0;
	while (mlx_info->map[i] != NULL) //rows
	{
		j = 0;
		while (mlx_info->map[i][j] && mlx_info->map[i][j] != '\n')
		{
			if (mlx_info->map[i][j] == '0' || ft_strchr("WESN", mlx_info->map[i][j]))
			{
				if (character_is_surrounded(mlx_info, i, j) == false)
				{
					printf("SPACE: wrong char\n");
					return (0);
				}
			}
			j++;
		}
		if (mlx_info->map[i][j - 1] && ft_strchr("1 ", mlx_info->map[i][j - 1]) == NULL)
		{
			printf("NEW_LINE: wrong char %c\n", mlx_info->map[i][j - 1]);
			return (0);
		}
		i++;
	}
	
	return (1);
}

int check_borders(t_mlx *mlx_info)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	///top
	while (mlx_info->map[i][j] && mlx_info->map[i][j] != '\n')
	{
		if (mlx_info->map[i][j] != ' ' && mlx_info->map[i][j] != '1')
		{
			printf("Error 0\n");
			return (0);
		}
		j++;
	}
	j = 0;
	i = mlx_info->map_height - 1;
	///bottom
	while (mlx_info->map[i][j] && mlx_info->map[i][j] != '\n')
	{
		if (mlx_info->map[i][j] != ' ' && mlx_info->map[i][j] != '1')
		{
			printf("Error 1\n");
			return (0);
		}
		j++;
	}
	j = 0;
	i = 0;
	while (i < mlx_info->map_height && mlx_info->map[i][j])
	{
		if (mlx_info->map[i][j] != ' ' && mlx_info->map[i][j] != '1')
		{
			printf("Error 3\n");
			return (0);
		}

		i++;
	}

	
	return (1);
}

