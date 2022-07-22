/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 15:39:16 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/22 21:10:32 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube.h"

void	init_img(t_mlx_info *mlx_info)
{
	// IF there is a leak it's hereeee :)
	mlx_info->main_img.img = mlx_new_image(
			mlx_info->mlx, mlx_info->window_width, mlx_info->window_height);
	mlx_info->main_img.addr = mlx_get_data_addr(mlx_info->main_img.img,
			&mlx_info->main_img.bits_per_pixel,
			&mlx_info->main_img.line_length,
			&mlx_info->main_img.endian);
}

void	floor_casting(t_mlx_info *data)
{
	int	y;
	int	t;

	y = -1;
	while (++y < data->window_height)
	{
		prep_floor(data, y);
		t = -1;
		while (++t < data->window_width)
		{
			data->floor_info.cell_x = (int)data->floor_info.floor_x;
			data->floor_info.cell_y = (int)data->floor_info.floor_y;
			data->floor_info.tx = (int)(data->texture_data->width
					* (data->floor_info.floor_x - data->floor_info.cell_x))
				& (data->texture_data->width - 1);
			data->floor_info.ty = (int)(data->texture_data->height
					* (data->floor_info.floor_y - data->floor_info.cell_y))
				& (data->texture_data->height - 1);
			data->floor_info.floor_x += data->floor_info.floor_step_x;
			data->floor_info.floor_y += data->floor_info.floor_step_y;
			better_pixel_put(&data->main_img, t, y, data->floor_color);
			better_pixel_put(&data->main_img, t, data->window_height - y - 1,
				data->celling_color);
		}
	}
}

static void	check_side_y(t_mlx_info *mlx_info)
{
	if (mlx_info->draw_prop.ray_dir_y < 0)
	{
		mlx_info->draw_prop.step_y = -1;
		mlx_info->draw_prop.side_dist_y = mlx_info->draw_prop.delta_dist_y
			* (mlx_info->unique_prop.pos_y - mlx_info->draw_prop.map_y);
	}
	else
	{
		mlx_info->draw_prop.step_y = 1;
		mlx_info->draw_prop.side_dist_y = mlx_info->draw_prop.delta_dist_y
			* (mlx_info->draw_prop.map_y + 1.0 - mlx_info->unique_prop.pos_y);
	}
}

void	check_side_xy(t_mlx_info *mlx_info)
{
	if (mlx_info->draw_prop.ray_dir_x < 0)
	{
		mlx_info->draw_prop.step_x = -1;
		mlx_info->draw_prop.side_dist_x = mlx_info->draw_prop.delta_dist_x
			* (mlx_info->unique_prop.pos_x - mlx_info->draw_prop.map_x);
	}
	else
	{
		mlx_info->draw_prop.step_x = 1;
		mlx_info->draw_prop.side_dist_x = mlx_info->draw_prop.delta_dist_x
			* (mlx_info->draw_prop.map_x + 1.0 - mlx_info->unique_prop.pos_x);
	}
	check_side_y(mlx_info);
}

void sprite_loop(t_mlx_info *mlx_info, int i)
{
	t_render_vars	v;
	int stripe = mlx_info->sprites->drawStartX;

	while(stripe < mlx_info->sprites->drawEndX)
	{
		int texX = (256 * (stripe - (-mlx_info->sprites->spriteWidth / 2 + mlx_info->sprites->spriteScreenX)) * mlx_info->texture_data[i].width / mlx_info->sprites->spriteWidth) / 256;
		if(mlx_info->sprites->transformY > 0 && stripe > 0 && stripe < mlx_info->window_width && mlx_info->sprites->transformY < mlx_info->sprites->z_buff[stripe])
		{
			int y = mlx_info->sprites->DrawStartY;
			while(y < mlx_info->sprites->DrawEndY)
			{
				int d = (y - mlx_info->sprites->move_screen) * 256 - mlx_info->window_height * 128 + mlx_info->sprites->spriteHeight * 128;
				int texY = ((d * mlx_info->texture_data[i].height) / mlx_info->sprites->spriteHeight) / 256;
				
				v.color = *mlx_info->texture_data[i].arr_color[texX][texY];
				add_transperency_to_colour(&v);
				v.pix = (v.a << 24) + (v.r << 16) + (v.g << 8) + (v.b);
				if(y >=  mlx_info->window_height || y < 0)
				{
					y++;
				}else if((v.pix != 0x393c3e && v.pix != 0xFCFDFF && v.pix != 0x00000))
				{
					// printf("Y val %d\n", y);
					// printf("X val %d\n", stripe);
						better_pixel_put(&mlx_info->main_img,stripe, y, v.pix);
						
				}
				y++;
			}
		}
		stripe++;
	}
}

