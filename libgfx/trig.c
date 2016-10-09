/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trig.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 18:22:26 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/09 01:09:03 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgfx.h"

float g_sin_table[360];
float g_cos_table[360];

void	init_trig(void)
{
	int	d;

	d = -1;
	while (++d < 360)
	{
		g_sin_table[d] = sin(d * M_PI / 128.0);
		g_cos_table[d] = cos(d * M_PI / 128.0);
	}
}

float	ft_sin(int x)
{
	return (g_sin_table[ABS((int)x % 360)]);
}

float	ft_cos(int x)
{
	return (g_cos_table[ABS((int)x % 360)]);
}
