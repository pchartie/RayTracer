/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_vec.h"
#include <stdio.h>

cl_float3	rot(cl_float3 v, double hor_angle, double vert_angle)
{
	double tmpx;
	double tmpz;

	tmpz = v.z;
	tmpx = v.x;
	(void)hor_angle;
	v.x = (v.x * cos(vert_angle)) + (tmpz * sin(vert_angle));
	v.z = (tmpx * (-sin(vert_angle))) + (tmpz * cos(vert_angle));
	return (v);
}
