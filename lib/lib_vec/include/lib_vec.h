/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_vec.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_VEC_H
# define LIB_VEC_H

# include <math.h>
# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif

cl_float3			normalize(cl_float3 v);
double				dot(cl_float3 v1, cl_float3 v2);
double				get_dist(cl_float3 v);
cl_float3			rot(cl_float3 v, double hor_angle, double vert_angle);
cl_float3			multiply_vec(cl_float3 v, double n);
cl_float3			sub_vec(cl_float3 v1, cl_float3 v2);
cl_float3			add_vec(cl_float3 v1, cl_float3 v2);
cl_float3			div_vec(cl_float3 v1, double n);
cl_float3			dot_div(cl_float3 v1, cl_float3 v2);
cl_float3			not_vec(cl_float3 v);
cl_float3			get_inters(cl_float3 origin, cl_float3 raydir, double t);
cl_float3			product_vec(cl_float3 v1, cl_float3 v2);

#endif
