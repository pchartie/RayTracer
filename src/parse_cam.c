/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	parse_cam(t_infos *i, char **split)
{
	if (split[0] != 0)
	{
		if (ft_strcmp(split[0], "\tPOS") == 0
			&& split[1] != 0 && split[2] != 0 && split[3] != 0)
		{
			i->cam_pos.x = ft_atoi(split[1]);
			i->cam_pos.y = -ft_atoi(split[2]);
			i->cam_pos.z = ft_atoi(split[3]);
			i->cam_pos.w = 0;
		}
		else if (ft_strcmp(split[0], "\tDIR") == 0
			&& split[1] != 0 && split[2] != 0 && split[3] != 0)
		{
			i->cam_dir.x = (cl_float)ft_atof(split[1]);
			i->cam_dir.y = (cl_float)ft_atof(split[2]);
			i->cam_dir.z = (cl_float)ft_atof(split[3]);
			i->cam_dir.w = 0;
			if (i->cam_dir.x > 1.0f || i->cam_dir.x < -1.0f
				|| i->cam_dir.y > 1.0f || i->cam_dir.y < -1.0f
				|| i->cam_dir.z > 1.0f || i->cam_dir.z < -1.0f)
				parse_error(15);
		}
		else
			parse_error(6);
	}
}

void		get_cam_value(t_infos *i, int fd, char *line)
{
	char **split;

	while (ft_strcmp(line, "") != 0)
	{
		free(line);
		get_next_line(fd, &line);
		if (ft_strcmp(line, "\t") == 0)
			break ;
		split = ft_strsplit(line, ':');
		parse_cam(i, split);
		free_split(split);
	}
	free(line);
}
