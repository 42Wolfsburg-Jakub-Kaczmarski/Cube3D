/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:45:50 by kmilchev          #+#    #+#             */
/*   Updated: 2022/07/03 15:39:56 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Cube.h"
#include "map_validation.h"

int	map_to_arr(t_mlx *mlx_info)
{
	int		i;
	char	*line;

	mlx_info->map = malloc((mlx_info->map_height - TEXTURES + 1) * sizeof(char *));
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