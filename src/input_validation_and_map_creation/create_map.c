/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 21:30:38 by kmilchev          #+#    #+#             */
/*   Updated: 2022/07/17 10:31:02 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube.h"
#include "map_validation.h"

//Reads from file and creates a string array
int	str_to_char_arr(t_mlx_info *mlx_info)
{
	char	*line;

	mlx_info->map_s = malloc((mlx_info->file_height + 10) * sizeof(char *));
	while (1)
	{
		line = get_next_line(mlx_info->fd);
		if (line == NULL)
			return (set_error_code(mlx_info, EMPTY_MAP), 0);
		if (ft_strncmp(line, "\n", 1) == 0)
			free(line);
		else
			break ;
	}
	if (str_to_char_arr2(mlx_info, line) == 0)
		return (0);
	return (1);
}

//Reads from file and creates a string array
int	str_to_char_arr2(t_mlx_info *mlx_info, char *line)
{
	int		i;
	bool	triggered;

	triggered = false;
	i = 0;
	while (line != NULL)
	{
		if (ft_strncmp(line, "\n", 1) == 0)
		{
			triggered = true;
			free(line);
		}
		else if (triggered)
			return (set_error_code(mlx_info, NEW_LINE_WITHIN_MAP), 0);
		else
		{
			mlx_info->map_height++;
			mlx_info->map_s[i] = line;
		}
		line = get_next_line(mlx_info->fd);
		i++;
	}
	mlx_info->map_s[i] = NULL;
	return (1);
}

//makes the map rectangular by filling in all spcaes with zeros
//i and j need to be passed as args because od the norm
//both need to be -1
void	fill_map_with_0(t_mlx_info *data, int i, int j)
{
	char	*new_row;

	data->longest_row = longest_row(data->map_s, data->map_height);
	new_row = malloc(sizeof(char *) * (data->longest_row + 1));
	while (++i < data->map_height)
	{
		while (++j < (int)data->longest_row)
		{
			if (i < data->map_height && j < (int)ft_strlen(data->map_s[i]))
			{
				if (data->map_s[i][j] == '\n' || data->map_s[i][j] == ' ')
					new_row[j] = '0';
				else
					new_row[j] = data->map_s[i][j];
			}
			else
				new_row[j] = '0';
		}
		free(data->map_s[i]);
		data->map_s[i] = ft_strdup(new_row);
		free(new_row);
		j = -1;
		new_row = malloc(sizeof(char *) * (data->longest_row + 1));
	}
	free(new_row);
}

void	set_direction(t_mlx_info *mlx_info, char c)
{
	if (c == 'N')
	{
		mlx_info->unique_prop.dirX = 0;
		mlx_info->unique_prop.dirY = -1;
	}
	else if (c == 'W')
	{
		mlx_info->unique_prop.dirX = -1;
		mlx_info->unique_prop.dirY = 0;
	}
	else if (c == 'E')
	{
		mlx_info->unique_prop.dirX = 1;
		mlx_info->unique_prop.dirY = 0;
	}
	else if (c == 'S')
	{
		mlx_info->unique_prop.dirX = 0;
		mlx_info->unique_prop.dirY = 1;
	}
	mlx_info->unique_prop.planeX = mlx_info->unique_prop.dirY;
	mlx_info->unique_prop.planeY = mlx_info->unique_prop.dirX * -1;
}

//Reads from the string array and creates an int array
void	char_to_int_map(t_mlx_info *mlx_info)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	mlx_info->map = ft_calloc(mlx_info->map_height, sizeof(int *));
	while (i < mlx_info->map_height)
	{
		mlx_info->map[i] = ft_calloc(mlx_info->longest_row, sizeof(int));
		while (j < mlx_info->longest_row)
		{
			if (ft_strchr(PLAYER_POS, mlx_info->map_s[i][j]) != NULL)
			{
				set_direction(mlx_info, mlx_info->map_s[i][j]);
				mlx_info->map[i][j] = 0;
				mlx_info->unique_prop.posX = i;
				mlx_info->unique_prop.posY = j;
			}
			else
				mlx_info->map[i][j] = (mlx_info->map_s[i][j]) - '0';
			j++;
		}
		j = 0;
		i++;
	}
}
