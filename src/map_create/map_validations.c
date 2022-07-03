/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:45:50 by kmilchev          #+#    #+#             */
/*   Updated: 2022/07/03 17:30:21 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Cube.h"
#include "map_validation.h"

int	map_to_arr(t_mlx *mlx_info)
{
	int		i;
	char	*line;
	bool	triggered;

	mlx_info->map = malloc((mlx_info->map_height - TEXTURES - mlx_info->new_lines + 1) * sizeof(char *));
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
			mlx_info->map[i] = line;
		line = get_next_line(mlx_info->fd);
		i++;
	}
	mlx_info->map[i] = NULL;
	return (1);
}
