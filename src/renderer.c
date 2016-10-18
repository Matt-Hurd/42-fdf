/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/09 04:47:42 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/18 11:40:32 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_map(t_data *d)
{
	int x;
	int y;

	y = -1;
	while (++y < d->plot->height)
	{
		x = -1;
		while (++x < d->plot->width)
		{
			if (y < d->plot->height - 1)
				ft_3d_drawline(d, *d->plot->points[y][x]->aligned,
					*d->plot->points[y + 1][x]->aligned);
			if (x < d->plot->width - 1)
				ft_3d_drawline(d, *d->plot->points[y][x]->aligned,
					*d->plot->points[y][x + 1]->aligned);
		}
	}
}

void	setup_world(t_data *d)
{
	float	global_matrix[4][4];
	int		x;
	int		y;

	ft_make_identity_matrix(global_matrix);
	ft_tr_translate(global_matrix,
		-(d->plot->width / 2),
		-(d->plot->height / 2),
		0);
	y = -1;
	while (++y < d->plot->height)
	{
		x = -1;
		while (++x < d->plot->width)
		{
			ft_vec_mult_mat(d->plot->points[y][x]->local,
				global_matrix,
				d->plot->points[y][x]->world);
		}
	}
}

void	calc_aligned(t_data *d)
{
	float	global_matrix[4][4];
	int		y;
	int		x;

	ft_make_identity_matrix(global_matrix);
	ft_tr_rotate(global_matrix, d->xr, d->yr, d->zr);
	ft_tr_scale(global_matrix,
		(WINDOW_SIZE_X * d->scale) / d->plot->width,
		(WINDOW_SIZE_Y * d->scale) / d->plot->height, 0);
	ft_tr_translate(global_matrix,
		WINDOW_SIZE_X / 2 + d->xtrans,
		WINDOW_SIZE_Y / 2 + d->ytrans, 0);
	y = -1;
	while (++y < d->plot->height)
	{
		x = -1;
		while (++x < d->plot->width)
		{
			ft_vec_mult_mat(d->plot->points[y][x]->world,
				global_matrix, d->plot->points[y][x]->aligned);
			d->plot->points[y][x]->aligned->z =
			d->plot->points[y][x]->local->z;
		}
	}
}

void	draw_reload(t_data *d)
{
	calc_aligned(d);
	d->img = mlx_new_image(d->mlx, WINDOW_SIZE_X + 100, WINDOW_SIZE_Y + 100);
	d->pixel_img = mlx_get_data_addr(d->img, &(d->bpp), &(d->s_line), &(d->ed));
	draw_map(d);
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
	mlx_destroy_image(d->mlx, d->img);
}

void	draw_everything(t_data *d)
{
	d->xr = 0.7;
	d->yr = 0.7;
	d->zr = 0.1;
	d->scale = 0.5;
	d->ytrans = 0;
	d->xtrans = 0;
	d->mlx = mlx_init();
	d->win = mlx_new_window(d->mlx, WINDOW_SIZE_X, WINDOW_SIZE_Y, "FdF");
	setup_world(d);
	mlx_expose_hook(d->win, expose_hook, d);
	mlx_hook(d->win, 2, 3, key_hook, d);
	mlx_loop(d->mlx);
}
