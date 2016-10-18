/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 16:48:59 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/15 11:51:13 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgfx.h"

static int			swap_vars(t_3d *p0, t_3d *p1)
{
	float temp;

	if (fabs(p1->x - p0->x) > fabs(p1->y - p0->y))
		return (0);
	temp = p0->y;
	p0->y = p0->x;
	p0->x = temp;
	temp = p1->y;
	p1->y = p1->x;
	p1->x = temp;
	return (1);
}

static unsigned int	color_by_height(float z, t_data *d)
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
	float			percent;

	percent = (z + fabs(d->plot->z_min)) / (d->plot->z_max - d->plot->z_min);
	percent = MIN(MAX(percent, 0), 1);
	red = ((COLOR2 >> 16) - (COLOR1 >> 16) * percent);
	red += COLOR1 >> 16;
	green = ((COLOR2 >> 8 & 0xFF) - (COLOR1 >> 8 & 0xFF)) * percent;
	green += COLOR1 >> 8 & 0xFF;
	blue = ((COLOR2 & 0xFF) - (COLOR1 & 0xFF)) * percent;
	blue += COLOR1 & 0xFF;
	return (((int)red) << 16 | ((int)green) << 8 | blue);
}

static void			find_deltas(float *delta, t_3d p0, t_3d p1)
{
	delta[0] = p1.x - p0.x;
	delta[1] = p1.y - p0.y;
	delta[2] = p1.z - p0.z;
}

static void			draw_point(t_data *d, int x, int y, int z)
{
	int i;
	int color;

	if (x > 0 && y > 0 && x < WINDOW_SIZE_X && y < WINDOW_SIZE_Y)
	{
		color = color_by_height(z, d);
		i = (x * 4) + (y * d->s_line);
		d->pixel_img[i] = color;
		d->pixel_img[++i] = color >> 8;
		d->pixel_img[++i] = color >> 16;
	}
}

/*
** Bresenham's line algorithm
*/

void				ft_3d_drawline(t_data *d, t_3d p0, t_3d p1)
{
	float	delta[3];
	float	error;
	float	deltaerr;
	int		dir;

	dir = swap_vars(&p0, &p1);
	find_deltas(delta, p0, p1);
	deltaerr = fabs(delta[1] / delta[0]);
	error = -1.0;
	while ((int)p0.x != (int)p1.x)
	{
		draw_point(d, dir ? p0.y : p0.x, dir ? p0.x : p0.y, p0.z);
		error += deltaerr;
		if (error >= 0.0)
		{
			p0.y += (p0.y > p1.y) ? -1 : 1;
			error -= 1.0;
		}
		p0.z -= (p0.z > p1.z) ? -(delta[2] / delta[0]) : delta[2] / delta[0];
		p0.x += (p0.x > p1.x) ? -1 : 1;
	}
}
