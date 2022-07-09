/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 10:42:55 by kmilchev          #+#    #+#             */
/*   Updated: 2022/07/09 22:13:05 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cube.h"

#define mapWidth 24
#define mapHeight 24
#define texWidth 64
#define texHeight 64

void cast_rays(t_ray_casting* data, t_mlx* mlx_info);
void draw_line(mlx_image_t *img, int x, int beginY, int endY, int colour)
{
	while(beginY < endY)
	{
		mlx_put_pixel(img, x, beginY, colour);
		beginY++;
	}	
}


int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


void  movement_hook(void *x)
{
  t_mlx *data;
  
  data = x;
	mlx_delete_image(data->mlx, data->img_arr[ALL]);
	data->img_arr[ALL] = mlx_new_image(data->mlx, screenWidth, screenHeight);
	// data->img_arr[ALL]->instances->z
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		key_w(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		key_s(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		key_d(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		key_a(data);
	if(mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		key_left_arrow(data);
	if(mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		key_right_arrow(data);
	
	cast_rays(&data->data, data);
}

void init_data_for_ray_cast(t_ray_casting *data)
{
	data->posX = 22;
	data->posY = 12;
	data->dirX = -1;
	data->dirY = 0;
	data->plane_X = 0;
	data->plane_Y = 0.66;
	data->time = 0;
}

void get_wall_X_and_x_coord_of_texture(t_ray_casting* ray, t_mlx* mlx_info)
{
	mlx_info->tex_num = worldMap[ray->mapX][ray->mapY] - 1;
	//calculate value of wall_X
	if (ray->side == 0)
	{
		mlx_info->wall_X = ray->posY + ray->perp_wall_dist * ray->rayDirY;
	}
	else
	{
		mlx_info->wall_X = ray->posX + ray->perp_wall_dist * ray->rayDirX;
	}
	mlx_info->wall_X -= floor((mlx_info->wall_X));

	//x coordinate on the texture
	
	mlx_info->tex_X = (int)(mlx_info->wall_X * (double)(texWidth));
	if (ray->side == 0 && ray->dirX > 0)
	{
		mlx_info->tex_X = texWidth - mlx_info->tex_X - 1;
	}
	if (ray->side == 1 && ray->dirY < 0)
	{
		//////////////////////it is literally the same, so what's up with that?
		mlx_info->tex_X = texWidth - mlx_info->tex_X - 1;
	}
}

void fill_buffer_with_colors(t_ray_casting* ray, t_mlx* data)
{
	int	y;
	
	data->step = 1.0 * texHeight / ray->line_height;
	//starting texture coordinate
	data->tex_position = (ray->draw_start - screenHeight / 2 + ray->line_height / 2) * data->step;
	y = ray->draw_start;
	while(y < ray->draw_end)
	{
		data->tex_Y = (int)data->tex_position & (texHeight - 1);
		data->tex_position += data->step;
		// data->colour = data->texture_arr[data->tex_num].;
		y++;
	}
}
void cast_rays(t_ray_casting* ray, t_mlx* data)
{
	static int i = 0;
	// printf("Take %d\n", i);
	for(int x = 0; x < screenWidth; x++)
	{	
		ray_init(ray, x);
		calculate_step(ray);
		check_if_hit(ray);
		calculate_ray_len(ray);
		get_line_start_end_points(ray);
		///////////////////////
		get_wall_X_and_x_coord_of_texture(ray, data);
		
		
		
		
		//////////////////
		draw_line(data->img_arr[ALL], x, ray->draw_start, ray->draw_end, 0xFF0000FF);
		// draw_line(mlx_info->img_arr[ALL], 2, 100, 200, 0xFF0000FF);
		// printf("%d ", x);
	}
	mlx_image_to_window(data->mlx, data->img_arr[ALL], 0, 0);
}

void textures_to_images(t_mlx *mlx_info)
{
	mlx_info->texture_arr[EAST_IMG] = mlx_load_png("../../images/east_colorstone.png");
	mlx_info->texture_arr[WEST_IMG] = mlx_load_png("../../images/west_bluestone.png");
	mlx_info->texture_arr[NORTH_IMG] = mlx_load_png("../../images/north_redbrick.png");
	mlx_info->texture_arr[SOUTH_IMG] = mlx_load_png("../../images/south_wood.png");
	for (int i = 0; i < 4; i++)
	{
		if (mlx_info->texture_arr[i] == 0)
			printf("SOmething went wrong\n");
		else 
		{
			mlx_info->img_arr[i] = mlx_texture_to_image(mlx_info->mlx, mlx_info->texture_arr[i]);
			mlx_image_to_window(mlx_info->mlx, mlx_info->img_arr[i], i * 20 , i * 10);
			printf("%u\n", mlx_info->img_arr[i]->height);
			printf("%u\n", mlx_info->img_arr[i]->width);
			// mlx_info->img_arr[0].
		}
	}
}

int main(int argc, char *argv[])
{
	t_mlx mlx_info;
	
	init_data_for_ray_cast(&mlx_info.data);
	mlx_info.data.colour = 0xFF0000FF;//RED
	mlx_info.mlx = mlx_init( screenWidth,screenHeight, "Cat shooter", 1);
	mlx_info.texture_arr = calloc(4, sizeof(mlx_texture_t *));
	mlx_info.img_arr = calloc(7, sizeof(mlx_image_t *)); //did not segfault without it?
	mlx_info.img_arr[ALL] = mlx_new_image(mlx_info.mlx, screenWidth, screenHeight);
	textures_to_images(&mlx_info);
	cast_rays(&mlx_info.data, &mlx_info);
	mlx_loop_hook(mlx_info.mlx, &movement_hook, (void*)&mlx_info);
	mlx_loop(mlx_info.mlx);

} 