void	sprite_init_loop(t_mlx_info	*mlx_info, int i)
{
	// int k = 0;
	// while(k < mlx_info->sprites->sprite_count)
	// {
	// 	printf("X %f\n",mlx_info->sprites->sprite_arr[k].x);
	// 	printf("Y %f\n",mlx_info->sprites->sprite_arr[k].y);
	// 	printf("Tx %d\n",mlx_info->sprites->sprite_arr[k].tex_num);
	// 	k++;
	// }
	mlx_info->sprites->sprite_x = mlx_info->sprites->sprite_arr[mlx_info->sprites->sprite_order[i]].x 
		- mlx_info->unique_prop.pos_x;
	// printf("Sprite X %f\n", mlx_info->sprites->sprite_x);
	mlx_info->sprites->sprite_y = mlx_info->sprites->sprite_arr[mlx_info->sprites->sprite_order[i]].y 
		- mlx_info->unique_prop.pos_y; 
	// printf("Sprite Y %f\n", mlx_info->sprites->sprite_y);
	// printf("%f %f\n",  mlx_info->sprites->sprite_x, mlx_info->sprites->sprite_y);
	mlx_info->sprites->invDet = 1.0	 / (mlx_info->unique_prop.plane_x * 
		mlx_info->unique_prop.dir_y - mlx_info->unique_prop.dir_x * mlx_info->unique_prop.plane_y);
	//Its fucked up somewhere here :))
		// printf("%f %f\n", mlx_info->unique_prop.dir_y, mlx_info->unique_prop.dir_x);
	mlx_info->sprites->transformX = mlx_info->sprites->invDet * (mlx_info->unique_prop.dir_y * mlx_info->sprites->sprite_x 
			- mlx_info->unique_prop.dir_x * mlx_info->sprites->sprite_y);

	mlx_info->sprites->transformY =  mlx_info->sprites->invDet * (-mlx_info->unique_prop.plane_y * mlx_info->sprites->sprite_x 
	+ mlx_info->unique_prop.plane_x * mlx_info->sprites->sprite_y);
	
	// printf("Transform X %f\n", mlx_info->sprites->transformX);
	// printf("Transform Y %f\n", mlx_info->sprites->transformY);
	double tmp = mlx_info->sprites->transformX /  mlx_info->sprites->transformY;
	// printf("%f\n", tmp);
	mlx_info->sprites->spriteScreenX = (int)((mlx_info->window_width / 2) * (1 + tmp));
	// mlx_info->sprites->spriteScreenX = (mlx_info->window_width / 2) * (1.0 + (mlx_info->sprites->transformX / mlx_info->sprites->transformY));
	
	mlx_info->sprites->uDiv = 1;
	mlx_info->sprites->vDiv = 1;
	mlx_info->sprites->vMove = 0.00;
	mlx_info->sprites->move_screen = (int)(mlx_info->sprites->vMove / mlx_info->sprites->transformY);
	calc_sprite_height(mlx_info);

	//Sprite width
	calculate_sprite_width(mlx_info);

	sprite_loop(mlx_info,  mlx_info->sprites->sprite_arr[mlx_info->sprites->sprite_order[i]].tex_num);

}

void	sprite_casting(t_mlx_info *mlx_info)
{
	sort_sprites(mlx_info);
	int i = 0;
	while(i < mlx_info->sprites->sprite_count)
	{
		// printf("%d Tex num in the loop\n", mlx_info->sprites->sprite_arr[i].tex_num);
		sprite_init_loop(mlx_info, i);
		i++;
	}
}
// void	sword_casting(t_mlx_info *mlx_info)
// {
// 	int start_x = mlx_info->window_width / 2;
// 	int start_y = 0;
// 	int x = 0;
// 		t_render_vars	v;
// 	int y = 0;
// 	while(x < mlx_info->texture_data[9].height)
// 	{
// 		y = 0;
// 		start_y = 0;
// 		while(y < mlx_info->texture_data[9].width)
// 		{
// 			v.color = *mlx_info->texture_data[4].arr_color[y][x];
// 			add_transperency_to_colour(&v);
// 			v.pix = (v.a << 24) + (v.r << 16) + (v.g << 8) + (v.b);
// 			if((v.pix != 0x393c3e && v.pix != 0xFCFDFF))
// 			{
// 				// better_pixel_put(&mlx_info->main_img,start_x, start_y, v.pix);
// 			}
// 			start_y++;
// 			x++;
// 		};
// 		start_x++;
// 		y++;
// 	}
// }
void	render(t_mlx_info *mlx_info)
{
	int	x;
	int	w;

	x = 0;
	w = mlx_info->window_width;
	init_img(mlx_info);
	floor_casting(mlx_info);
	while (x < w)
	{
		init_for_drawing(mlx_info, x, w);
		check_side_xy(mlx_info);
		hit_loop(mlx_info);
		calculate_wall_dist(mlx_info);
		calculate_wall_tex_x(mlx_info);
		get_which_tex(mlx_info);
		render_textures(mlx_info, x);
		mlx_info->sprites->z_buff[x] = mlx_info->draw_prop.perp_wall_dist;
		x++;
	}
	sprite_casting(mlx_info);
	// sword_casting(mlx_info);
	mlx_put_image_to_window(
		mlx_info->mlx, mlx_info->main_win, mlx_info->main_img.img, 0, 0);
	mlx_put_image_to_window(mlx_info->mlx, mlx_info->main_win, mlx_info->mlx_imgs[9], mlx_info->window_width/ 2 - mlx_info->texture_data[9].width / 2, mlx_info->window_height - mlx_info->texture_data[9].height);
}
