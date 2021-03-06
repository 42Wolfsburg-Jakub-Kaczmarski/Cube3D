/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 15:48:24 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/21 21:12:42 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube.h"

int	convert_to_argb(char *colors_str)
{
	char	**temp;
	int		red;
	int		green;
	int		blue;
	int		a;

	a = 0;
	temp = ft_split(colors_str, ',');
	red = ft_atoi(temp[0]);
	green = ft_atoi(temp[1]);
	blue = ft_atoi(temp[2]);
	free_2d_array(temp);
	return ((a << 24) + (red << 16) + (green << 8) + (blue));
}

void	get_colors(t_mlx_info *mlx_info)
{
	int		i;
	char	*temp;
	char	*just_colors;

	i = 0;
	while (mlx_info->textures[i])
	{
		temp = ft_strtrim(mlx_info->textures[i], " ");
		just_colors = ft_substr(temp, 1, ft_strlen(temp) - 1);
		if (ft_strncmp(temp, "C", 1) == 0)
		{
			free(temp);
			temp = ft_strtrim(just_colors, " ");
			mlx_info->celling_color = convert_to_argb(temp);
		}
		else if (ft_strncmp(temp, "F", 1) == 0)
		{
			free(temp);
			temp = ft_strtrim(just_colors, " ");
			mlx_info->floor_color = convert_to_argb(temp);
		}
		free(just_colors);
		free(temp);
		i++;
	}
}

void	switch_right_tex(t_mlx_info *mlx_info, char *temp, int i)
{
	char	*just_path;

	just_path = ft_substr(temp, 2, ft_strlen(temp) - 1);
	free(temp);
	temp = ft_strtrim(just_path, " ");
	free(just_path);
	just_path = ft_strtrim(temp, "\n");
	mlx_info->texture_paths[i] = ft_strdup(just_path);
	free(just_path);
}

void	get_textures(t_mlx_info *mlx_info)
{
	int		i;
	char	*temp;

	i = 0;
	mlx_info->texture_paths = calloc(sizeof(char *), 4);
	while (mlx_info->textures[i])
	{
		temp = ft_strtrim(mlx_info->textures[i], " ");
		if (ft_strncmp(temp, "NO", 2) == 0)
			switch_right_tex(mlx_info, temp, 0);
		else if (ft_strncmp(temp, "WE", 2) == 0)
			switch_right_tex(mlx_info, temp, 1);
		else if (ft_strncmp(temp, "EA", 2) == 0)
			switch_right_tex(mlx_info, temp, 2);
		else if (ft_strncmp(temp, "SO", 2) == 0)
			switch_right_tex(mlx_info, temp, 3);
		free(temp);
		i++;
	}
}

int	check_if_tex_exist(t_mlx_info *mlx_info)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (access(mlx_info->texture_paths[i], F_OK | R_OK) != 0)
		{
			return (1);
		}
		i++;
	}
	return (0);
}
