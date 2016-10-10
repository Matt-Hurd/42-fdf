/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/09 19:26:41 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/09 23:27:27 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

static void	list_to_array(t_plot *plot, t_list *rows)
{
	int		y;
	int		x;
	char	**buff;
	int		z;

	plot->points = (t_vertex ***)ft_memalloc(sizeof(t_vertex **) * plot->height);
	y = -1;
	while (++y < plot->height)
	{
		plot->points[y] = (t_vertex **)ft_memalloc(sizeof(t_vertex *) * plot->width);
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
}

t_plot		*parse_file(char *filename)
{
	char	*buff;
	int		result;
	int		fd;
	t_list	*list;
	t_plot	*plot;

	plot = (t_plot *)ft_memalloc(sizeof(t_plot));
	plot->width = -1;
	plot->height = 0;
	fd = open(filename, O_RDONLY);
	list = NULL;
	while ((result = ft_get_next_line(fd, &buff)) > 0)
	{
		if (plot->width == -1)
			plot->width = ft_count_words(buff, 0, ' ');
		if (plot->width != ft_count_words(buff, 0, ' '))
			return (0); //Error handling here, invalid line size
		ft_lst_add_back(&list, ft_lstnew(buff, sizeof(char) * (ft_strlen(buff) + 1)));
		(plot->height)++;
	}
	list_to_array(plot, list);
	close(fd);
	return (plot);
}