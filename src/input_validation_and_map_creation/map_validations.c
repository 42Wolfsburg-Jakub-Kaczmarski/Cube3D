/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:45:50 by kmilchev          #+#    #+#             */
/*   Updated: 2022/07/21 18:46:25 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube.h"
#include "map_validation.h"

int	check_if_right_characs(t_mlx_info *mlx_info)
{
	int	i;
	int	j;
	int	counter;

	counter = 0;
	i = 0;
	j = 0;
	while (mlx_info->map_s[i] != NULL)
	{
		j = 0;
		while (mlx_info->map_s[i][j] && mlx_info->map_s[i][j] != '\n')
		{
			if (ft_strchr(ALLOWED_SYMBOLS, mlx_info->map_s[i][j]) == NULL)
				return (set_error_code(mlx_info, UNKNOWN_SYMBOL), 0);
			if (ft_strchr(PLAYER_POS, mlx_info->map_s[i][j]) != NULL
				&& mlx_info->map_s[i][j] != '\0')
				counter++;
			j++;
		}
		i++;
	}
	if (counter != 1)
		return (set_error_code(mlx_info, ONLY_ONE_PLAYER_ALLOWED), 0);
	return (1);
}

bool	character_is_surrounded(t_mlx_info *mlx_info, int i, int j)
{
	if (!square_left_exists(mlx_info, i, j)
		|| !square_right_exists(mlx_info, i, j)
		|| !square_above_exists(mlx_info, i, j)
		|| !square_below_exists(mlx_info, i, j))
	{
		return (set_error_code(mlx_info, NOT_ENCLOSED), false);
	}
	return (true);
}

bool	char_surrounded_my_valid(t_mlx_info *mlx_info, int i, int j)
{
	if (ft_strchr(VALID_SYMBOLS, mlx_info->map_s[i][j - 1]) == NULL
		|| ft_strchr(VALID_SYMBOLS, mlx_info->map_s[i][j + 1]) == NULL
		|| ft_strchr(VALID_SYMBOLS, mlx_info->map_s[i - 1][j]) == NULL
		|| ft_strchr(VALID_SYMBOLS, mlx_info->map_s[i + 1][j]) == NULL)
	{
		return (set_error_code(mlx_info, ELEMENT_POSITIONED_WRONG), false);
	}
	return (true);
}

int	check_if_zeroes_and_player_are_placed_correctly(t_mlx_info *mlx_info)
{
	int		i;
	int		j;
	int		counter;

	counter = 0;
	i = 0;
	j = 0;
	while (mlx_info->map_s[i] != NULL)
	{
		j = 0;
		while (mlx_info->map_s[i][j] && mlx_info->map_s[i][j] != '\n')
		{
			if (mlx_info->map_s[i][j] == '0'
				|| ft_strchr(PLAYER_POS, mlx_info->map_s[i][j]))
			{
				if (!character_is_surrounded(mlx_info, i, j)
					|| !char_surrounded_my_valid(mlx_info, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	get_number_of_sprites(t_mlx_info *mlx_info)
{
	int	i;
	int	j;
	int	counter;

	counter = 0;
	i = 0;
	j = 0;
	while (mlx_info->map_s[i] != NULL)
	{
		j = 0;
		while (mlx_info->map_s[i][j] && mlx_info->map_s[i][j] != '\n')
		{
			if (ft_strchr(SPRITES, mlx_info->map_s[i][j]) != NULL)
				counter++;
			j++;
		}
		i++;
	}
	printf("Sprites: %d\n", counter);
	mlx_info->sprites_amount = calloc(counter, sizeof(t_sprite));
	return (1);
}