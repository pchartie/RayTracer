/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		free_split(char **split)
{
	int x;

	x = 0;
	while (split[x])
	{
		free(split[x]);
		x++;
	}
	free(split);
}

cl_uchar2	count_light_n_obj(char *line, cl_uchar2 m)
{
	if (ft_strcmp(line, "LIGHT:") == 0)
		m.x++;
	else if (ft_strcmp(line, "PLANE:") == 0 || ft_strcmp(line, "CONE:") == 0
		|| ft_strcmp(line, "CYLINDER:") == 0 || ft_strcmp(line, "SPHERE:") == 0
		|| ft_strcmp(line, "ELLIPSOID:") == 0)
		m.y++;
	return (m);
}

cl_uchar2	get_m_value(char *scene)
{
	char		*cpy_scene;
	cl_uchar2	m;
	int			fd;
	char		*line;
	int			i;

	i = 0;
	cpy_scene = ft_strdup(scene);
	m.x = 0;
	m.y = 0;
	fd = open(cpy_scene, O_RDONLY);
	free(cpy_scene);
	if (fd <= 0)
		parse_error(5);
	while (get_next_line(fd, &line))
	{
		((!line[0] && i == 0) || ft_isascii(line[0]) == 0) ? parse_error(5) : 0;
		m = count_light_n_obj(line, m);
		i++;
		free(line);
	}
	free(line);
	close(fd);
	return (m);
}

static int	check_for_mallocs(t_infos *i)
{
	if (!i->obj_pos || !i->obj_dir || !i->obj_angle || !i->obj_rayon
	|| !i->obj_lim || !i->obj_lim_length || !i->obj_color || !i->obj_damier
	|| !i->obj_id || !i->obj_type || !i->obj_indice || !i->obj_perlin
	|| !i->elli_rayon || !i->light_pos || !i->light_coef || !i->light_color
	|| !i->light_id)
		return (1);
	return (0);
}

void		malloc_t_infos(t_infos *i, cl_uchar2 m)
{
	i->light_pos = (cl_float4 *)malloc(sizeof(cl_float4) * m.x);
	i->light_coef = (float *)malloc(sizeof(float) * m.x);
	i->light_color = (cl_uint *)malloc(sizeof(cl_uint) * m.x);
	i->light_id = (cl_uchar *)malloc(sizeof(cl_uchar) * m.x);
	i->obj_pos = (cl_float4 *)malloc(sizeof(cl_float4) * m.y);
	i->obj_dir = (cl_float4 *)malloc(sizeof(cl_float4) * m.y);
	i->obj_angle = (cl_uchar *)malloc(sizeof(cl_uchar) * m.y);
	i->obj_rayon = (float *)malloc(sizeof(float) * m.y);
	i->obj_lim = (cl_float4 *)malloc(sizeof(cl_float4) * m.y);
	i->obj_lim_length = (float *)malloc(sizeof(float) * m.y);
	i->obj_color = (cl_uint *)malloc(sizeof(cl_uint) * m.y);
	i->obj_id = (cl_uchar *)malloc(sizeof(cl_uchar) * m.y);
	i->obj_type = (cl_uchar *)malloc(sizeof(cl_uchar) * m.y);
	i->obj_indice = (cl_float4 *)malloc(sizeof(cl_float4) * m.y);
	i->obj_perlin = (cl_uchar *)malloc(sizeof(cl_uchar) * m.y);
	i->obj_damier = (float *)malloc(sizeof(float) * m.y);
	i->elli_rayon = (cl_float4 *)malloc(sizeof(cl_float4) * m.y);
	if (check_for_mallocs(i))
	{
		ft_putstr("Error malloc\n");
		exit(0);
	}
	set_to_zero_infos(i, m);
}
