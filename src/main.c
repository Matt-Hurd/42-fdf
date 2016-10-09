/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 15:35:03 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/09 01:20:58 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int sample[11][19] = {
	{0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{0, 0, 10, 10,  0,  0, 10, 10,  0,  0,  0, 10, 10, 10, 10, 10,  0,  0,  0},
	{0, 0, 10, 10,  0,  0, 10, 10,  0,  0,  0,  0,  0,  0,  0, 10, 10,  0,  0},
	{0, 0, 10, 10,  0,  0, 10, 10,  0,  0,  0,  0,  0,  0,  0, 10, 10,  0,  0},
	{0, 0, 10, 10, 10, 10, 10, 10,  0,  0,  0,  0, 10, 10, 10, 10,  0,  0,  0},
	{0, 0,  0, 10, 10, 10, 10, 10,  0,  0,  0, 10, 10,  0,  0,  0,  0,  0,  0},
	{0, 0,  0,  0,  0,  0, 10, 10,  0,  0,  0, 10, 10,  0,  0,  0,  0,  0,  0},
	{0, 0,  0,  0,  0,  0, 10, 10,  0,  0,  0, 10, 10, 10, 10, 10, 10,  0,  0},
	{0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	{0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}
};

#include <stdio.h>


#define WINDOW_SIZE_X 1000
#define WINDOW_SIZE_Y 700


void make_array(t_data *d)
{
	int x;
	int y;
	float rot_matrix[4][4];
	float scale_matrix[4][4];
	t_3d **final;
	t_3d *point_source;
	t_3d *point_dest;

	point_source = (t_3d *)ft_memalloc(sizeof(t_3d));
	point_dest = (t_3d *)ft_memalloc(sizeof(t_3d));

	ft_make_identity_matrix(rot_matrix);
	ft_make_identity_matrix(scale_matrix);

	ft_tr_rotate(rot_matrix, 5, 5, 0);
	ft_tr_scale(scale_matrix, WINDOW_SIZE_X / 19, WINDOW_SIZE_Y / 11, 30);
	y = -1;
	final = (t_3d **)ft_memalloc(sizeof(t_3d *) * 11);
	while (++y < 11)
	{
		x = -1;
		final[y] = (t_3d *)ft_memalloc(sizeof(t_3d) * 19);
		while (++x < 19)
		{
			point_source->x = x;
			point_source->y = y;
			point_source->z = sample[y][x];
			ft_vec_mult_mat(point_source, scale_matrix, point_dest);
			ft_vec_mult_mat(point_dest, rot_matrix, &final[y][x]);
			final[y][x].z = point_source->z;
		}
	}

	y = -1;
	while (++y < 11)
	{
		x = -1;
		while (++x < 19)
		{
			printf("(%0.1f, %0.1f, %0.1f), ", final[y][x].x, final[y][x].y, final[y][x].z);
			if (y < 10)
				ft_3d_drawline(d, final[y][x], final[y+1][x]);
			if (x < 18)
				ft_3d_drawline(d, final[y][x], final[y][x+1]);
		}
		printf("\n");
	}
}

int	main(int ac, char **av)
{
	t_data	*d;

	init_trig();
	d = (t_data *)ft_memalloc(sizeof(t_data));
	d->mlx = mlx_init();
	d->win = mlx_new_window(d->mlx, WINDOW_SIZE_X + 20, WINDOW_SIZE_Y + 20, "FdF");
    make_array(d);
    mlx_loop(d->mlx);

	(void)ac;
	(void)av;
	return (0);
}
