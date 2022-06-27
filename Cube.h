/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:19:52 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/06/27 21:39:58 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

#include <fcntl.h>
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
#define BUFFER_SIZE 1000
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
  char **map;
} mai_t;

int	check_map(char **argv, mai_t *mlx_info);

//Get_next_line
char	*get_next_line(int fd);
size_t	ft_strlen(const char *ch);
void	*ft_memset(void *ptr, int value, size_t num);
void	*ft_memmove(void *dest, const void *src, size_t n);
char	*ft_strrchr(const char *s, int c);
void	*ft_calloc(size_t nmemb, size_t size);

#endif