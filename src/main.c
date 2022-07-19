/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:37:02 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/19 21:46:25 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/Cube.h"
#include "../src/input_validation_and_map_creation/map_validation.h"

void	init_main(t_mlx_info *mlx_info)
{
	mlx_info->window_width = 800;
	mlx_info->window_height = 500;
	mlx_info->unique_prop.rot_speed = 0.05;
	mlx_info->unique_prop.move_speed = 0.6;
	mlx_info->unique_prop.tex_width = 200;
	mlx_info->unique_prop.tex_height = 200;
	mlx_info->mlx_imgs = calloc(4, sizeof(void *));
	mlx_info->mouse = false;
	mlx_info->main_win = mlx_new_window(mlx_info->mlx,
			mlx_info->window_width, mlx_info->window_height, "Starting point");
}
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
	mlx_info->sprites->sprite_arr[0].x = 5;
	mlx_info->sprites->sprite_arr[0].y = 5;
	mlx_info->sprites->sprite_arr[0].tex_num = 4;
	mlx_info->sprites->sprite_arr[1].x = 10;
	mlx_info->sprites->sprite_arr[1].y = 7;
	mlx_info->sprites->sprite_arr[2].y = 6;
	mlx_info->sprites->sprite_arr[2].y = 15;
	mlx_info->sprites->sprite_arr[2].tex_num = 4;
	mlx_info->sprites->sprite_arr[1].tex_num = 4;
	mlx_info->sprites->sprite_count = 3;
	//To be changed z_buff size
	mlx_info->sprites->z_buff = ft_calloc(1000, sizeof(double));
	mlx_info->sprites->sprite_order = ft_calloc(mlx_info->sprites->sprite_count, sizeof(int));
	mlx_info->sprites->sprite_distance = ft_calloc(mlx_info->sprites->sprite_count, sizeof(double));
}
//To be implemented
// void	sort_sprites(t_mlx_info *mlx_info)
// {}
int	main(int argc, char **argv)
{
	t_mlx_info	mlx_info;

	if (!file_input_is_okay(argc, argv, &mlx_info))
	{
		return (0);
	}
	mlx_info.mlx = mlx_init();
	if (!mlx_info.mlx)
		return (0);
	init_main(&mlx_info);
	get_colors(&mlx_info);
	get_textures(&mlx_info);
	if (check_if_tex_exist(&mlx_info) == 1)
	{
		free_2d_array(mlx_info.texture_paths);
		return (-1);
	}
	load_images(&mlx_info);
	init_sprites(&mlx_info);
	load_sprites(&mlx_info);
	render(&mlx_info);
	mlx_loop_hook(mlx_info.mlx, ft_mouse_tracker, &mlx_info);
	mlx_hook(mlx_info.main_win, 2, 0, key_hook, &mlx_info);
	mlx_loop(mlx_info.mlx);
}

///I need to fix the freeing when there is an error