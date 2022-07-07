/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:37:02 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/07 17:14:58 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Cube.h"

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,2,2,2,2,2,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,3,0,0,0,0,2,2,2,2,2,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,2,2,2,2,2,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,2,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,3,0,0,0,0,3,0,0,0,3,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,3,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,1},
  {1,2,2,3,3,3,2,2,2,0,0,0,0,0,3,0,0,3,0,0,0,0,0,1},
  {1,2,0,2,0,0,0,0,2,0,0,0,0,0,3,0,0,3,0,0,0,0,0,1},
  {1,2,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,3,0,0,0,0,0,1},
  {1,2,0,2,0,0,0,0,2,0,0,0,0,0,0,0,0,3,0,0,0,0,0,1},
  {1,2,0,3,3,3,3,2,2,0,0,0,0,0,0,0,0,3,0,0,0,0,0,1},
  {1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	init_for_drawing(t_mlx_info *mlx_info, int x, int w)
{
	mlx_info->draw_prop.cameraX = 3 * x / (double) w - 1;
	mlx_info->draw_prop.rayDirX = mlx_info->unique_prop.dirX + mlx_info->unique_prop.planeX 
	* mlx_info->draw_prop.cameraX;
	mlx_info->draw_prop.rayDirY = mlx_info->unique_prop.dirY + mlx_info->unique_prop.planeY 
	* mlx_info->draw_prop.cameraX;
	mlx_info->draw_prop.mapX = (int)mlx_info->unique_prop.posX;
	mlx_info->draw_prop.mapY = (int)mlx_info->unique_prop.posY;
	mlx_info->draw_prop.hit = 0;
	if(mlx_info->draw_prop.rayDirX == 0)
		mlx_info->draw_prop.deltaDistX = 1e30;
	else
		mlx_info->draw_prop.deltaDistX = fabs(1/ mlx_info->draw_prop.rayDirX);
	if(mlx_info->draw_prop.rayDirY == 0)
		mlx_info->draw_prop.deltaDistY = 1e30;
	else
		mlx_info->draw_prop.deltaDistY = fabs(1 / mlx_info->draw_prop.rayDirY);
}

void	check_sideXY(t_mlx_info *mlx_info)
{
	if(mlx_info->draw_prop.rayDirX < 0)
	{
		mlx_info->draw_prop.stepX = -1;
		mlx_info->draw_prop.sideDistX = (mlx_info->unique_prop.posX - mlx_info->draw_prop.mapX) * mlx_info->draw_prop.deltaDistX;
	}else{
		mlx_info->draw_prop.stepX = 1;
		mlx_info->draw_prop.sideDistX = (mlx_info->draw_prop.mapX + 1.0 - mlx_info->unique_prop.posX) * mlx_info->draw_prop.deltaDistX;
	}
	if(mlx_info->draw_prop.rayDirY < 0)
	{
		mlx_info->draw_prop.stepY = -1;
		mlx_info->draw_prop.sideDistY = (mlx_info->unique_prop.posY - mlx_info->draw_prop.mapY) * mlx_info->draw_prop.deltaDistY;
	}else{
		mlx_info->draw_prop.stepY = 1;
		mlx_info->draw_prop.sideDistY = (mlx_info->draw_prop.mapY + 1.0 - mlx_info->unique_prop.posY) * mlx_info->draw_prop.deltaDistY;
	}
}

void	hit_loop(t_mlx_info *mlx_info)
{
	while(mlx_info->draw_prop.hit == 0)
	{
		if(mlx_info->draw_prop.sideDistX < mlx_info->draw_prop.sideDistY)
		{
			mlx_info->draw_prop.sideDistX += mlx_info->draw_prop.deltaDistX;
			mlx_info->draw_prop.mapX += mlx_info->draw_prop.stepX;
			mlx_info->draw_prop.side = 0;
		}else{
			mlx_info->draw_prop.sideDistY += mlx_info->draw_prop.deltaDistY;
			mlx_info->draw_prop.mapY += mlx_info->draw_prop.stepY;
			mlx_info->draw_prop.side = 1;
		}
		if(worldMap[mlx_info->draw_prop.mapX][mlx_info->draw_prop.mapY] > 0)
			mlx_info->draw_prop.hit = 1;
	}
}

void	calculate_wall_dist(t_mlx_info *mlx_info)
{
	if(mlx_info->draw_prop.side == 0)
	{
		mlx_info->draw_prop.perpWallDist = mlx_info->draw_prop.sideDistX - mlx_info->draw_prop.deltaDistX;
	}else{
		mlx_info->draw_prop.perpWallDist = (mlx_info->draw_prop.sideDistY - mlx_info->draw_prop.deltaDistY);
	}
	mlx_info->draw_prop.lineHeight = (int)(mlx_info->window_height / mlx_info->draw_prop.perpWallDist);
	mlx_info->draw_prop.drawStart = -mlx_info->draw_prop.lineHeight / 2 + mlx_info->window_height / 2;
	if(mlx_info->draw_prop.drawStart < 0)
	{
		mlx_info->draw_prop.drawStart = 0;
	}
	mlx_info->draw_prop.drawEnd = mlx_info->draw_prop.lineHeight / 2 + mlx_info->window_height / 2;
	
	if(mlx_info->draw_prop.drawEnd >= mlx_info->window_height)
	{
		mlx_info->draw_prop.drawEnd = mlx_info->window_height - 1;
	}
}

void	color_walls(t_mlx_info *mlx_info, int x)
{
	int color;

	if(worldMap[mlx_info->draw_prop.mapX][mlx_info->draw_prop.mapY] == 1)
		color = 0x00FFFFFF;	
	else if(worldMap[mlx_info->draw_prop.mapX][mlx_info->draw_prop.mapY] == 2)
		color = 0x00FF00FF;
	else if(worldMap[mlx_info->draw_prop.mapX][mlx_info->draw_prop.mapY] == 0)
		color = 0;
	else if(worldMap[mlx_info->draw_prop.mapX][mlx_info->draw_prop.mapY] == 3)
		color = 0x0000FFFF;
	else if(worldMap[mlx_info->draw_prop.mapX][mlx_info->draw_prop.mapY] == 4)
		color = 0x00FFF0FF;
	else
		color = 0;

	if(mlx_info->draw_prop.side == 1)
		color = color / 2;
	draw_line(mlx_info,  x, mlx_info->draw_prop.drawStart, mlx_info->draw_prop.drawEnd, color);
}

void	init_img(t_mlx_info *mlx_info)
{
	//IF there is a leak it's hereeee :)
	mlx_info->main_img.img = mlx_new_image(mlx_info->mlx, mlx_info->window_width, mlx_info->window_height);
	mlx_info->main_img.addr = mlx_get_data_addr(mlx_info->main_img.img, &mlx_info->main_img.bits_per_pixel, &mlx_info->main_img.line_length, &mlx_info->main_img.endian);
}

void	calculate_wall_texX(t_mlx_info *mlx_info)
{
	mlx_info->draw_prop.texture_num = worldMap[mlx_info->draw_prop.mapX][mlx_info->draw_prop.mapY] - 1;
	
	if(mlx_info->draw_prop.side == 0)
	{
		mlx_info->draw_prop.wall_X = mlx_info->unique_prop.posY + mlx_info->draw_prop.perpWallDist
			* mlx_info->draw_prop.rayDirY;
	}else{
		mlx_info->draw_prop.wall_X = mlx_info->unique_prop.posX + mlx_info->draw_prop.perpWallDist 
			* mlx_info->draw_prop.rayDirX;
	}
	mlx_info->draw_prop.wall_X -= floor((mlx_info->draw_prop.wall_X));
	
	//X texture coord
	mlx_info->draw_prop.texX = (int)(mlx_info->draw_prop.wall_X * (double) mlx_info->unique_prop.texWidth);
	if(mlx_info->draw_prop.side == 0 && mlx_info->draw_prop.rayDirX > 0)
	{
		mlx_info->draw_prop.texX = mlx_info->unique_prop.texWidth - mlx_info->draw_prop.texX - 1;
	}
	if(mlx_info->draw_prop.side == 1 && mlx_info->draw_prop.rayDirY < 0)
	{
		mlx_info->draw_prop.texX = mlx_info->unique_prop.texWidth - mlx_info->draw_prop.texX - 1;
	}	
}

void	load_images(t_mlx_info *mlx_info)
{
	t_temp_img img;
	t_temp_img img1;
	t_temp_img img2;
	mlx_info->mlx_imgs = calloc(10,sizeof(void *));
	mlx_info->texture_data = calloc(5,sizeof(*mlx_info->texture_data ));
	mlx_info->mlx_imgs[0] = mlx_xpm_file_to_image(mlx_info->mlx, "wall_2.xpm",& mlx_info->texture_data[0].width, &mlx_info->texture_data[0].height);
	mlx_info->mlx_imgs[1] = mlx_xpm_file_to_image(mlx_info->mlx, "wall_thingy.xpm", & mlx_info->texture_data[1].width, &mlx_info->texture_data[1].height);
	mlx_info->mlx_imgs[2] = mlx_xpm_file_to_image(mlx_info->mlx, "beach.xpm", & mlx_info->texture_data[2].width, &mlx_info->texture_data[2].height);
	// mlx_info->mlx_imgs[3] = mlx_xpm_file_to_image(mlx_info->mlx, "east_texture.xpm", &mlx_info->window_width, &mlx_info->window_height);
	img.img_data = mlx_get_data_addr(mlx_info->mlx_imgs[0], &img.img_bp, &img.img_sl, &img.img_e);
	img1.img_data = mlx_get_data_addr(mlx_info->mlx_imgs[1], &img1.img_bp, &img1.img_sl, &img1.img_e);
	img2.img_data = mlx_get_data_addr(mlx_info->mlx_imgs[2], &img2.img_bp, &img2.img_sl, &img2.img_e);

	mlx_info->texture_data[0].arr_color = create_color_arr(&img,mlx_info->texture_data[0].height, mlx_info->texture_data[0].width);
	mlx_info->texture_data[1].arr_color = create_color_arr(&img1,mlx_info->texture_data[1].height, mlx_info->texture_data[1].width);
	mlx_info->texture_data[2].arr_color = create_color_arr(&img2,mlx_info->texture_data[2].height, mlx_info->texture_data[2].width);

	mlx_info->texture_data[0].img_h = mlx_info->mlx_imgs[0];
	mlx_info->texture_data[1].img_h = mlx_info->mlx_imgs[1];
	mlx_info->texture_data[2].img_h = mlx_info->mlx_imgs[2];
}


void	render_textures(t_mlx_info *mlx_info, int x)
{
	double step = 1.0 * mlx_info->texture_data[mlx_info->draw_prop.texture_num].height / mlx_info->draw_prop.lineHeight;

	double texPos = (mlx_info->draw_prop.drawStart - mlx_info->window_height / 2 + mlx_info->draw_prop.lineHeight / 2) * step;
	
	int y = mlx_info->draw_prop.drawStart;
	while(y < mlx_info->draw_prop.drawEnd)
	{
		// printf("%d height thingy\n", mlx_info->texture_data[mlx_info->draw_prop.texture_num].height );
		// int texY = (int) texPos & (mlx_info->texture_data[mlx_info->draw_prop.texture_num].height - 1);
		texPos += step;
		if(texPos - 1 < 0)
		{
			texPos = 1;
		}else if(texPos - 1 > mlx_info->texture_data[mlx_info->draw_prop.texture_num].height)
		{
			texPos = mlx_info->texture_data[mlx_info->draw_prop.texture_num].height - 1;
		}
		t_color color = *mlx_info->texture_data[mlx_info->draw_prop.texture_num].arr_color[mlx_info->draw_prop.texX][(int)(texPos) - 1];

		// if(x || color.a){}
		int r = color.r & 0xFF;
		int g = color.g & 0xFF;
		int b = color.b & 0xFF;
		int a = color.a & 0xFF;
		// printf("Y start %d : Y end %d \n", y, mlx_info->draw_prop.drawEnd);

		int pix = (a << 24) + (r << 16) + (g << 8) + (b);
		// if(mlx_info->draw_prop.side == 1) pix = (pix >> 1) & 8355711;
		better_pixel_put(&mlx_info->main_img, x, y, pix);
		// draw_line(mlx_info->mlx, x, mlx_info->draw_prop.drawStart, mlx_info->draw_prop.drawEnd, pix);
		y++;
	}
}

void	prep_floor(t_mlx_info *mlx_info, int y)
{
	mlx_info->floor_info.rayDirX0 = mlx_info->unique_prop.dirX - mlx_info->unique_prop.planeX;
	mlx_info->floor_info.rayDirY0 = mlx_info->unique_prop.dirY - mlx_info->unique_prop.planeY;
	mlx_info->floor_info.rayDirX1 = mlx_info->unique_prop.dirX + mlx_info->unique_prop.planeX;
	mlx_info->floor_info.rayDirY1 = mlx_info->unique_prop.dirY + mlx_info->unique_prop.planeY;
	mlx_info->floor_info.p = y - mlx_info->window_height / 2;
	mlx_info->floor_info.posZ = 0.5 * mlx_info->window_height;
	mlx_info->floor_info.rowDistance = mlx_info->floor_info.posZ / mlx_info->floor_info.p;
	mlx_info->floor_info.floorStepX = mlx_info->floor_info.rowDistance * (mlx_info->floor_info.rayDirX1 - mlx_info->floor_info.rayDirX0) / mlx_info->window_width;
	mlx_info->floor_info.floorStepY = mlx_info->floor_info.rowDistance * (mlx_info->floor_info.rayDirY1 - mlx_info->floor_info.rayDirY0) / mlx_info->window_width;
	mlx_info->floor_info.floorX = mlx_info->unique_prop.posX + mlx_info->floor_info.rowDistance * mlx_info->floor_info.rayDirX0;
	mlx_info->floor_info.floorY = mlx_info->unique_prop.posY + mlx_info->floor_info.rowDistance * mlx_info->floor_info.rayDirY0;
}

void	floor_casting(t_mlx_info *mlx_info)
{
	int y = 0;

	while(y < mlx_info->window_height)
	{
		prep_floor(mlx_info, y);
		int t = 0;
		while(t < mlx_info->window_width)
		{
			mlx_info->floor_info.cellX = (int)mlx_info->floor_info.floorX;
			mlx_info->floor_info.cellY = (int)mlx_info->floor_info.floorY;
			mlx_info->floor_info.tx = (int) (mlx_info->texture_data->width * (mlx_info->floor_info.floorX - mlx_info->floor_info.cellX)) & (mlx_info->texture_data->width - 1);
			mlx_info->floor_info.ty = (int) (mlx_info->texture_data->height * (mlx_info->floor_info.floorY - mlx_info->floor_info.cellY)) & (mlx_info->texture_data->height - 1);
			mlx_info->floor_info.floorX += mlx_info->floor_info.floorStepX;
			mlx_info->floor_info.floorY += mlx_info->floor_info.floorStepY;
			
			// int floor_texture = 2;
			// int ceiling_texture = 1;
			// int color;
			better_pixel_put(&mlx_info->main_img, t, y, 0x000000FF);
			better_pixel_put(&mlx_info->main_img, t, mlx_info->window_height - y - 1, 0x0000FFFF);
			t++;
		}
		y++;
	}
}

void	render(t_mlx_info *mlx_info)
{
	int x = 0;
	int w = mlx_info->window_width;
	init_img(mlx_info);
	// mlx_clear_window(mlx_info->mlx, mlx_info->main_win);
	floor_casting(mlx_info);
	while(x < w)
	{
		init_for_drawing(mlx_info, x, w);
		check_sideXY(mlx_info);
		hit_loop(mlx_info);
		calculate_wall_dist(mlx_info);
		calculate_wall_texX(mlx_info);
		render_textures(mlx_info, x);
		// color_walls(mlx_info, x);
		x++;
	};
		mlx_put_image_to_window(mlx_info->mlx, mlx_info->main_win, mlx_info->main_img.img, 0,0);
}

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
	mlx_info->unique_prop.posX = 22;
	mlx_info->unique_prop.posY = 12;
	mlx_info->unique_prop.texWidth = 200;
	mlx_info->unique_prop.texHeight = 200;
	mlx_info->mlx_imgs = calloc(4, sizeof(void *));
	mlx_info->main_win = mlx_new_window(mlx_info->mlx, mlx_info->window_width, mlx_info->window_height, "Starting point");
}

int main(void)
{
	t_mlx_info mlx_info;
	mlx_info.mlx = mlx_init();
	if(!mlx_info.mlx)
		return 0;
	init_main(&mlx_info);
	load_images(&mlx_info);
	// mlx_info.main_img.img = mlx_new_image(mlx_info.mlx, mlx_info.window_width, mlx_info.window_height);
	// mlx_info.mlx_imgs[0] = mlx_png_file_to_image(mlx_info.mlx, "catto_Tex.png", &w, &h);
	// mlx_put_image_to_window(mlx_info.mlx, mlx_info.main_win, 	mlx_info.mlx_imgs[0], 0,0);
	render(&mlx_info);
	// mlx_loop_hook(mlx_info.mlx, frame_render, &mlx_info);
	mlx_hook(mlx_info.main_win, 2,0,key_hook,&mlx_info);
	mlx_loop(mlx_info.mlx);
}
