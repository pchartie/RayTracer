/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	get_dir(t_infos *i, char **split, int i_obj, int type)
{
	if (type == PLANE)
	{
		i->obj_dir[i_obj].x = (cl_float)-ft_atof(split[1]);
		i->obj_dir[i_obj].y = (cl_float)-ft_atof(split[2]);
		i->obj_dir[i_obj].z = (cl_float)-ft_atof(split[3]);
		if (i->obj_dir[i_obj].x > 1.0f || i->obj_dir[i_obj].x < -1.0f
			|| i->obj_dir[i_obj].y > 1.0f || i->obj_dir[i_obj].y < -1.0f
			|| i->obj_dir[i_obj].z > 1.0f || i->obj_dir[i_obj].z < -1.0f)
			parse_error(15);
		i->obj_dir[i_obj] = normalize(i->obj_dir[i_obj]);
	}
	else
	{
		i->obj_dir[i_obj].x = (cl_float)ft_atof(split[1]);
		i->obj_dir[i_obj].y = (cl_float)ft_atof(split[2]);
		i->obj_dir[i_obj].z = (cl_float)ft_atof(split[3]);
		if (i->obj_dir[i_obj].x > 1.0f || i->obj_dir[i_obj].x < -1.0f
			|| i->obj_dir[i_obj].y > 1.0f || i->obj_dir[i_obj].y < -1.0f
			|| i->obj_dir[i_obj].z > 1.0f || i->obj_dir[i_obj].z < -1.0f)
			parse_error(15);
		i->obj_dir[i_obj] = normalize(i->obj_dir[i_obj]);
	}
}

void	get_lim(t_infos *i, char **split, int i_obj)
{
	if (ft_strcmp(split[1], "DIR") == 0 && split[2] != 0 && split[3] != 0
		&& split[4] != 0 && split[5] != 0 && split[6] != 0)
	{
		i->obj_lim[i_obj].x = (cl_float)ft_atof(split[2]);
		i->obj_lim[i_obj].y = (cl_float)ft_atof(split[3]);
		i->obj_lim[i_obj].z = (cl_float)ft_atof(split[4]);
		if (i->obj_lim[i_obj].x > 1.0f || i->obj_lim[i_obj].x < -1.0f
			|| i->obj_lim[i_obj].y > 1.0f || i->obj_lim[i_obj].y < -1.0f
			|| i->obj_lim[i_obj].z > 1.0f || i->obj_lim[i_obj].z < -1.0f)
			parse_error(30);
		if (ft_strcmp(split[5], "LEN") == 0)
			i->obj_lim_length[i_obj] = (cl_float)ft_atof(split[6]);
		else
			parse_error(31);
	}
	else
		parse_error(31);
}

void	get_perlin(t_infos *i, char **split, int i_obj)
{
	if (ft_strcmp(split[1], "MARBLE") == 0)
		i->obj_perlin[i_obj] = 1;
	else if (ft_strcmp(split[1], "WOOD") == 0)
		i->obj_perlin[i_obj] = 2;
	else if (ft_strcmp(split[1], "FIRE") == 0)
		i->obj_perlin[i_obj] = 3;
	else if (ft_strcmp(split[1], "WATER") == 0)
		i->obj_perlin[i_obj] = 4;
	else if (ft_strcmp(split[1], "DISCO") == 0)
		i->obj_perlin[i_obj] = 5;
	else if (ft_strcmp(split[1], "MERCURY") == 0)
		i->obj_perlin[i_obj] = 6;
	else if (ft_strcmp(split[1], "0") == 0)
		i->obj_perlin[i_obj] = 0;
	else
		parse_error(25);
}

void	get_bonus_value(t_infos *i, char **split, int i_obj, int type)
{
	if (ft_strcmp(split[0], "\tMAT") == 0
		&& split[1] != 0)
		get_mat(i, split, i_obj);
	else if (ft_strcmp(split[0], "\tSPEC") == 0
		&& split[1] != 0)
		get_spec(i, split, i_obj);
	else if (ft_strcmp(split[0], "\tREF") == 0
		&& split[1] != 0)
		get_ref(i, split, i_obj);
	else if (ft_strcmp(split[0], "\tIND") == 0
		&& split[1] != 0)
		get_ind(i, split, i_obj);
	else if (ft_strcmp(split[0], "\tPERLIN") == 0
		&& split[1] != 0)
		get_perlin(i, split, i_obj);
	else if (ft_strcmp(split[0], "\tLIM") == 0 && split[1] != 0)
		get_lim(i, split, i_obj);
	else if (ft_strcmp(split[0], "\tCOLOR") == 0
		&& split[1] != 0)
		i->obj_color[i_obj] = (cl_uint)ft_atoi_base(split[1], 16);
	else
		parse_error(type);
}
