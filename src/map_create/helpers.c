/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 21:24:21 by kmilchev          #+#    #+#             */
/*   Updated: 2022/07/05 21:01:07 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Cube.h"

void	print_2d_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("%s", arr[i]);
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