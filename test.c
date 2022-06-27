/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 17:19:02 by kmilchev          #+#    #+#             */
/*   Updated: 2022/06/27 12:21:06 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "MLX42/include/MLX42/MLX42.h"
// void swap(int *a1, int *a2)
// {
// 	int *temp;
// 	*temp = *a1;
// 	*a1 = *a2;
// 	*a2 = *temp;
// }
// ///Gets the coordinates of two points and draws a line between them.
// //No protection against invalid coordinates
// void draw_line2(int x0, int y0, int x1, int y1, mlx_t *mlx)
// {
// 	mlx_image_t *bg;
// 	bg = mlx_new_image(mlx, 1000, 500);
	
// 	int dx = x1 - x0; //difference between start and end point
// 	int dy = y1 - y0; //difference between start and end point
// 	int quicker = x0;
// 	double error = (double)dx/2;

// 	if (y1 > x1)
// 	{
// 		printf("here?\n");
// 		quicker = y0;
// 		error = (double)dy/2;
// 		swap(&x0, &y0);
// 		swap(&x1, &y1);
// 		swap(&dx, &dy);
// 	}
	
// 	mlx_put_pixel(bg, x0, y0, 0xFFFFFF);
// 	printf("X = %d Y = %d\n", x0, y0);
// 	x0++;
// 	for(; x0 < x1; x0++)
// 	{
// 		error = error - dy;
// 		printf("X = %d Y = %d\n", x0, y0);
// 		if (error < 0)
// 		{
// 			printf("Error %f\n", error);
// 			y0 = y0 + 1;
// 			error = (double)(error + dx);
// 		}
// 		mlx_put_pixel(bg, x0, y0, 0xFF);
// 	}
// 	mlx_put_pixel(bg, x1, y1, 0xFFFFFF);
// 	mlx_image_to_window(mlx, bg, 0, 0);
// 	// mlx_image_to_window(mlx, bg, 0, 0);
// 	mlx_loop(mlx);
// }

typedef struct mlx_and_image
{
  mlx_t *mlx;
  mlx_image_t *bg;
  mlx_image_t *player;
  mlx_image_t *dicky;
    
} mai_t;

int draw_line(mai_t *yes, int beginX, int beginY, int endX, int endY, int colour)
{
	double	deltaX;
	double	deltaY;
	int 	pixels;
	double 	pixelX;
	double 	pixelY;

  	printf("SMORT %i %i %i %i\n",beginX,  beginY,  endX,  endY);
	deltaX = endX - beginX;
	deltaY = endY - beginY;
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	pixelX = beginX;
	pixelY = beginY;
	deltaX /= pixels;
	deltaY /= pixels;
	while (pixels)
	{
		mlx_put_pixel(yes->bg, pixelX, pixelY, colour);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
	return (0);
}


int main(void)
{
	mai_t yes;
	// mlx_image_t *bg;
	
	yes.mlx = mlx_init(1000, 500, "Siemanko", true);
	yes.bg = mlx_new_image(yes.mlx, 1000, 500);
	mlx_image_to_window(yes.mlx, yes.bg, 0, 0);
	draw_line(&yes, 40, 80, 40, 160, 0xFFFFFF);
	mlx_loop(yes.mlx);
}