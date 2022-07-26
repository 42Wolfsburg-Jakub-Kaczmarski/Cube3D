/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:43:05 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/26 21:22:10 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube.h"
#include "../../src/input_validation_and_map_creation/map_validation.h"

enum
{
	UP_LEFT,
	UP_RIGHT,
	DOWN_LEFT,
	DOWN_RIGHT,
};

bool is_diagonal(t_mlx_info *mlx_info, int x1, int y1)
{
	int x;
	int y;
	int diagonal = -1; //put this in struct

	x = mlx_info->unique_prop->pos_x;
	y = mlx_info->unique_prop->pos_y;
	if (x - 1 == x1 && y - 1 == y1)
		diagonal = UP_LEFT;
	else if (x + 1 == x1 && y - 1 == y1)
		diagonal = UP_RIGHT;
	else if (x + 1 == x1 && y + 1 == y1)
		diagonal = DOWN_RIGHT;
	else if (x - 1 == x1 && y + 1 == y1)
		diagonal = DOWN_LEFT;
	if (diagonal == -1)
		return (false);
	return (true);
}

bool movement_is_allowed(t_mlx_info *mlx_info, int x1, int y1)
{

}

void	key_w(t_mlx_info *mlx_info)
{
	t_uniq_prop	*m;
	int			map_x0;
	int			map_y0;

	m = &mlx_info->unique_prop;
	map_x0 = m->pos_x + (m->dir_x * ((m->move_speed + 0)));
	map_y0 = m->pos_y + (m->dir_y * ((m->move_speed + 0)));
	if (mlx_info->map[map_x0][map_y0] != 1)
	{
		if (!(is_diagonal(mlx_info, map_x0, map_y0) && movement_is_allowed(mlx_info, map_x0, map_y0)))
		{
			return ;
		}
		m->pos_y += m->dir_y * m->move_speed;
		m->pos_x += m->dir_x * m->move_speed;
	}
}

void	key_s(t_mlx_info *mlx_info)
{
	t_uniq_prop	*m;
	int			map_x0;
	int			map_y0;

	m = &mlx_info->unique_prop;
	map_x0 = m->pos_x - m->dir_x * (m->move_speed + 0);
	map_y0 = m->pos_y - m->dir_y * (m->move_speed + 0);

	if (mlx_info->map[map_x0][map_y0] != 1)
	{
		m->pos_x -= m->dir_x * m->move_speed;
		m->pos_y -= m->dir_y * m->move_speed;
	}
}

void	key_a(t_mlx_info *mlx_info)
{
	t_uniq_prop	*m;
	int			map_x0;
	int			map_y0;
	double tmp;

	m = &mlx_info->unique_prop;
	tmp = m->plane_x * m->plane_x + m->plane_y * m->plane_y;
	tmp = sqrt(tmp);
	map_x0 = m->pos_x - (m->plane_x / tmp) * (m->move_speed + 0);
	map_y0 = m->pos_y - (m->plane_y / tmp) * (m->move_speed + 0);
	if (mlx_info->map[map_x0][map_y0] != 1)
	{
		m->pos_x -= m->plane_x * m->move_speed;
		m->pos_y -= m->plane_y * m->move_speed ;
	}
}

void	key_d(t_mlx_info *mlx_info)
{
	t_uniq_prop	*m;
	int			map_x0;
	int			map_y0;
	double tmp;
	m = &mlx_info->unique_prop;
	tmp = m->plane_x * m->plane_x + m->plane_y * m->plane_y;
	tmp = sqrt(tmp);
	map_x0 = m->pos_x +( m->plane_x / tmp) * (m->move_speed + 0);
	map_y0 = m->pos_y + (m->plane_y / tmp) * (m->move_speed + 0);
	if (mlx_info->map[map_x0][map_y0] != 1)
	{
		m->pos_x += m->plane_x * m->move_speed ;
		m->pos_y += m->plane_y * m->move_speed ;
	}
}

void	key_space(t_mlx_info *mlx_info)
{
	if (mlx_info->mouse == true)
	{
		mlx_mouse_move(mlx_info->main_win, mlx_info->window_width / 2,
			- mlx_info->window_width / 2);
		mlx_info->mouse = false;
	}
	else if (mlx_info->mouse == false)
		mlx_info->mouse = true;
}


// #include <stdio.h>

// enum
// {
// 	UP_LEFT,
// 	UP_RIGHT,
// 	DOWN_LEFT,
// 	DOWN_RIGHT,
// };

// int main()
// {
// 	int map[5][5] = {
// 		{0, 0, 0, 0, 0},
// 		{0, 3, 1, 4, 0},
// 		{0, 1, 2, 1, 0},
// 		{0, 5, 1, 6, 0},
// 		{0, 0, 0, 0, 0}
// 	};
// 	int x;
// 	int y;
// 	int pos_x;
// 	int pos_y;
// 	int diagonal = -1;
	
	x = 3;
	y = 3;
	pos_x = 2;
	pos_y = 2;
	if (map[x][y] != 1)
	{
		if (pos_x - 1 == x && pos_y -1 == y)
			diagonal = UP_LEFT;
		else if (pos_x + 1 == x && pos_y - 1 == y)
			diagonal = UP_RIGHT;
		else if (pos_x + 1 == x && pos_y + 1 == y)
			diagonal = DOWN_RIGHT;
		else if (pos_x - 1 == x && pos_y + 1 == y)
			diagonal = DOWN_LEFT;
		
// 		printf("Value: %d\n", map[y][x]);
// 		if (diagonal == 0)
// 		{
// 			printf("UP LEFT\n");
// 			if (map[y][x + 1] == 1 && map[y + 1][x] == 1)
// 				printf("Movement not permitted\n");
// 		}
// 		else if (diagonal == 1)
// 		{
// 			printf("UP RIGHT\n");
// 			if (map[y][x - 1] == 1 && map[y + 1][x] == 1)
// 				printf("Movement not permitted\n");
// 		}
// 		else if (diagonal == 2)
// 		{
// 			printf("DOWN LEFT\n");
// 			if (map[y][x + 1] == 1 && map[y - 1][x] == 1)
// 				printf("Movement not permitted\n");
// 		}
// 		else if (diagonal == 3)
// 		{
// 			printf("DOWN RIGHT\n");
// 			if (map[y][x - 1] == 1 && map[y - 1][x] == 1)
// 				printf("Movement not permitted\n");
// 		}
// 		else
// 			printf("IDIOT");
// 	}
// 	else
// 		printf("Not true\n");
// }