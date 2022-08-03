/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 21:53:25 by jkaczmar          #+#    #+#             */
/*   Updated: 2022/08/03 15:31:23 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube.h"

void	load_sprites(t_mlx_info *m)
{
	int		i;
	char	**str;

	str = ft_calloc(4, sizeof(char *));
	str[0] = ft_strdup("./assets/cat_fighter.xpm");
	str[1] = ft_strdup("./assets/cuttlefish.xpm");
	str[2] = ft_strdup("./assets/fish.xpm");
	i = 3;
	while (++i < 7)
	{
	m->mlx_imgs[i] = mlx_xpm_file_to_image(m->mlx, str[i - 4],
				&m->texture_data[i].width,
				&m->texture_data[i].height);
	m->im[i].img_data = mlx_get_data_addr(m->mlx_imgs[i],
				&m->im[i].img_bp,
				&m->im[i].img_sl,
				&m->im[i].img_e);
	m->texture_data[i].arr_color = create_color_arr(&m->im[i],
				m->texture_data[i].height,
				m->texture_data[i].width);
	m->texture_data[i].img_h = m->mlx_imgs[i];
	}
	free_2d_array(str);
}

void	init_sprites(t_mlx_info *mlx_info)
{
	t_sprite_data	*s;

	s = mlx_info->sprites;
	s->z_buff = ft_calloc(mlx_info->window_width, sizeof(double));
	s->sprite_order = ft_calloc(s->sprite_count, sizeof(int));
	s->sprite_distance = ft_calloc(s->sprite_count, sizeof(double));
}
