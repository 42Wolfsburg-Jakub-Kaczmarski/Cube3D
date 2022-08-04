/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:37:02 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/08/04 17:09:34 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cube.h"
#include "../src/input_validation_and_map_creation/map_validation.h"

void	init_main(t_mlx_info *mlx_info)
{
	mlx_info->keys.a = false;
	mlx_info->keys.s = false;
	mlx_info->keys.d = false;
	mlx_info->keys.w = false;
	mlx_info->keys.left_arrow = false;
	mlx_info->keys.right_arrow = false;
	mlx_info->window_width = 800;
	mlx_info->window_height = 500;
	mlx_info->window_width = 840;
	mlx_info->window_height = 640;
	mlx_info->unique_prop.rot_speed = 0.05;
	mlx_info->unique_prop.move_speed = 0.09;
	mlx_info->unique_prop.tex_width = 200;
	mlx_info->unique_prop.tex_height = 200;
	mlx_info->mouse = false;
	mlx_info->main_win = mlx_new_window(mlx_info->mlx,
			mlx_info->window_width, mlx_info->window_height, "Бавноразвиващи");
}

int	play_theme_song(t_mlx_info *mlx_info)
{
	const char	*args[] = {AUDIO, "./music/music_water.wav", NULL};

	mlx_info->pid = fork();
	if (mlx_info->pid == 0)
	{
		execvp(args[0], (char **)args);
		exit(1);
	}
	return (0);
}

int	x_close(void *sth)
{
	t_mlx_info	*mlx_info;

	mlx_info = sth;
	kill(mlx_info->pid, SIGKILL);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_mlx_info	mlx_info;

	if (!file_input_is_okay(argc, argv, &mlx_info))
		return (-1);
	mlx_info.mlx = mlx_init();
	if (!mlx_info.mlx)
		return (-1);
	init_main(&mlx_info);
	get_colors(&mlx_info);
	get_textures(&mlx_info);
	if (check_if_tex_exist(&mlx_info) == 1)
	{
		print_and_free("The path to xpm file is wrong", &mlx_info);
		return (-1);
	}
	play_theme_song(&mlx_info);
	load_images(&mlx_info);
	init_sprites(&mlx_info);
	load_sprites(&mlx_info);
	render(&mlx_info);
	mlx_loop_hook(mlx_info.mlx, movement, &mlx_info);
	mlx_hook(mlx_info.main_win, 2, 0, key_is_pressed, &mlx_info);
	mlx_hook(mlx_info.main_win, 3, 0, key_is_released, &mlx_info);
	mlx_hook(mlx_info.main_win, 17, 0, x_close, &mlx_info);
	mlx_loop(mlx_info.mlx);
}
