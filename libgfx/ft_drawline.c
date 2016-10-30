/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 14:36:16 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/30 16:35:57 by mhurd            ###   ########.fr       */
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

void				init_color_table(t_data *d)
{
	int		i;
	float	r[3];
	float	g[3];
	float	b[3];

	d->colors = (int *)malloc(sizeof(int) * 100);
	r[0] = (float)(COLOR1 >> 16 & 0xFF);
	r[1] = (float)(COLOR2 >> 16 & 0xFF);
	g[0] = (float)(COLOR1 >> 8 & 0xFF);
	g[1] = (float)(COLOR2 >> 8 & 0xFF);
	b[0] = (float)(COLOR1 & 0xFF);
	b[1] = (float)(COLOR2 & 0xFF);
	i = -1;
	while (++i < 100)
	{
		r[2] = (float)(r[0] * i) / 100 + (float)(r[1] * (100 - i)) / 100;
		g[2] = (float)(g[0] * i) / 100 + (float)(g[1] * (100 - i)) / 100;
		b[2] = (float)(b[0] * i) / 100 + (float)(b[1] * (100 - i)) / 100;
		d->colors[i] = (int)r[2] << 16 | (int)g[2] << 8 | (int)b[2];
	}
}

static void			find_deltas(float *delta, t_3d p0, t_3d p1)
{
	delta[0] = p1.x - p0.x;
	delta[1] = p1.y - p0.y;
	delta[2] = p1.z - p0.z;
}

static void			draw_point(t_data *d, int x, int y, float z)
{
	int				i;
	unsigned int	color;
	float			which;

	if (x > 0 && y > 0 && x < WINDOW_SIZE_X && y < WINDOW_SIZE_Y)
	{
		which = ((z - d->plot->z_min)
			/ (d->plot->z_max - d->plot->z_min)) * 100;
		color = d->colors[abs((int)which - 1)];
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
		p0.z += delta[2] / fabs(delta[0]);
		p0.x += (p0.x > p1.x) ? -1 : 1;
	}
}
