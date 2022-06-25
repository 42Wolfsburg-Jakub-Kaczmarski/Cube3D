/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:19:52 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/06/25 15:35:19 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE
#define CUBE

#include <stdio.h>
#include <math.h>
#include <stdlib.h>



#define PI 3.14159265359

typedef struct mlx_and_image
{
  mlx_t *mlx;
  //Index 0 reserved for the player
  mlx_image_t **img_arr;
    
} mai_t;

#endif