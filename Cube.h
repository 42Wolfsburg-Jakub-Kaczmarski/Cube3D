/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:19:52 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/07 14:52:01 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

#include <fcntl.h>
#include "minilbx/mlx.h"
#include "libft.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define DR 0.0174533 //one degree in radian
#define IMG_SIDE 80
#define PLAYER_SIZE 20
#define WAND_LEN (PLAYER_SIZE)
#define NORTH 3.0/2 * PI
#define SOUTH 1/2.0 * PI
#define WEST PI
#define EAST 0.0f
#define BUFFER_SIZE 1000
# include <unistd.h>
#define ROTATION_SPEED PI / 100
#define PI 3.14159265359
#define DR 0.0174533
#define MOVEMENT_SPEED 5
#define rotationfix (PI / 241)
# if defined(__linux__)
		#define AUDIO "/usr/bin/aplay"
# elif defined(__APPLE__)
		#define AUDIO "/usr/bin/afplay", "--volume", "1"
# else 
	#define AUDIO ""
# endif

#define mapWidth 24
#define mapHeight 24

extern int worldMap[mapWidth][mapHeight];

enum IMG
{
	PLAYER,
	BACKGROUND,
	WALL,
	WAND,
};

typedef struct s_image_s
{
	void *img;
	char *addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}	t_image;

typedef struct s_floor_vars
{
	float rayDirX0;
	float rayDirY0;
	float rayDirX1;
	float rayDirY1;
	int p;
	float posZ;
	float rowDistance;
	float floorStepX;
	float floorStepY;
	float floorX;
	float floorY;
	int	cellX;
	int cellY;
	int	tx;
	int	ty;
	int floor_index;
	int	ceiling_index;
	int color;
}	t_floor_vars;


typedef struct s_draw_prop
{
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int mapX;
	int	mapY;
	int	lineHeight;
	int	drawStart;
	int	drawEnd;
	double	sideDistX;
	double	sideDistY;
	double deltaDistX;
	double deltaDistY;
	int	stepX;
	int	stepY;
	double	perpWallDist;
	int	hit;
	int	side;
	int	texture_num;
	double	wall_X;
	int	texX;
}	t_draw_prop;

typedef struct s_uniq_prop
{
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	double rotSpeed;
	double move_speed;	
	double	posX;
	double	posY;
	int		texWidth;
	int		texHeight;
} t_uniq_prop;

typedef struct s_color
{
	unsigned char b;
	unsigned char g;
	unsigned char r;
	unsigned char a;
}	t_color;

typedef struct s_temp_img
{
	char	*img_data;
	int	img_bp;
	int	img_sl;
	int	img_e;
}	t_temp_img;

typedef struct s_texture
{
	void *img_h;
	t_color	***arr_color;
	int	height;
	int	width;
	void *img_data;
}	t_texture;


typedef struct s_info_mlx{
	void	*mlx;
	t_image	main_img;
	int		window_width;
	int		window_height;
	void	**mlx_imgs;
	t_texture	*texture_data;
	void	*main_win;
	t_floor_vars	floor_info;
	t_uniq_prop	unique_prop;
	t_draw_prop	draw_prop;
}	t_mlx_info;



//Movement
void key_W_hook(t_mlx_info *mlx_info);
void	key_S(t_mlx_info *mlx_info);
void	key_A(t_mlx_info *mlx_info);
void	key_D(t_mlx_info *mlx_info);
void	key_right_arr(t_mlx_info *mlx_info);
void	key_left_arr(t_mlx_info *mlx_info);
int	key_hook(int keycode,void *mlx);


//Rendering
void	render(t_mlx_info *mlx_info);
void	render_textures(t_mlx_info *mlx_info, int x);
void	better_pixel_put(t_image *data, int x, int y, int color);
int draw_line(t_mlx_info *mlx_info,int x, int beginY, int endY, int colour);
void	init_for_drawing(t_mlx_info *mlx_info, int x, int w);
void	check_sideXY(t_mlx_info *mlx_info);
void	hit_loop(t_mlx_info *mlx_info);
t_color *set_color_fstr(t_temp_img *img, int x, int y);
t_color ***create_color_arr(t_temp_img *img, int height, int width);
void	color_walls(t_mlx_info *mlx_info, int x);
void	init_img(t_mlx_info *mlx_info);
void	calculate_wall_texX(t_mlx_info *mlx_info);
void	load_images(t_mlx_info *mlx_info);
void	prep_floor(t_mlx_info *mlx_info, int y);
void	floor_casting(t_mlx_info *mlx_info);

// typedef struct s_mlx_img
// {
//   mlx_t *mlx;
//   //Index 0 reserved for the player
//   mlx_image_t **img_arr;
//   float px;
//   float py;
//   float pdx;
//   float pdy;
//   float pa;
//   float wx;
//   float wy;
//   char **map;
//   int map_height;
//   int map_width;
//   double dir;
// } t_mlx;

// int	check_map(char **argv, t_mlx *mlx_info);

// //Get_next_line
// char	*get_next_line(int fd);
// size_t	ft_strlen(const char *ch);
// void	*ft_memset(void *ptr, int value, size_t num);
// void	*ft_memmove(void *dest, const void *src, size_t n);
// char	*ft_strrchr(const char *s, int c);
// void	*ft_calloc(size_t nmemb, size_t size);

// ///keys.c
// void key_w(t_mlx *data);
// void key_s(t_mlx *data);
// void key_a(t_mlx *data);
// void key_d(t_mlx *data);
// void key_left_arrow(t_mlx *data);
// void key_right_arrow(t_mlx *data);

// //draw.c
// int draw_line(mlx_image_t *img,int x, int beginY, int endY, int colour);
// void draw_wand(t_mlx *mlx_info);
// void draw_grid(t_mlx *mlx);
// void draw_player(t_mlx *mlx_info);

// //main.c
// void load_textures(t_mlx *mlx);
// bool check_movement(t_mlx *data);
// int draw_rays(t_mlx *mlx_info);
#endif
