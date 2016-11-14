/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	parse_light(t_infos *i, int i_lght, char **split)
{
	if (split[0] != 0)
	{
		if (ft_strcmp(split[0], "\tPOS") == 0
				&& split[1] != 0 && split[2] != 0 && split[3] != 0)
		{
			i->light_pos[i_lght].x = ft_atoi(split[1]);
			i->light_pos[i_lght].y = -ft_atoi(split[2]);
			i->light_pos[i_lght].z = ft_atoi(split[3]);
		}
		else if (ft_strcmp(split[0], "\tCOEF") == 0
				&& split[1] != 0)
		{
			i->light_coef[i_lght] = (cl_float)ft_atof(split[1]);
			if (i->light_coef[i_lght] > 1.0f || i->light_coef[i_lght] < 0.0f)
				parse_error(10);
		}
		else if (ft_strcmp(split[0], "\tCOLOR") == 0
				&& split[1] != 0)
			i->light_color[i_lght] = (cl_uint)ft_atoi_base(split[1], 16);
		else
			parse_error(7);
		i->light_id[i_lght] = (cl_uchar)i_lght;
	}
}

void		get_light_value(t_infos *i, int i_lght, int fd, char *line)
{
	char **split;

	while ((ft_strcmp(line, "") != 0))
	{
		free(line);
		get_next_line(fd, &line);
		if (ft_strcmp(line, "\t") == 0)
			break ;
		split = ft_strsplit(line, ':');
		parse_light(i, i_lght, split);
		free_split(split);
	}
	free(line);
}
