/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:45:50 by kmilchev          #+#    #+#             */
/*   Updated: 2022/07/03 21:46:13 by kmilchev         ###   ########.fr       */
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
			// free_2d_array(mlx_info->map); some double free?? but I shouldn't free here anyway?
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
			// printf("SPACE: wrong char   %c\n", mlx_info->map[i][j]);
			if (mlx_info->map[i][j] == ' ')
			{
				// printf("%d\n", j - 1);
				if (   (j - 1 > 0 && mlx_info->map[i][j - 1] && ft_strchr("1 \n", mlx_info->map[i][j - 1]) == NULL)
					|| (j + 1 < ft_strlen(mlx_info->map[i]) && mlx_info->map[i][j + 1] && ft_strchr("1 \n", mlx_info->map[i][j + 1]) == NULL)
					|| (i - 1 > 0 && mlx_info->map[i - 1][j] && ft_strchr("1 \n", mlx_info->map[i][j]) == NULL)
					|| (i + 1 < mlx_info->map_height - 1 &&  mlx_info->map[i + 1][j] && ft_strchr("1 \n", mlx_info->map[i + 1][j]) == NULL)
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

int check_boarders(t_mlx *mlx_info)
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
		// if (mlx_info->map[i][j] == ' ' && mlx_info->map[i - 1][j] != '1')
		// {
		// 	printf("Error 2\n");
		// 	return (0);
		// }
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
