/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambients.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	parse_ambient2(t_infos *i, char **split)
{
	if (ft_strcmp(split[0], "\tNBREFLET") == 0
		&& split[1] != 0)
	{
		i->ambient2.y = (cl_uchar)ft_atoi(split[1]);
		if (ft_atoi(split[1]) > 255 || ft_atoi(split[1]) < 0)
			parse_error(26);
	}
	else if (ft_strcmp(split[0], "\tNBREFRACT") == 0
		&& split[1] != 0)
	{
		i->ambient2.z = (cl_uchar)ft_atoi(split[1]);
		if (ft_atoi(split[1]) > 255 || ft_atoi(split[1]) < 0)
			parse_error(27);
	}
	else
		parse_error(13);
}

static void	parse_ambient(t_infos *i, char **split)
{
	if (ft_strcmp(split[0], "\tCOEF") == 0
		&& split[1] != 0)
	{
		i->ambient.x = (cl_float)ft_atof(split[1]);
		if (i->ambient.x > 1.0f || i->ambient.x < 0.0f)
			parse_error(11);
	}
	else if (ft_strcmp(split[0], "\tFILTER") == 0
		&& split[1] != 0)
	{
		i->ambient.y = (cl_float)ft_atof(split[1]);
		if (i->ambient.y > 1.0f || i->ambient.y < 0.0f)
			parse_error(23);
	}
	else if (ft_strcmp(split[0], "\tFILTERCOLOR") == 0
		&& split[1] != 0)
		i->filter_color = (cl_uint)ft_atoi_base(split[1], 16);
	else if (ft_strcmp(split[0], "\tANTIALIASING") == 0 && split[1] != 0)
	{
		i->ambient2.x = (cl_uchar)ft_atoi(split[1]);
		if ((int)i->ambient2.x < 1 || (int)i->ambient2.x > 4)
			parse_error(24);
	}
	else
		parse_ambient2(i, split);
}

void		get_ambient_value(t_infos *i, int fd, char *line)
{
	char **split;

	while (ft_strcmp(line, "") != 0)
	{
		free(line);
		get_next_line(fd, &line);
		if (ft_strcmp(line, "\t") == 0)
			break ;
		split = ft_strsplit(line, ':');
		if (split[0] != 0)
			parse_ambient(i, split);
		free_split(split);
	}
	free(line);
	if (i->ambient2.x == 0)
		i->ambient2.x = 1;
}
