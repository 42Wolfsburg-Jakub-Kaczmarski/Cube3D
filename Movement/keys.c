/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:43:05 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/15 14:17:01 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cube.h"
#include "../src/input_validation_and_map_creation/map_validation.h"

void key_W_hook(t_mlx_info *mlx_info)
{
	t_uniq_prop *prop;

	printf("Up________________________\n");
	prop = &(mlx_info->unique_prop);
	int x = (int)prop->posX + (int)prop->dirX * (int)prop->move_speed;
	int y = (int)prop->posY - (int)prop->dirY * (int)prop->move_speed;
	// printf("Current x: %d\n", (int)prop->posX);
	// printf("Current y: %d\n", (int)prop->posY );
	// printf("Speed: %d\n", (int)prop->move_speed);
	// printf("Additional x: %d\n", (int)prop->dirX * (int)prop->move_speed);
	// printf("Substract y: %d\n", (int)prop->dirY * (int)prop->move_speed );
	// 	printf("Projected x: %d\n", x);
	// 	printf("Projected y: %d\n", y);
	// printf("Status %d\n", (x > 1 && x < mapHeight - 1));
	// printf("here\n");
	if( 
		worldMap[x][y] != 1)
	{
		printf("Square value: %d\n", worldMap[x][y]);
		printf("Current x: %d\n", x);
		printf("Current y: %d\n", y);
		prop->posX += prop->dirX * prop->move_speed;
		prop->posY += prop->dirY * prop->move_speed;
	}
	// if(( x2 > 1 && x2 < mapHeight - 1) && (y2 > 1 && y2 < mapWidth) &&
	// 	worldMap[(int)prop->posX][(int)prop->posY - (int)prop->dirY * (int)prop->move_speed ] != 1)
	// {
	// }
}

void	key_S(t_mlx_info *mlx_info)
{
	t_uniq_prop *prop;

	printf("Down________________________\n");
	prop = &(mlx_info->unique_prop);
	int x = (int)prop->posX - (int)prop->dirX * (int) prop->move_speed;
	int y = (int)prop->posY;
	printf("x: %d\n", x);
	printf("y: %d\n", y);
	if((x > 0 && x < mapHeight -2 ) && (y > 1 && y < mapWidth - 2) &&
		worldMap[x][y] != 1)
	{
		printf("Square value: %d\n", worldMap[x][y]);
		printf("Current x: %d\n", x);
		printf("Current y: %d\n", y);
		prop->posX -= prop->dirX * prop->move_speed;
		prop->posY -= prop->dirY * prop->move_speed;
	}
}

void	key_A(t_mlx_info *mlx_info)
{
	t_uniq_prop *prop;

	printf("Left________________________\n");
	prop = &(mlx_info->unique_prop);
	int x = (int)prop->posX - (int)prop->planeX * (int)prop->move_speed;
	int y = (int)prop->posY - (int)prop->planeY * (int)prop->move_speed;
	if(worldMap[x][y] != 1)
	{
		printf("Square value: %d\n", worldMap[x][y]);
		printf("Current x: %d\n", x);
		printf("Current y: %d\n", y);
		prop->posX -= prop->planeX * prop->move_speed;
		prop->posY -= prop->planeY * prop->move_speed;
	}
}

void	key_D(t_mlx_info *mlx_info)
{
	t_uniq_prop *prop;

	printf("Right________________________\n");
	prop = &(mlx_info->unique_prop);
	int x = (int)prop->posX - (int)prop->planeX * (int)prop->move_speed;
	int y = (int)prop->posY - (int)prop->planeY * (int)prop->move_speed;
	if(worldMap[x][y] != 1)
	{
		printf("Square value: %d\n", worldMap[x][y]);
		printf("Current x: %d\n", x);
		printf("Current y: %d\n", y);
		prop->posX += prop->planeX * prop->move_speed;
		prop->posY += prop->planeY * prop->move_speed;

	}
}
