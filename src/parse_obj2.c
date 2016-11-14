/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	get_ind(t_infos *i, char **split, int i_obj)
{
	i->obj_indice[i_obj].w = (cl_float)ft_atof(split[1]);
	if (i->obj_indice[i_obj].w < 0.0f)
		parse_error(9);
}

void	get_ref(t_infos *i, char **split, int i_obj)
{
	i->obj_indice[i_obj].z = (cl_float)ft_atof(split[1]);
	if (i->obj_indice[i_obj].z > 1.0f || i->obj_indice[i_obj].z < 0.0f)
		parse_error(14);
}

void	get_spec(t_infos *i, char **split, int i_obj)
{
	i->obj_indice[i_obj].y = (cl_float)ft_atof(split[1]);
	if (i->obj_indice[i_obj].y < 0.0f)
		parse_error(20);
}

void	get_mat(t_infos *i, char **split, int i_obj)
{
	i->obj_indice[i_obj].x = (cl_float)ft_atof(split[1]);
	if (i->obj_indice[i_obj].x > 1.0f || i->obj_indice[i_obj].x < 0.0f)
		parse_error(19);
}

void	get_pos(t_infos *i, char **split, int i_obj)
{
	i->obj_pos[i_obj].x = ft_atoi(split[1]);
	i->obj_pos[i_obj].y = -ft_atoi(split[2]);
	i->obj_pos[i_obj].z = ft_atoi(split[3]);
}
