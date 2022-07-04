/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 21:24:49 by kmilchev          #+#    #+#             */
/*   Updated: 2022/07/03 20:59:21 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_VALIDATION
# define MAP_VALIDATION

#include "../../Cube.h"

//helpers.c
void	print_2d_array(char **arr);
void	free_2d_array(char **arr);
int		arr_len(char **arr);

//textures.c
int		textures_to_arr(t_mlx *mlx_info);
int		check_textures_amount(t_mlx *mlx_info);
void	check_textures_names(char *texture_name, t_mlx *mlx_info);
int		all_textures_are_present(t_mlx *mlx_info);

//map_validations.c
int	map_to_arr(t_mlx *mlx_info);
int	check_if_right_characs(t_mlx *mlx_info);
int check_if_spaces_are_placed_correctly(t_mlx *mlx_info);
int check_boarders(t_mlx *mlx_info);

//validation.c
void	init_element_booleans(t_mlx *mlx_info);
#endif