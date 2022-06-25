/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkaczmar <jkaczmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:19:52 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/06/25 13:34:16 by jkaczmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE
#define CUBE

#include <stdio.h>
#include <math.h>
#include <stdlib.h>


#define WIDTH 1280
#define HEIGHT 768
#define PI 3.14159265359

typedef struct s_main_thingy
{
    mlx_t *mlx;
    mlx_image_t *image_thingy;
}   t_main_thingy;


#endif