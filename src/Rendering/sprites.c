/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 21:53:25 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/21 21:31:04 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube.h"

void	load_sprites(t_mlx_info *mlx_info)
{
		int i = 4;
		//Replace add more paths to texture paths :)
		char **str = ft_calloc(3, sizeof(char *));
		str[0] = ft_strdup("./assets/cat_fighter.xpm");
		str[1] = ft_strdup("./assets/fish.xpm");
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
		// i++;
}

void	init_sprites(t_mlx_info *mlx_info)
{
	printf("%d", mlx_info->sprites->sprite_count);
	// mlx_info->sprites->sprite_arr = calloc(10, sizeof(t_sprite));
	// mlx_info->sprites->sprite_arr[0].x = 6;
	// mlx_info->sprites->sprite_arr[0].y = 15;
	// mlx_info->sprites->sprite_arr[0].tex_num = 4;
	// mlx_info->sprites->sprite_arr[1].x = 10;
	// mlx_info->sprites->sprite_arr[1].y = 7;
	// mlx_info->sprites->sprite_arr[1].tex_num = 4;
	// mlx_info->sprites->sprite_arr[2].x = 5;
	// mlx_info->sprites->sprite_arr[2].y = 5;
	// mlx_info->sprites->sprite_arr[2].tex_num = 4;
	// mlx_info->sprites->sprite_arr[3].x = 5;
	// mlx_info->sprites->sprite_arr[3].y = 7;
	// mlx_info->sprites->sprite_arr[3].tex_num = 4;
	// mlx_info->sprites->sprite_arr[4].x = 6;
	// mlx_info->sprites->sprite_arr[4].y = 9;
	// mlx_info->sprites->sprite_arr[4].tex_num = 4;
	// mlx_info->sprites->sprite_count = 5;
	
	mlx_info->sprites->z_buff = ft_calloc(mlx_info->window_width, sizeof(double));
	mlx_info->sprites->sprite_order = ft_calloc(mlx_info->sprites->sprite_count, sizeof(int));
	mlx_info->sprites->sprite_distance = ft_calloc(mlx_info->sprites->sprite_count, sizeof(double));
}