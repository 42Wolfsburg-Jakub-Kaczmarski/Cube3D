/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 21:24:49 by kmilchev          #+#    #+#             */
/*   Updated: 2022/08/03 12:40:03 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_VALIDATION_H
# define MAP_VALIDATION_H
# define ALLOWED_SYMBOLS "102345WESN \n"
# define PLAYER_POS "WESN"
# define VALID_SYMBOLS "012345WESN"
# define SPRITES "2345"
# define TEXTURES 6

enum e_ERRORS
{
	NOTHING,
	FILE_CANNOT_BE_OPENED,
	EMPTY_FILE,
	NOT_ENOUGH_TEXTURES,
	WRONG_TEXTURE_DATA,
	EMPTY_MAP,
	NEW_LINE_WITHIN_MAP,
	ONLY_ONE_PLAYER_ALLOWED,
	UNKNOWN_SYMBOL,
	NOT_ENCLOSED,
	ELEMENT_POSITIONED_WRONG,
	WRONG_AMOUNT_OF_ARGUMENTS,
};

//set_direction.c
void	set_direction(t_mlx_info *mlx_info, char c);

//helpers.c
void	print_2d_array(char **arr);
void	print_int_map(t_mlx_info	*mlx_info);
void	free_2d_safe(char ***arr);
void	free_2d_array(char **arr);
void	free_2d_int_array(int **arr, t_mlx_info	*mlx_info);

//helpers_2.c
int		count_chars(char *str, char c);
int		arr_len(char **arr);
void	get_number_of_lines(t_mlx_info *mlx_info);
int		longest_row(char **map, int rows);
void	set_error_code(t_mlx_info *mlx_info, int num);
void	free_sprites(t_mlx_info *mlx_info);

//textures.c
int		textures_to_arr(t_mlx_info *mlx_info);
int		check_textures_amount(t_mlx_info *mlx_info);
void	check_textures_names(char *texture_name, t_mlx_info *mlx_info);
int		all_textures_are_present(t_mlx_info *mlx_info);

//map_validations.c
int		check_if_right_characs(t_mlx_info *mlx_info);
int		check_if_zeroes_and_player_are_placed_correctly(t_mlx_info *mlx_info);
int		get_number_of_sprites(t_mlx_info *mlx_info);

//create_map.c
int		str_to_char_arr(t_mlx_info *mlx_info);
int		str_to_char_arr2(t_mlx_info *mlx_info, char *line, int i);
void	fill_map_with_0(t_mlx_info *mlx_info, int i, int j);
void	char_to_int_map(t_mlx_info *mlx_info, int i, int j);

//validation.c
void	init_element_booleans(t_mlx_info *mlx_info);
int		longest_row(char **map, int rows);
int		file_input_is_okay(int argc, char *argv[], t_mlx_info *mlx_info);

//check_if_map_index_exists.c
bool	square_exists(t_mlx_info *mlx_info, int i, int j);
bool	square_below_exists(t_mlx_info *mlx_info, int i, int j);
bool	square_above_exists(t_mlx_info *mlx_info, int i, int j);
bool	square_left_exists(t_mlx_info *mlx_info, int i, int j);
bool	square_right_exists(t_mlx_info *mlx_info, int i, int j);

#endif