/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:19:52 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/07/19 17:37:38 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# define BUFFER_SIZE 1000
# if defined(__linux__)
#  define AUDIO "/usr/bin/aplay"
# elif defined(__APPLE__)
#  define AUDIO "/usr/bin/afplay", "--volume", "1"
# else
#  define AUDIO ""
# endif

enum e_DIREC
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
};

typedef struct s_image_s
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_image;

typedef struct s_floor_vars
{
	float			ray_dir_x0;
	float			ray_dir_y0;
	float			ray_dir_x1;
	float			ray_dir_y1;
	int				p;
	float			pos_z;
	float			row_distance;
	float			floor_step_x;
	float			floor_step_y;
	float			floor_x;
	float			floor_y;
	int				cell_x;
	int				cell_y;
	int				tx;
	int				ty;
	int				floor_index;
	int				ceiling_index;
	int				color;
}					t_floor_vars;

typedef struct s_draw_prop
{
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	int				step_x;
	int				step_y;
	double			perp_wall_dist;
	int				hit;
	int				side;
	int				texture_num;
	double			wall_x;
	int				tex_x;
}					t_draw_prop;

typedef struct s_uniq_prop
{
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	rot_speed;
	double	move_speed;
	double	pos_x;
	double	pos_y;
	int		tex_width;
	int		tex_height;
}					t_uniq_prop;

typedef struct s_color
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	a;
}					t_color;

//needed to norminette render_textures
typedef struct render_texture_variables
{
	int		y;
	int		r;
	int		g;
	int		b;
	int		a;
	int		pix;
	double	step;
	double	tex_pos;
	t_color	color;
}			t_render_vars;

typedef struct s_temp_img
{
	char	*img_data;
	int		img_bp;
	int		img_sl;
	int		img_e;
}				t_temp_img;

typedef struct s_texture
{
	void	*img_h;
	t_color	***arr_color;
	int		height;
	int		width;
	void	*img_data;
}			t_texture;

typedef struct s_elements
{
	bool	c;
	bool	f;
	bool	no;
	bool	so;
	bool	ea;
	bool	we;
}					t_elements;

typedef struct s_info_mlx
{
	void			*mlx;
	t_image			main_img;
	int				window_width;
	int				window_height;
	void			**mlx_imgs;
	t_texture		*texture_data;
	void			*main_win;
	t_floor_vars	floor_info;
	t_uniq_prop		unique_prop;
	t_draw_prop		draw_prop;
	int				direction;
	t_temp_img		*im;
	char			**map_s;
	int				longest_row;
	int				map_height;
	int				file_height;
	int				new_lines;
	int				fd;
	char			**textures;
	t_elements		elements;
	double			dir;
	int				**map;
	int				error_code;
	int				celling_color;
	int				floor_color;
	char			**texture_paths;
	bool			mouse;
}					t_mlx_info;

// Movement
void				key_space(t_mlx_info *mlx_info);
void				key_w(t_mlx_info *mlx_info);
void				key_s(t_mlx_info *mlx_info);
void				key_a(t_mlx_info *mlx_info);
void				key_d(t_mlx_info *mlx_info);
void				key_right_arr(t_mlx_info *mlx_info, int diff_x);
void				key_left_arr(t_mlx_info *mlx_info, int diff_x);
int					key_hook(int keycode, void *mlx);
int					ft_mouse_tracker(t_mlx_info *window);

// Rendering
void				render(t_mlx_info *mlx_info);
void				render_textures(t_mlx_info *mlx_info, int x);
void				better_pixel_put(t_image *data, int x, int y, int color);
void				init_for_drawing(t_mlx_info *mlx_info, int x, int w);
void				check_side_xy(t_mlx_info *mlx_info);
void				hit_loop(t_mlx_info *mlx_info);
t_color				*set_color_fstr(t_temp_img *img, int x, int y);
t_color				***create_color_arr(t_temp_img *img, int height, int width);
void				color_walls(t_mlx_info *mlx_info, int x);
void				init_img(t_mlx_info *mlx_info);
void				calculate_wall_tex_x(t_mlx_info *mlx_info);
void				load_images(t_mlx_info *mlx_info);
void				prep_floor(t_mlx_info *mlx_info, int y);
void				floor_casting(t_mlx_info *mlx_info);
void				get_which_tex(t_mlx_info *mlx_info);
void				calculate_wall_dist(t_mlx_info *mlx_info);
int					convert_to_argb(char *colors_str);
void				get_colors(t_mlx_info *mlx_info);
void				switch_right_tex(t_mlx_info *mlx_info, char *temp, int i);
void				get_textures(t_mlx_info *mlx_info);
int					check_if_tex_exist(t_mlx_info *mlx_info);
void				free_2d_array(char **arr);

// Get_next_line
char				*get_next_line(int fd);
size_t				ft_strlen(const char *ch);
void				*ft_memset(void *ptr, int value, size_t num);
void				*ft_memmove(void *dest, const void *src, size_t n);
char				*ft_strrchr(const char *s, int c);
void				*ft_calloc(size_t nmemb, size_t size);

#endif
