/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 21:53:25 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/20 19:48:02 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube.h"

void	load_sprites(t_mlx_info *mlx_info)
{
		int i = 4;
		//Replace add more paths to texture paths :)
		char *path = ft_strdup("./assets/cat_fighter.xpm");
		// while(i < 5)
		// {
				mlx_info->mlx_imgs[i] = mlx_xpm_file_to_image(mlx_info->mlx,
				path,
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
		// }

		// i++;
}

void	init_sprites(t_mlx_info *mlx_info)
{
	if(mlx_info){}
	mlx_info->sprites = calloc(10,sizeof(t_sprite_data));
	mlx_info->sprites->sprite_arr = calloc(10, sizeof(t_sprite*));
	// mlx_info->sprites->sprite_arr[0].x = 5;
	// mlx_info->sprites->sprite_arr[0].y = 5;
	// mlx_info->sprites->sprite_arr[0].tex_num = 4;
	// mlx_info->sprites->sprite_arr[1].x = 10;
	// mlx_info->sprites->sprite_arr[1].y = 7;
	mlx_info->sprites->sprite_arr[0].x = 6;
	mlx_info->sprites->sprite_arr[0].y = 15;
	mlx_info->sprites->sprite_arr[0].tex_num = 4;
	// mlx_info->sprites->sprite_arr[1].tex_num = 4;
	mlx_info->sprites->sprite_count = 1;
	//To be changed z_buff size
	mlx_info->sprites->z_buff = ft_calloc(mlx_info->window_width, sizeof(double));
	mlx_info->sprites->sprite_order = ft_calloc(mlx_info->sprites->sprite_count, sizeof(int));
	mlx_info->sprites->sprite_distance = ft_calloc(mlx_info->sprites->sprite_count, sizeof(double));
}