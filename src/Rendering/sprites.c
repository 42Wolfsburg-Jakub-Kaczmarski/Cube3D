/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 21:53:25 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/22 21:16:03 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube.h"

void	load_sprites(t_mlx_info *mlx_info)
{
		int i = 4;
		char **str = ft_calloc(4, sizeof(char *));
		str[0] = ft_strdup("./assets/cat_fighter.xpm");
		str[1] = ft_strdup("./assets/cuttlefish.xpm");
		str[2] = ft_strdup("./assets/fish.xpm");
		int j = 0;
		while(i < 7)
		{
				mlx_info->mlx_imgs[i] = mlx_xpm_file_to_image(mlx_info->mlx,
				str[j],
				&mlx_info->texture_data[i].width,
				&mlx_info->texture_data[i].height);
		mlx_info->im[i].img_data = mlx_get_data_addr(mlx_info->mlx_imgs[i],
				&mlx_info->im[i].img_bp,
				&mlx_info->im[i].img_sl,
				&mlx_info->im[i].img_e);
		mlx_info->texture_data[i].arr_color = create_color_arr(&mlx_info->im[i],
				mlx_info->texture_data[i].height,
				mlx_info->texture_data[i].width);
		mlx_info->texture_data[i].img_h = mlx_info->mlx_imgs[i];
			j++;
			i++;
		}
		free_2d_array(str);
}

void	init_sprites(t_mlx_info *mlx_info)
{
	mlx_info->sprites->z_buff = ft_calloc(mlx_info->window_width, sizeof(double));
	mlx_info->sprites->sprite_order = ft_calloc(mlx_info->sprites->sprite_count, sizeof(int));
	mlx_info->sprites->sprite_distance = ft_calloc(mlx_info->sprites->sprite_count, sizeof(double));
}