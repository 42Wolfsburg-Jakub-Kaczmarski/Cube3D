/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:14:43 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/06/25 13:38:48 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "MLX42/include/MLX42/MLX42.h"
#include "Cube.h"
#include <string.h>
#include <unistd.h>
	mlx_t *mlx;
int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}
int get_r(int rgba)
{
    // Move 3 bytes to the right and mask out the first byte.
    return ((rgba >> 24) & 0xFF);
}
void hook(void *ptr)
{
	t_main_thingy *main_thingy = (t_main_thingy *)ptr;
	
	if(mlx_is_key_down(main_thingy->mlx, MLX_KEY_LEFT))
	{
		main_thingy->image_thingy->instances->x -= 20;		
	}
	if(mlx_is_key_down(main_thingy->mlx, MLX_KEY_RIGHT))
	{
		main_thingy->image_thingy->instances->x += 20;		
	}
	if(mlx_is_key_down(main_thingy->mlx, MLX_KEY_UP))
	{
		main_thingy->image_thingy->instances->y -= 20;		
	}
	if(mlx_is_key_down(main_thingy->mlx, MLX_KEY_DOWN))
	{
		main_thingy->image_thingy->instances->y += 20;		
	}

}
int main(void)
{
	// int b = get_rgba(255,255,255,255);
	// b = get_r(b);
	// printf("Czary %d", b);
	// char arr[] = {
	// 	1,1,1,1,1,1,1,1,1,1,1,1,1,
	// 	1,0,0,0,0,0,0,0,0,0,1,
	// 	1,0,0,0,0,0,0,0,0,0,1,
	// 	1,0,0,0,0,0,0,0,0,0,1,
	// 	1,0,0,0,0,0,0,0,0,0,1,
	// 	1,0,0,0,0,0,0,0,0,0,1,
	// 	1,0,0,0,0,0,0,0,0,0,1,
	// 	1,1,1,1,1,1,1,1,1,1,1,1,1
	// };

	// mlx_texture_t *player_tex;
	// mlx_image_t *image_var;
	t_main_thingy main_thingy;
	main_thingy.mlx = mlx_init(WIDTH,HEIGHT, "Chernobyl Cattos", 1);
	mlx_put_string(main_thingy.mlx, "Hello world!", WIDTH/2,HEIGHT/2);
	// player_tex = mlx_load_png("catto.png");
	main_thingy.image_thingy= mlx_new_image(main_thingy.mlx, 50,50);
	mlx_image_to_window(main_thingy.mlx, main_thingy.image_thingy, 50,50);
	int i = 0;
	int j = 0;
	while(i < 50)
	{
		j = 0;
		while(j < 50)
		{
			mlx_put_pixel(main_thingy.image_thingy, i, j, 0x000FFFF);
			j++;
		}
		i++;
	}
	// memset(image_var->pixels, b , image_var->height * image_var->width * sizeof(int));
	// image_var = mlx_texture_to_image(mlx, player_tex);
	// mlx_image_to_window(mlx, image_var, 200, 200);]
	mlx_loop_hook(main_thingy.mlx,&hook, (void *)(&main_thingy));
	mlx_loop(main_thingy.mlx);
	mlx_terminate(main_thingy.mlx);
}