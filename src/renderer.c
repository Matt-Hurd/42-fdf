/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/09 04:47:42 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/10 01:27:48 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


#include <stdio.h>




void	draw_everything(t_data *d)
{
	//Set up env
	init_trig();
	d->mlx = mlx_init();
	d->win = mlx_new_window(d->mlx, WINDOW_SIZE_X + 20, WINDOW_SIZE_Y + 20, "FdF");

	//Set the global matrix to an identity matrix
	float global_matrix[4][4];
	ft_make_identity_matrix(global_matrix);

	//Translate center to (0,0)
	ft_tr_translate(global_matrix,
		-(d->plot->width / 2),
		-(d->plot->height / 2),
		0);

	ft_tr_scale(global_matrix, 1, 1, 0.1);

	//Rotate the global matrix with the angle of the object
	ft_tr_rotate(global_matrix, 0, 0, 0);

	//Multiply the local coordinates by the global matrix to get the world coordinates
	int x, y;
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
	//Set the global matrix to an identity matrix
	ft_make_identity_matrix(global_matrix);

	//Find new center
	float minx = 1000;
	float miny = 1000; 
	float maxx = -1000;
	float maxy = -1000;
	y = -1;
	while (++y < d->plot->height)
	{
		x = -1;
		while (++x < d->plot->width)
		{
			minx = MIN(d->plot->points[y][x]->world->x, minx);
			maxx = MAX(d->plot->points[y][x]->world->x, maxx);
			miny = MIN(d->plot->points[y][x]->world->y, miny);
			maxy = MAX(d->plot->points[y][x]->world->y, maxy);
		}
	}
	printf("%f, %f, %f, %f\n", minx, maxx, miny, maxy);

	//Scale the global matrix with the scaling of the object
	ft_tr_scale(global_matrix, 
		(WINDOW_SIZE_X * 1) / d->plot->width, 
		(WINDOW_SIZE_Y * 1) / d->plot->height, 
		0);

	//Translate matrix to center of screen
	ft_tr_translate(global_matrix,
		WINDOW_SIZE_X / 2,
		WINDOW_SIZE_Y / 2,
		0);

	//Multiply the world coordinates by the global matrix to get the aligned coordinates
	y = -1;
	while (++y < d->plot->height)
	{
		x = -1;
		while (++x < d->plot->width)
		{
			ft_vec_mult_mat(d->plot->points[y][x]->world, 
				global_matrix, 
				d->plot->points[y][x]->aligned);
			d->plot->points[y][x]->aligned->z = d->plot->points[y][x]->local->z;
		}
	}

	//Draw
	y = -1;
	while (++y < d->plot->height)
	{
		x = -1;
		while (++x < d->plot->width)
		{
			printf("(%0.1f, %0.1f, %0.1f), ", (*d->plot->points[y][x]->aligned).x, (*d->plot->points[y][x]->aligned).y, (*d->plot->points[y][x]->aligned).z);
			if (y < d->plot->height - 1)
				ft_3d_drawline(d, *d->plot->points[y][x]->aligned, *d->plot->points[y+1][x]->aligned);
			if (x < d->plot->width - 1)
				ft_3d_drawline(d, *d->plot->points[y][x]->aligned, *d->plot->points[y][x+1]->aligned);
		}
		printf("\n");
	}
	//loop
    mlx_loop(d->mlx);
}

// void make_array(t_data *d)
// {
// 	int x;
// 	int y;
// 	float rot_matrix[4][4];
// 	float scale_matrix[4][4];
// 	t_3d **final;
// 	t_3d *point_source;
// 	t_3d *point_dest;

// 	point_source = (t_3d *)ft_memalloc(sizeof(t_3d));
// 	point_dest = (t_3d *)ft_memalloc(sizeof(t_3d));

// 	ft_make_identity_matrix(rot_matrix);
// 	ft_make_identity_matrix(scale_matrix);

// 	ft_tr_scale(scale_matrix, WINDOW_SIZE_X / 19, WINDOW_SIZE_Y / 11, 30);
// 	y = -1;
// 	final = (t_3d **)ft_memalloc(sizeof(t_3d *) * 11);
// 	while (++y < 11)
// 	{
// 		x = -1;
// 		final[y] = (t_3d *)ft_memalloc(sizeof(t_3d) * 19);
// 		while (++x < 19)
// 		{
// 			point_source->x = x;
// 			point_source->y = y;
// 			point_source->z = sample[y][x];
// 			ft_vec_mult_mat(point_source, scale_matrix, point_dest);
// 			ft_vec_mult_mat(point_dest, rot_matrix, &final[y][x]);
// 			final[y][x].z = point_source->z;
// 		}
// 	}
// }