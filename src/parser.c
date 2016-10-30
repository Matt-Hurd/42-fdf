/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/09 19:26:41 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/30 14:10:50 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

static t_plot	*list_to_array(t_plot *plot, t_list *rows)
{
	int		y;
	int		x;
	char	**buff;
	int		z;

	plot->points = (t_vertex ***)ft_memalloc(sizeof(t_vertex **)
		* plot->height);
	y = -1;
	while (++y < plot->height)
	{
		plot->points[y] = (t_vertex **)ft_memalloc(sizeof(t_vertex *)
			* plot->width);
		buff = ft_strsplit(rows->content, ' ');
		x = -1;
		while (++x < plot->width)
		{
			z = ft_atoi(buff[x]);
			plot->points[y][x] = ft_make_vertex(x, y, z);
			plot->z_min = MIN(z, plot->z_min);
			plot->z_max = MAX(z, plot->z_max);
		}
		rows = rows->next;
	}
	return (plot);
}

t_plot			*parse_file(char *filename)
{
	char	*buff;
	int		result;
	int		fd;
	t_list	*list;
	t_plot	*plot;

	plot = (t_plot *)ft_memalloc(sizeof(t_plot));
	plot->width = -1;
	fd = open(filename, O_RDONLY);
	list = NULL;
	plot->z_min = 2147483647;
	plot->z_max = -2147483648;
	while ((result = ft_get_next_line(fd, &buff)) > 0)
	{
		if (plot->width == -1)
			plot->width = ft_count_words(buff, ' ');
		if (plot->width != ft_count_words(buff, ' '))
			ft_error("Invalid Map");
		ft_lst_add_back(&list, ft_lstnew(buff, ft_strlen(buff) + 1));
		(plot->height)++;
	}
	if (result < 0)
		ft_error_unknown();
	close(fd);
	return (list_to_array(plot, list));
}
