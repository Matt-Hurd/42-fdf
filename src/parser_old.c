/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhurd <mhurd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/09 19:26:41 by mhurd             #+#    #+#             */
/*   Updated: 2016/10/09 20:20:16 by mhurd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>






#include <stdio.h>






static t_point	*new_point(int x, int y, int z)
{
	t_point *ret;

	ret = (t_point *)ft_memalloc(sizeof(t_point));
	ret->point = ft_make_3d(x, y, z);
	return (ret);
}

static void make_list(char **buff, t_plot *plot)
{
	int		x;
	t_point	*prev;

	x = 0;
	plot->head = new_point(0, 0, ft_atoi(buff[0]));
	plot->z_min = MIN(plot->z_min, ft_atoi(buff[0]));
	plot->z_max = MAX(plot->z_max, ft_atoi(buff[0]));
	prev = plot->head;
	while (++x < plot->width)
	{
		prev->right = new_point(x, 0, ft_atoi(buff[x]));
		prev = prev->right;
		plot->z_min = MIN(plot->z_min, ft_atoi(buff[x]));
		plot->z_max = MAX(plot->z_max, ft_atoi(buff[x]));
	}
}

static void	add_to_list(char **buff, t_plot *plot, int y_pos)
{
	int y;
	int x;
	t_point	*current;
	t_point *prev;

	if (y_pos == 0)
		return make_list(buff, plot);
	y = 0;
	current = plot->head;
	while (++y < y_pos)
		current = current->below;
	x = -1;
	prev = NULL;
	while (++x < plot->width)
	{
		current->below = new_point(x, y, ft_atoi(buff[x]));
		if (prev)
			prev->right = current->below;
		prev = current->below;
		current = current->right;
		plot->z_min = MIN(plot->z_min, ft_atoi(buff[x]));
		plot->z_max = MAX(plot->z_max, ft_atoi(buff[x]));
	}
}

void		parse_file(int fd, t_plot **plot)
{
	char	*buff;
	char	**split;
	int		result;
	int		y;

	*plot = (t_plot *)ft_memalloc(sizeof(t_plot));
	y = 0;
	while ((result = ft_get_next_line(fd, &buff)) > 0)
	{
		(*plot)->width = ft_count_words(buff, 0, ' ');
		split = ft_strsplit(buff, ' ');
		add_to_list(split, *plot, y);
		y++;
	}
	(*plot)->height = y;
}