/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 22:11:38 by kmilchev          #+#    #+#             */
/*   Updated: 2022/07/09 22:22:51 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cube.h"
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
			close(mlx_info->fd);
			return ;
		}
		i++;
		free(line);
	}
}

int	longest_row(char **map, int rows)
{
	int	i;
	int	longest;
	int	curr_len;

	i = 0;
	longest = 0;
	while (i < rows)
	{
		curr_len = ft_strlen(map[i]);
		if (curr_len > longest)
			longest = curr_len;
		i++;
	}
	return (longest);
}

void	set_error_code(t_mlx *mlx_info, int num)
{
	mlx_info->error_code = num;
}
