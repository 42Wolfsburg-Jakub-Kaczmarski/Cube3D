/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:19:52 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/03 15:16:33 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

#include <fcntl.h>
#include "MLX42/include/MLX42/MLX42.h"
#include "libft.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define DR 0.0174533 //one degree in radian
#define TEXTURES 6
#define IMG_SIDE 80
#define COLS 12
#define ROWS 6
#define PLAYER_SIZE 20
#define WAND_LEN 30
#define NORTH 3.0/2 * PI
#define SOUTH 1/2.0 * PI
#define WEST PI
#define EAST 0.0f
#define WINDOW_WIDTH ((COLS * IMG_SIDE) + COLS - 1)
#define WINDOW_HEIGHT ((ROWS * IMG_SIDE) + ROWS - 1)
#define BUFFER_SIZE 1000
# include <unistd.h>
#define ROTATION_SPEED PI / 20
#define PI 3.14159265359
#define MOVEMENT_SPEED 4
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

typedef struct s_elements
{
  bool c;
  bool f;
  bool no;
  bool so;
  bool ea;
  bool we;
} t_elements;

typedef struct s_mlx_img
{
  mlx_t			*mlx;
  //Index 0 reserved for the player
  mlx_image_t	**img_arr;
  t_elements	elements;
  float			px;
  float			py;
  float			pdx;
  float			pdy;
  float			pa;
  float			wx;
  float			wy;
  int			fd;
  char			**map;
  char			**textures;
  int			map_height;
  int			map_width;
  double		dir;
} t_mlx;

int	check_map(char **argv, t_mlx *mlx_info);

//Get_next_line
char	*get_next_line(int fd);
size_t	ft_strlen(const char *ch);
void	*ft_memset(void *ptr, int value, size_t num);
void	*ft_memmove(void *dest, const void *src, size_t n);
char	*ft_strrchr(const char *s, int c);
void	*ft_calloc(size_t nmemb, size_t size);

///keys.c
void key_w(t_mlx *data);
void key_s(t_mlx *data);
void key_a(t_mlx *data);
void key_d(t_mlx *data);
void key_left_arrow(t_mlx *data);
void key_right_arrow(t_mlx *data);

//draw.c
int draw_line(mlx_image_t *img,  int beginX, int beginY, int endX, int endY, int colour);
void draw_wand(t_mlx *mlx_info);
void draw_grid(t_mlx *mlx);
void draw_player(t_mlx *mlx_info);

//main.c
void load_textures(t_mlx *mlx);
bool check_movement(t_mlx *data);
#endif
