/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:37:02 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/16 15:48:08 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "include/Cube.h"
#include "src/input_validation_and_map_creation/map_validation.h"

void	init_main(t_mlx_info *mlx_info)
{
	mlx_info->window_width = 800;
	mlx_info->window_height = 500;
	mlx_info->unique_prop.dirX = -1;
	mlx_info->unique_prop.dirY = 0;
	mlx_info->unique_prop.planeX = 0;
	mlx_info->unique_prop.planeY = 0.66;
	mlx_info->unique_prop.rotSpeed = 0.1;
	mlx_info->unique_prop.move_speed = 0.6;
	mlx_info->unique_prop.texWidth = 200;
	mlx_info->unique_prop.texHeight = 200;
	mlx_info->mlx_imgs = calloc(4, sizeof(void *));
	mlx_info->main_win = mlx_new_window(mlx_info->mlx, mlx_info->window_width, mlx_info->window_height, "Starting point");
}

int main(int argc, char **argv)
{
	t_mlx_info mlx_info;
	if (!file_input_is_okay(argc, argv, &mlx_info))
	{
		// printf("sth");
		return (0);
	}
	mlx_info.mlx = mlx_init();
	if(!mlx_info.mlx)
		return 0;
	init_main(&mlx_info);
	get_colors(&mlx_info);
	get_textures(&mlx_info);
	if(check_if_tex_exist(&mlx_info) == 1)
	{
		free_2d_array(mlx_info.texture_paths);
		perror("Provided paths are wrong or cannot open textures\n");
		return -1;
	};
	load_images(&mlx_info);
	// mlx_info.main_img.img = mlx_new_image(mlx_info.mlx, mlx_info.window_width, mlx_info.window_height);
	// mlx_info.mlx_imgs[0] = mlx_png_file_to_image(mlx_info.mlx, "catto_Tex.png", &w, &h);
	// mlx_put_image_to_window(mlx_info.mlx, mlx_info.main_win, 	mlx_info.mlx_imgs[0], 0,0);
	render(&mlx_info);
	// mlx_loop_hook(mlx_info.mlx, frame_render, &mlx_info);
	
	mlx_hook(mlx_info.main_win, 2,0,key_hook,&mlx_info);
	mlx_loop(mlx_info.mlx);

}
