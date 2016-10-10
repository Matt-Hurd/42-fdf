/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 15:35:03 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/10 01:14:40 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <stdio.h>

void	display_controls(void)
{
	ft_putstr("\
____________________________\n\
CONTROLS:\n\
Translation:\n\
	Y: Key: UP, DOWN\n\
	X: Key: LEFT, RIGHT\n\
\n\
Rotation:\n\
	X: Keypad: 1, 4\n\
	Y: Keypad: 2, 5\n\
	Z: Keypad: 3, 6\n\
\n\
Zoom:\n\
	IN: Keypad: +\n\
	OUT: Keypad: -\n\
____________________________\n\
");
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac == 2)
	{
		display_controls();
		data = (t_data *)ft_memalloc(sizeof(t_data));
		data->plot = parse_file(av[1]);
		draw_everything(data);
	}
	return (0);
}
