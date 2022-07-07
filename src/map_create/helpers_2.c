/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 22:11:38 by kmilchev          #+#    #+#             */
/*   Updated: 2022/07/07 23:02:03 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Cube.h"
#include "map_validation.h"

int	arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		i++;
	}
	return (i);
}

int	count_chars(char *str, char c)
{
	int	idx;
	int	count;

	if (!str || !c)
		return (-1);
	idx = 0;
	count = 0;
	while (str[idx])
	{
		if (str[idx] == c)
			count++;
		idx++;
	}
	return (count);
}

void	get_number_of_lines(t_mlx *mlx_info)
{
	int		i;
	char	*line;

	i = 0;
	while (1)
	{
		line = get_next_line(mlx_info->fd);
		if (line == NULL)
		{
			mlx_info->file_height = i;
			return ;
		}
		i++;
		free(line);
	}
	close(mlx_info->fd);
}
