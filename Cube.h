/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:19:52 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/06/28 21:09:41 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

#include <fcntl.h>
#include "MLX42/include/MLX42/MLX42.h"
#include "42_libft/libft.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define IMG_SIDE 80
#define ROWS 12
#define COLS 6
#define PLAYER_SIZE 20
#define NORTH 3.0/2 * PI
#define SOUTH 1/2.0 * PI
#define WEST PI
#define EAST 0.0f
#define WINDOW_WIDTH ((ROWS * IMG_SIDE) + ROWS - 1)
#define WINDOW_HEIGHT ((COLS * IMG_SIDE) + COLS - 1)
#define BUFFER_SIZE 1000
# include <unistd.h>
#define ROTATION_SPEED PI / 20
#define PI 3.14159265359
#define MOVEMENT_SPEED 2
# if defined(__linux__)
    #define AUDIO "/usr/bin/aplay"
# elif defined(__APPLE__)
    #define AUDIO "/usr/bin/afplay", "--volume", "1"
# else 
	#define AUDIO ""
# endif

enum IMG
{
  PLAYER,
  BACKGROUND,
  WALL,
  WAND,
};

typedef struct s_mlx_img
{
  mlx_t *mlx;
  //Index 0 reserved for the player
  mlx_image_t **img_arr;
  float px;
  float py;
  float pdx;
  float pdy;
  float pa;
  float wx;
  float wy;
  char **map;
  int map_height;
  int map_width;
  double dir;
} t_mlx;

int	check_map(char **argv, t_mlx *mlx_info);

//Get_next_line
char	*get_next_line(int fd);
size_t	ft_strlen(const char *ch);
void	*ft_memset(void *ptr, int value, size_t num);
void	*ft_memmove(void *dest, const void *src, size_t n);
char	*ft_strrchr(const char *s, int c);
void	*ft_calloc(size_t nmemb, size_t size);

#endif