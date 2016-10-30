/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libgfx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 14:35:51 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/30 16:37:47 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBGFX_H
# define LIBGFX_H
# include "mlx.h"
# include "libft.h"
# include <stdlib.h>
# include <math.h>
# define ABS(x) ((x > 0) ? x : x * -1)
# define COLOR1 0xa7f442
# define COLOR2 0xc542f4
# define WINDOW_SIZE_X 1000
# define WINDOW_SIZE_Y 700

typedef struct	s_2d
{
	short	x;
	short	y;
}				t_2d;

typedef struct	s_3d
{
	float	x;
	float	y;
	float	z;
}				t_3d;

typedef struct	s_vertex
{
	t_3d	*local;
	t_3d	*world;
	t_3d	*aligned;
}				t_vertex;

typedef struct	s_plot
{
	t_vertex	***points;
	int			width;
	int			height;
	float		z_min;
	float		z_max;
}				t_plot;

typedef struct	s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*pixel_img;
	float	xr;
	float	yr;
	float	zr;
	float	scale;
	float	xtrans;
	float	ytrans;
	int		bpp;
	int		s_line;
	int		ed;
	int		*colors;
	t_plot	*plot;
}				t_data;

void			ft_mat_copy(float source[4][4], float dest[4][4]);
void			ft_mat_mult(float m1[4][4], float m2[4][4], float d[4][4]);
void			ft_vec_mult_mat(t_3d *s, float mat[4][4], t_3d *d);
float			ft_cos(int x);
float			ft_sin(int x);
void			ft_tr_translate(float m[4][4], float tx, float ty, float tz);
void			ft_tr_scale(float matrix[4][4], float sx, float sy, float sz);
void			ft_tr_rotate(float matrix[4][4], float ax, float ay, float az);
void			ft_make_identity_matrix(float matrix[4][4]);
void			ft_3d_drawline(t_data *d, t_3d p1, t_3d p2);
t_3d			*ft_make_3d(int x, int y, int z);
t_vertex		*ft_make_vertex(int x, int y, int z);
void			init_color_table(t_data *d);
#endif
