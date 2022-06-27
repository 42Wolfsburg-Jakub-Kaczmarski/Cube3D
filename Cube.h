/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:19:52 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/06/27 15:11:44 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

#include "MLX42/include/MLX42/MLX42.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define IMG_SIDE 80
#define ROWS 12
#define COLS 6
#define PLAYER_SIZE 20
#define WINDOW_WIDTH ((ROWS * IMG_SIDE) + ROWS - 1)
#define WINDOW_HEIGHT ((COLS * IMG_SIDE) + COLS - 1)

# include <unistd.h>
#define PI 3.14159265359
# if defined(__linux__)
    #define AUDIO "/usr/bin/aplay"
# elif defined(__APPLE__)
    #define AUDIO "/usr/bin/afplay", "--volume", "1"
# else 
	#define AUDIO ""
# endif
typedef struct mlx_and_image
{
  mlx_t *mlx;
  //Index 0 reserved for the player
  mlx_image_t **img_arr;
  float px;
  float py;
  float pdx;
  float pdy;
  float pa;
} mai_t;

int	check_map(char **argv);

#endif