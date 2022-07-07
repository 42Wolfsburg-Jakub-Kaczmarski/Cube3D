/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:58:11 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/07 14:58:29 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cube.h"

void	better_pixel_put(t_image *data, int x, int y, int color)
{
	char *dst;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


int draw_line(t_mlx_info *mlx_info,int x, int beginY, int endY, int colour)
{
	int beg_y = beginY;

	while (beg_y < endY)
	{
		better_pixel_put(&mlx_info->main_img ,x, beg_y, colour);
		beg_y++;
	}
	return (0);
}

t_color *set_color_fstr(t_temp_img *img, int x, int y)
{
	int *pix_pos;

	pix_pos = (int *)(img->img_data + (y * img->img_sl + x * (img->img_bp / 8)));

	return (t_color *)pix_pos;
}

t_color ***create_color_arr(t_temp_img *img, int height, int width)
{
	t_color ***color_arr;
	int i;
	int j;
	
	color_arr = calloc(sizeof(t_color **), height + 1);
	j = 0;
	while(j < height)
	{
		color_arr[j] = calloc(sizeof(t_color *), width + 1);
		i = 0;
		while(i < width)
		{
			color_arr[j][i] = set_color_fstr(img, j, i);
			i++;
		}
		j++;
	}
	return color_arr;
}