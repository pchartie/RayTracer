/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	check_parse(t_parse p)
{
	if (p.ambient == 0)
		parse_error(16);
	if (p.i_lght == 0)
		parse_error(17);
	if (p.cam == 0)
		parse_error(18);
	if (p.ambient != 1)
		parse_error(12);
	if (p.cam != 1)
		parse_error(8);
	if (p.i_obj > 255)
		parse_error(28);
	if (p.i_lght > 255)
		parse_error(29);
}

static void	parse3(t_infos *i, t_parse *p, int fd, char *line)
{
	if (ft_strcmp(line, "SPHERE:") == 0)
	{
		get_sphere_value(i, p->i_obj, fd, line);
		p->i_obj++;
	}
	else if (ft_strcmp(line, "CONE:") == 0)
	{
		get_cone_value(i, p->i_obj, fd, line);
		p->i_obj++;
	}
	else if (ft_strcmp(line, "ELLIPSOID:") == 0)
	{
		get_ellipsoid_value(i, p->i_obj, fd, line);
		p->i_obj++;
	}
	else if (ft_strcmp(line, "AMBIENT:") == 0)
	{
		get_ambient_value(i, fd, line);
		p->ambient++;
	}
	else
		free(line);
}

static void	parse2(t_infos *i, t_parse *p, int fd, char *line)
{
	if (ft_strcmp(line, "CAM:") == 0)
	{
		get_cam_value(i, fd, line);
		p->cam++;
	}
	else if (ft_strcmp(line, "LIGHT:") == 0)
	{
		get_light_value(i, p->i_lght, fd, line);
		p->i_lght++;
	}
	else if (ft_strcmp(line, "PLANE:") == 0)
	{
		get_plane_value(i, p->i_obj, fd, line);
		p->i_obj++;
	}
	else if (ft_strcmp(line, "CYLINDER:") == 0)
	{
		get_cylinder_value(i, p->i_obj, fd, line);
		p->i_obj++;
	}
	else
		parse3(i, p, fd, line);
}

t_infos		*parse(t_infos *i, cl_uchar2 m, char *scene)
{
	int		fd;
	char	*line;
	t_parse	p;

	p.i_lght = 0;
	p.i_obj = 0;
	p.cam = 0;
	p.ambient = 0;
	malloc_t_infos(i, m);
	fd = open(scene, O_RDONLY);
	if (fd <= 0)
		parse_error(5);
	while (get_next_line(fd, &line))
	{
		parse2(i, &p, fd, line);
	}
	free(line);
	close(fd);
	check_parse(p);
	return (i);
}
