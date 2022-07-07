/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:19:52 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/07 14:49:47 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

#include <fcntl.h>
#include "../MLX42/include/MLX42/MLX42.h"
#include "libft.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480
#define DR 0.0174533 //one degree in radian
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
#define ROTATION_SPEED PI / 50
#define PI 3.14159265359
#define MOVEMENT_SPEED 0.3
# if defined(__linux__)
    #define AUDIO "/usr/bin/aplay"
# elif defined(__APPLE__)
    #define AUDIO "/usr/bin/afplay", "--volume", "1"
# else 
	#define AUDIO ""
# endif

enum IMG
{
  WEST_IMG,
  EAST_IMG,
  NORTH_IMG,
  SOUTH_IMG,
  ALL,
};

typedef struct s_ray_casting
{
	//Player position
	double  posX;
	double  posY;
	//Make sure the camera plane is perpendicular to the direction, but you can change the length of it.
	//Direciton
	double  dirX;
	double  dirY;
  //Plane
	double  plane_X;
	double  plane_Y;
  //the time difference between these two -> how much you should move when a certain key is pressed
  //and for the FPS counter.
	double  time;
	double  old_time;
	//the x-coordinate on the camera plane that the current x-coordinate of the screen represents,
	//done this way so that the right side of the screen will get coordinate 1,
	//the center of the screen gets coordinate 0, and the left side of the screen gets coordinate -1. 
	double  cameraX;
	//Ray direction
	double  rayDirX;
	double  rayDirY;
	//mapX and mapY represent the current square of the map the ray is in.
	int     mapX;
	int     mapY;
	//side_dist_X and side_dist_Y are initially the distance the ray has to travel from its start position
	//to the first x-side and the first y-side. They will be incremented while steps are taken.
	double side_dist_X;
	double side_dist_Y;
	//delta_dist_X and delta_dist_Y are the distance the ray has to travel to go from 1 x-side to the next x-side,
	//or from 1 y-side to the next y-side.
	double delta_dist_X;
	double delta_dist_Y;
	//used later to calculate the length of the ray
	double perp_wall_dist;
	//used to determinate whether or not the coming loop may be ended
	bool  hit;
	int  side; //0 for x-side, 1 for y-side
	//direction indicaiton
	int	stepX;
	int stepY;
	long long int colour;
	int line_height;
	int draw_start;
	int draw_end;
	//for the loop, idk yet
	bool confused;
} t_ray_casting;

typedef struct s_mlx_img
{
  t_ray_casting data;
  mlx_t *mlx;
  //Index 0 reserved for the player
  mlx_image_t	**img_arr;
  mlx_texture_t	**texture_arr;
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

u_int32_t buffer[screenHeight][screenWidth];
int worldMap[mapWidth][mapHeight];

//Get_next_line
char	*get_next_line(int fd);
size_t	ft_strlen(const char *ch);
void	*ft_memset(void *ptr, int value, size_t num);
void	*ft_memmove(void *dest, const void *src, size_t n);
char	*ft_strrchr(const char *s, int c);
void	*ft_calloc(size_t nmemb, size_t size);

///keys.c
// void key_w(t_mlx *data);
// void key_s(t_mlx *data);
// void key_a(t_mlx *data);
// void key_d(t_mlx *data);
// void key_left_arrow(t_mlx *data);
// void key_right_arrow(t_mlx *data);

//main.c
bool check_movement(t_mlx *data);

//raycasting.c
void ray_init(t_ray_casting *data, int i);
void calculate_step(t_ray_casting *data);
void check_if_hit(t_ray_casting *data);
void calculate_ray_len(t_ray_casting *data);
void get_line_start_end_points(t_ray_casting *data);

#endif
