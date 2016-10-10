/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 16:06:16 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/10 01:13:34 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "mlx.h"
# include "libft.h"
# include "libgfx.h"
# include <fcntl.h>
# include <unistd.h>

# define WINDOW_SIZE_X 1000
# define WINDOW_SIZE_Y 700

/*
** KEYS
*/

# define KEY_ESC 53

# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124

# define KEY_ZOOM_IN 69
# define KEY_ZOOM_OUT 78

# define KEY_ROT_X_U 86
# define KEY_ROT_X_D 83
# define KEY_ROT_Y_U 87
# define KEY_ROT_Y_D 84
# define KEY_ROT_Z_U 88
# define KEY_ROT_Z_D 85

t_plot		*parse_file(char *filename);
void		draw_everything(t_data *d);
#endif