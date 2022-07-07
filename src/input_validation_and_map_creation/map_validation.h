/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 21:24:49 by kmilchev          #+#    #+#             */
/*   Updated: 2022/07/07 23:08:06 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_VALIDATION_H
# define MAP_VALIDATION_H

# include "../../Cube.h"

//helpers.c
void	print_2d_array(char **arr);
void	print_int_map(int **map, t_mlx	*mlx_info);
void	free_2d_array(char **arr);
void	free_2d_int_array(int **arr, t_mlx	*mlx_info);

//helpers_2.c
int		count_chars(char *str, char c);
int		arr_len(char **arr);
void	get_number_of_lines(t_mlx *mlx_info);
int		longest_row(char **map, int rows);

//textures.c
int		textures_to_arr(t_mlx *mlx_info);
int		check_textures_amount(t_mlx *mlx_info);
void	check_textures_names(char *texture_name, t_mlx *mlx_info);
int		all_textures_are_present(t_mlx *mlx_info);

//map_validations.c
int		check_if_right_characs(t_mlx *mlx_info);
int		check_if_zeroes_and_player_are_placed_correctly(t_mlx *mlx_info);

//create_map.c
int		str_to_char_arr(t_mlx *mlx_info);
int		str_to_char_arr2(t_mlx *mlx_info, char *line);
void	fill_map_with_0(t_mlx *mlx_info, int i, int j);
void	char_to_int_map(t_mlx *mlx_info);

//validation.c
void	init_element_booleans(t_mlx *mlx_info);
int		longest_row(char **map, int rows);

//check_if_map_index_exists.c
bool	square_exists(t_mlx *mlx_info, int i, int j);
bool	square_below_exists(t_mlx *mlx_info, int i, int j);
bool	square_above_exists(t_mlx *mlx_info, int i, int j);
bool	square_left_exists(t_mlx *mlx_info, int i, int j);
bool	square_right_exists(t_mlx *mlx_info, int i, int j);

#endif