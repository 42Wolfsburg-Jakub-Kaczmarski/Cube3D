/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:43:05 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/15 15:27:41 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cube.h"
#include "../src/input_validation_and_map_creation/map_validation.h"

void key_W_hook(t_mlx_info *mlx_info)
{
	t_uniq_prop *prop;

	printf("Up________________________\n");
	prop = &(mlx_info->unique_prop);
	int x = (int)prop->posX + (int)(prop->dirX * prop->move_speed);
	int y = (int)prop->posY - (int)(prop->dirY * prop->move_speed);
	double temp_X = prop->posX + prop->dirX * prop->move_speed;
	double temp_Y = prop->posY + prop->dirY * prop->move_speed;
	printf("Current x: %d\n", (int)prop->posX);
	printf("Current y: %d\n", (int)prop->posY );
	printf("Speed: %d\n", (int)prop->move_speed);
	printf("Additional x: %d\n", (int)prop->dirX * (int)prop->move_speed);
	printf("Substract y: %d\n", (int)prop->dirY * (int)prop->move_speed );
		printf("Projected x: %d\n", x);
		printf("Projected y: %d\n", y);
	printf("Status %d\n", (x > 1 && x < mapHeight - 1));
	printf("here\n");
	if( temp_X > 1 && temp_X < mapWidth - 1 && temp_Y > 1 && temp_Y < mapHeight - 1)
	{
		printf("Passed first check\n");
		printf("Square value: %d\n", worldMap[x][y]);
		if (worldMap[x][y] != 2)
		{
			printf("Square value: %d\n", worldMap[x][y]);
			printf("Current x in: %d\n", x);
			printf("Current y in: %d\n", y);
			printf("Position X: %f\n", prop->posX + prop->dirX * prop->move_speed);
			prop->posX += prop->dirX * prop->move_speed;
			prop->posY += prop->dirY * prop->move_speed;
		}
		else
		{
			printf("why am I even here????\n");
		}
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
	int y = (int)prop->posY - (int)prop->dirY * (int)prop->move_speed ;
	double temp_X = prop->posX - prop->dirX * prop->move_speed;
	double temp_Y = prop->posY - prop->dirY * prop->move_speed;
	printf("x: %d\n", x);
	printf("y: %d\n", y);
	if( temp_X > 1 && temp_X < mapWidth - 1 && temp_Y > 1 && temp_Y < mapHeight - 1 &&
		worldMap[x][y] != 1)
	{
		printf("Square value: %d\n", worldMap[x][y]);
		printf("Current x in: %d\n", x);
		printf("Current y in: %d\n", y);
		printf("Position X: %f\n", prop->posX - prop->dirX * prop->move_speed);
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
	double temp_X = prop->posX - prop->planeX * prop->move_speed;
	double temp_Y = prop->posY - prop->planeY * prop->move_speed;
	printf("Current x: %d\n", (int)prop->posX);
	printf("Current y: %d\n", (int)prop->posY );
	printf("Speed: %d\n", (int)prop->move_speed);
	printf("Change of x: %f\n", prop->planeX * (int)prop->move_speed);
	printf("Change of y: %f\n", prop->planeY * (int)prop->move_speed);
		printf("Projected x: %d\n", x);
		printf("Projected y: %d\n", y);
	printf("Status %d\n", (x > 1 && x < mapHeight - 1));
	if(temp_X > 1 && temp_X < mapWidth - 1 && temp_Y > 1 && temp_Y < mapHeight - 1 &&
		worldMap[x][y] != 1)
	{
		printf("Square value: %d\n", worldMap[x][y]);
		printf("Current x in: %d\n", x);
		printf("Current y in: %d\n", y);
		prop->posX -= prop->planeX * prop->move_speed;
		prop->posY -= prop->planeY * prop->move_speed;
	}
}

void	key_D(t_mlx_info *mlx_info)
{
	t_uniq_prop *prop;

	printf("Right________________________\n");
	
	prop = &(mlx_info->unique_prop);
	int x = prop->posX - (int)prop->planeX * (int)prop->move_speed;
	int y = prop->posY - (int)prop->planeY * (int)prop->move_speed;
	double temp_X = prop->posX + prop->planeX * prop->move_speed;
	double temp_Y = prop->posY + prop->planeY * prop->move_speed;
	printf("Current x: %d\n", (int)prop->posX);
	printf("Current y: %d\n", (int)prop->posY );
	printf("Speed: %d\n", (int)prop->move_speed);
	printf("Change of x: %f\n", prop->planeX * (int)prop->move_speed);
	printf("Change of y: %f\n", prop->planeY * (int)prop->move_speed);
		printf("Projected x: %d\n", x);
		printf("Projected y: %d\n", y);
	printf("Status %d\n", (x > 1 && x < mapHeight - 1));

	
	if(temp_X > 1 && temp_X < mapWidth - 1 && temp_Y > 1 && temp_Y < mapHeight - 1 &&
		worldMap[x][y] != 1)
	{
		printf("Square value: %d\n", worldMap[x][y]);
		printf("Current x in: %d\n", x);
		printf("Current y in: %d\n", y);
		prop->posX += prop->planeX * prop->move_speed;
		prop->posY += prop->planeY * prop->move_speed;

	}
}
