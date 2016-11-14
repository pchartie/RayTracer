/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	parse_sphere(t_infos *i, char **split, int i_obj)
{
	if (split[0] != 0)
	{
		if (ft_strcmp(split[0], "\tPOS") == 0
			&& split[1] != 0 && split[2] != 0 && split[3] != 0)
			get_pos(i, split, i_obj);
		else if (ft_strcmp(split[0], "\tRAYON") == 0
			&& split[1] != 0)
		{
			i->obj_rayon[i_obj] = ft_atoi(split[1]);
			if (i->obj_rayon[i_obj] < 0)
				parse_error(22);
		}
		else
			get_bonus_value(i, split, i_obj, SPHERE);
		i->obj_type[i_obj] = SPHERE;
		i->obj_id[i_obj] = (cl_uchar)i_obj;
	}
}

void		get_sphere_value(t_infos *i, int i_obj, int fd, char *line)
{
	char **split;

	while ((ft_strcmp(line, "") != 0))
	{
		free(line);
		get_next_line(fd, &line);
		if (ft_strcmp(line, "\t") == 0)
			break ;
		split = ft_strsplit(line, ':');
		parse_sphere(i, split, i_obj);
		free_split(split);
	}
	free(line);
}
