/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 14:33:57 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/30 14:33:58 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	void	key_hook_rotation(int keycode, t_data *d)
{
	if (keycode == KEY_ROT_X_U)
		d->xr += 0.05;
	else if (keycode == KEY_ROT_X_D)
		d->xr -= 0.05;
	else if (keycode == KEY_ROT_Y_U)
		d->yr += 0.05;
	else if (keycode == KEY_ROT_Y_D)
		d->yr -= 0.05;
	else if (keycode == KEY_ROT_Z_U)
		d->zr += 0.05;
	else if (keycode == KEY_ROT_Z_D)
		d->zr -= 0.05;
}

static	void	key_hook_translation(int keycode, t_data *d)
{
	if (keycode == KEY_UP)
		d->ytrans += 5;
	else if (keycode == KEY_DOWN)
		d->ytrans -= 5;
	else if (keycode == KEY_LEFT)
		d->xtrans += 5;
	else if (keycode == KEY_RIGHT)
		d->xtrans -= 5;
}

static	void	key_hook_scale(int keycode, t_data *d)
{
	if (keycode == KEY_ZOOM_IN)
		d->scale += 0.1;
	else if (keycode == KEY_ZOOM_OUT)
		d->scale = fabs(d->scale - 0.1);
}

int				expose_hook(t_data *d)
{
	draw_reload(d);
	return (0);
}

int				key_hook(int keycode, t_data *d)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(d->mlx, d->win);
		exit(0);
	}
	key_hook_rotation(keycode, d);
	key_hook_translation(keycode, d);
	key_hook_scale(keycode, d);
	draw_reload(d);
	return (0);
}
