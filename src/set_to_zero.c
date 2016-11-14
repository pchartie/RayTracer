/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_to_zero.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	set_to_zero_light(t_infos *i, cl_uchar2 m)
{
	int		k;

	k = -1;
	while (++k < m.x)
	{
		i->light_pos[k].x = 0;
		i->light_pos[k].y = 0;
		i->light_pos[k].z = 0;
		i->light_pos[k].w = 0;
		i->light_coef[k] = 0;
		i->light_color[k] = 0;
		i->light_id[k] = 0;
	}
}

static void	set_to_zero_ambient(t_infos *i)
{
	i->ambient.x = 0;
	i->ambient.y = 0;
	i->ambient2.x = 0;
	i->ambient2.y = 0;
	i->ambient2.z = 0;
	i->ambient2.w = 0;
}

static void	set_to_zero_obj_generalities(t_infos *i, int k)
{
	i->obj_pos[k].x = 0;
	i->obj_pos[k].y = 0;
	i->obj_pos[k].z = 0;
	i->obj_pos[k].w = 0;
	i->obj_dir[k].x = 0;
	i->obj_dir[k].y = 0;
	i->obj_dir[k].z = 0;
	i->obj_dir[k].w = 0;
	i->obj_angle[k] = 0;
	i->obj_rayon[k] = 0;
	i->obj_color[k] = 0;
	i->elli_rayon[k].x = 0;
	i->elli_rayon[k].y = 0;
	i->elli_rayon[k].z = 0;
	i->elli_rayon[k].w = 0;
	i->obj_lim[k].x = 0;
	i->obj_lim[k].y = 0;
	i->obj_lim[k].z = 0;
	i->obj_lim[k].w = 0;
	i->obj_indice[k].x = 0;
	i->obj_indice[k].y = 0;
	i->obj_indice[k].z = 0;
	i->obj_indice[k].w = 0;
	i->obj_perlin[k] = 0;
	i->obj_damier[k] = 1;
}

void		set_to_zero_infos(t_infos *i, cl_uchar2 m)
{
	int		k;

	k = 0;
	set_to_zero_ambient(i);
	set_to_zero_light(i, m);
	while (k < m.y)
	{
		set_to_zero_obj_generalities(i, k);
		i->obj_id[k] = 0;
		i->obj_type[k] = 0;
		i->obj_lim_length[k] = 0;
		k++;
	}
}
