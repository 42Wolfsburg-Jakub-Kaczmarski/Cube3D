/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_casting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:40:09 by kmilchev          #+#    #+#             */
/*   Updated: 2022/08/10 17:17:16 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube.h"

void	sprite_loop_ctd(t_mlx_info	*m, t_sprite_loop	*l,
	int i, t_render_vars	*v)
{
	while (l->y < m->sprites->draw_end_y)
	{
		
		l->d = d_calculation(*l, m);
		l->tex_y = tex_y_calculation(*l, m, i);
		if(l->tex_x < 0)
		{
			l->tex_x = 0;
		}
		if(l->tex_y < 0)
		{
			l->tex_y = 0;
		}
		v->color = *m->texture_data[i].arr_color[l->tex_x][l->tex_y];	
		add_transparency_to_colour(v);
		v->pix = (v->a << 24) + (v->r << 16) + (v->g << 8) + (v->b);
		if (l->y >= m->window_height || l->y < 0)
			l->y++;
		else if ((v->pix != PIX1 && v->pix != PIX2 && v->pix != PIX3))
		{
			better_pixel_put(&m->main_img, l->stripe, l->y, v->pix);
		}
		l->y++;
	}
}

void	sprite_loop(t_mlx_info *m, int i)
{
	t_render_vars	v;
	t_sprite_loop	l;

	l.stripe = m->sprites->draw_start_x;
	while (l.stripe < m->sprites->draw_end_x)
	{
		// if(l.stripe == 1)
		// {
		// 	l.stripe++;
		// 	continue;
		// }
		// if (l.stripe == 2)
		// {
		// 	l.stripe++;
		// 	continue;
		// }
		// if (l.stripe == 3)
		// {
		// 	l.stripe++;
		// 	continue;
		// }
		// printf("KURWA %d\n", l.stripe);
		l.tex_x = tex_x_calculation(l.stripe, m, i);
		if (check_values(m, l))
		{
			l.y = m->sprites->draw_start_y;
			sprite_loop_ctd(m, &l, i, &v);
		}
		l.stripe++;
	}
}

void	sprite_init_loop(t_mlx_info	*mlx_info, int i)
{
	t_sprite_data	*s;
	double			tmp;

	s = mlx_info->sprites;
	s->sprite_x = s->sprite_arr[s->sprite_order[i]].x
		- mlx_info->unique_prop.pos_x;
	s->sprite_y = s->sprite_arr[s->sprite_order[i]].y
		- mlx_info->unique_prop.pos_y;
	// printf("KURWA 1\n");
	// printf("X %f\n",s->sprite_x );
	// printf("X %f\n",s->sprite_x );
	s->inv_det = 1.0 / (mlx_info->unique_prop.plane_x
			* mlx_info->unique_prop.dir_y
			- mlx_info->unique_prop.dir_x * mlx_info->unique_prop.plane_y);
	s->transform_x = s->inv_det * (mlx_info->unique_prop.dir_y * s->sprite_x
			- mlx_info->unique_prop.dir_x * s->sprite_y);
	s->transform_y = s->inv_det * (-mlx_info->unique_prop.plane_y * s->sprite_x
			+ mlx_info->unique_prop.plane_x * s->sprite_y);
	tmp = s->transform_x / s->transform_y;
	s->sprite_screen_x = (int)((mlx_info->window_width / 2) * (1 + tmp));
	s->u_div = 1;
	s->v_div = 1;
	s->v_move = 0.00;
	s->move_screen = (int)(s->v_move / s->transform_y);
	// printf("KURWA 2\n");
	calc_sprite_height(mlx_info);
	// printf("KURWA 3\n");
	calculate_sprite_width(mlx_info);
	// printf("KURWA 4\n");
	sprite_loop(mlx_info, s->sprite_arr[s->sprite_order[i]].tex_num);
	// printf("KURWA 5\n");
}

void	sprite_casting(t_mlx_info *mlx_info)
{
	int	i;

	i = 0;
	sort_sprites(mlx_info);
	while (i < mlx_info->sprites->sprite_count)
	{
		sprite_init_loop(mlx_info, i);
		i++;
	}
}
