/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 15:35:03 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/18 11:36:44 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <stdio.h>

void	display_usage(char *av)
{
	ft_putstr("usage: ");
	ft_putstr(av);
	ft_putendl(" input_file");
}

void	display_controls(void)
{
	ft_putendl("CONTROLS:\n\
Translation:\n\
	Y: Key: UP, DOWN\n\
	X: Key: LEFT, RIGHT\n\
Rotation:\n\
	X: Keypad: 1, 4\n\
	Y: Keypad: 2, 5\n\
	Z: Keypad: 3, 6\n\
Zoom:\n\
	IN: Keypad: +\n\
	OUT: Keypad: -");
}

int		main(int ac, char **av)
{
	t_data	*data;

	if (ac == 2)
	{
		data = (t_data *)ft_memalloc(sizeof(t_data));
		if (!data)
			ft_error("Malloc Error");
		data->plot = parse_file(av[1]);
		display_controls();
		draw_everything(data);
	}
	else
		display_usage(av[0]);
	return (0);
}
