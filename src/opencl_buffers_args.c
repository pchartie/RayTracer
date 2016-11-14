/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_buffers_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	cl_kernel_set_light_buffer(t_graph *graph, cl_uchar2 m, t_infos *i)
{
	graph->light_pos = clCreateBuffer(graph->context, CL_MEM_READ_ONLY |
	CL_MEM_COPY_HOST_PTR, m.x * sizeof(cl_float4), i->light_pos, &graph->ret);
	graph->light_coef = clCreateBuffer(graph->context, CL_MEM_READ_ONLY |
	CL_MEM_COPY_HOST_PTR, m.x * sizeof(float), i->light_coef, &graph->ret);
	graph->light_color = clCreateBuffer(graph->context, CL_MEM_READ_ONLY |
	CL_MEM_COPY_HOST_PTR, m.x * sizeof(cl_uint), i->light_color, &graph->ret);
	graph->light_id = clCreateBuffer(graph->context, CL_MEM_READ_ONLY |
	CL_MEM_COPY_HOST_PTR, m.x * sizeof(cl_uchar), i->light_id, &graph->ret);
	graph->obj_perlin = clCreateBuffer(graph->context, CL_MEM_READ_WRITE |
	CL_MEM_COPY_HOST_PTR, m.y * sizeof(cl_uchar), i->obj_perlin, &graph->ret);
	graph->obj_damier = clCreateBuffer(graph->context, CL_MEM_READ_WRITE |
	CL_MEM_COPY_HOST_PTR, m.y * sizeof(float), i->obj_damier, &graph->ret);
	graph->normals = clCreateBuffer(graph->context, CL_MEM_READ_WRITE,
	(SCRY * SCRX) * sizeof(cl_float4), NULL, &graph->ret);
	graph->elli_rayon = clCreateBuffer(graph->context, CL_MEM_READ_ONLY |
	CL_MEM_COPY_HOST_PTR, m.y * sizeof(cl_float4), i->elli_rayon, &graph->ret);
}

void		cl_kernel_set_buffer(t_graph *graph, cl_uchar2 m, t_infos *i)
{
	graph->data = clCreateBuffer(graph->context, CL_MEM_READ_WRITE, (MEM_SIZE)
			* sizeof(char), NULL, &graph->ret);
	graph->obj_pos = clCreateBuffer(graph->context, CL_MEM_READ_ONLY |
	CL_MEM_COPY_HOST_PTR, m.y * sizeof(cl_float4), i->obj_pos, &graph->ret);
	graph->obj_dir = clCreateBuffer(graph->context, CL_MEM_READ_ONLY |
	CL_MEM_COPY_HOST_PTR, m.y * sizeof(cl_float4), i->obj_dir, &graph->ret);
	graph->obj_rayon = clCreateBuffer(graph->context, CL_MEM_READ_ONLY |
	CL_MEM_COPY_HOST_PTR, m.y * sizeof(float), i->obj_rayon, &graph->ret);
	graph->obj_color = clCreateBuffer(graph->context, CL_MEM_READ_ONLY |
	CL_MEM_COPY_HOST_PTR, m.y * sizeof(cl_uint), i->obj_color, &graph->ret);
	graph->obj_type = clCreateBuffer(graph->context, CL_MEM_READ_ONLY |
	CL_MEM_COPY_HOST_PTR, m.y * sizeof(cl_uchar), i->obj_type, &graph->ret);
	graph->obj_angle = clCreateBuffer(graph->context, CL_MEM_READ_ONLY |
	CL_MEM_COPY_HOST_PTR, m.y * sizeof(cl_uchar), i->obj_angle, &graph->ret);
	graph->obj_id = clCreateBuffer(graph->context, CL_MEM_READ_ONLY |
	CL_MEM_COPY_HOST_PTR, m.y * sizeof(cl_uchar), i->obj_id, &graph->ret);
	graph->obj_indice = clCreateBuffer(graph->context, CL_MEM_READ_ONLY |
	CL_MEM_COPY_HOST_PTR, m.y * sizeof(cl_float4), i->obj_indice, &graph->ret);
	graph->obj_lim = clCreateBuffer(graph->context, CL_MEM_READ_ONLY |
	CL_MEM_COPY_HOST_PTR, m.y * sizeof(cl_float4), i->obj_lim, &graph->ret);
	graph->obj_lim_length = clCreateBuffer(graph->context, CL_MEM_READ_ONLY |
	CL_MEM_COPY_HOST_PTR, m.y * sizeof(float), i->obj_lim_length, &graph->ret);
	cl_kernel_set_light_buffer(graph, m, i);
}

static void	cl_kernel_set_buffers(t_graph *graph)
{
	clSetKernelArg(graph->kernel, 0, sizeof(cl_mem), &graph->data);
	clSetKernelArg(graph->kernel, 4, sizeof(cl_mem), &graph->obj_pos);
	clSetKernelArg(graph->kernel, 5, sizeof(cl_mem), &graph->obj_dir);
	clSetKernelArg(graph->kernel, 6, sizeof(cl_mem), &graph->obj_rayon);
	clSetKernelArg(graph->kernel, 7, sizeof(cl_mem), &graph->obj_color);
	clSetKernelArg(graph->kernel, 8, sizeof(cl_mem), &graph->obj_type);
	clSetKernelArg(graph->kernel, 9, sizeof(cl_mem), &graph->obj_angle);
	clSetKernelArg(graph->kernel, 10, sizeof(cl_mem), &graph->obj_indice);
	clSetKernelArg(graph->kernel, 11, sizeof(cl_mem), &graph->obj_id);
	clSetKernelArg(graph->kernel, 12, sizeof(cl_mem), &graph->light_pos);
	clSetKernelArg(graph->kernel, 13, sizeof(cl_mem), &graph->light_coef);
	clSetKernelArg(graph->kernel, 14, sizeof(cl_mem), &graph->light_color);
	clSetKernelArg(graph->kernel, 15, sizeof(cl_mem), &graph->light_id);
	clSetKernelArg(graph->kernel, 18, sizeof(cl_mem), &graph->obj_lim);
	clSetKernelArg(graph->kernel, 19, sizeof(cl_mem), &graph->obj_lim_length);
	clSetKernelArg(graph->kernel, 21, sizeof(cl_mem), &graph->obj_perlin);
	clSetKernelArg(graph->kernel, 22, sizeof(cl_mem), &graph->obj_damier);
	clSetKernelArg(graph->kernel, 23, sizeof(cl_mem), &graph->normals);
	clSetKernelArg(graph->kernel, 24, sizeof(cl_mem), &graph->elli_rayon);
}

void		cl_kernel_set_arg(t_infos *i, t_graph *graph)
{
	clSetKernelArg(graph->kernel, 1, sizeof(cl_short2), &i->screen);
	clSetKernelArg(graph->kernel, 2, sizeof(cl_uchar2), &i->m);
	clSetKernelArg(graph->kernel, 3, sizeof(cl_float4), &i->cam_pos);
	clSetKernelArg(graph->kernel, 16, sizeof(cl_float4), &i->ambient);
	clSetKernelArg(graph->kernel, 17, sizeof(cl_float2), &i->rot_angle);
	clSetKernelArg(graph->kernel, 20, sizeof(cl_uchar4), &i->ambient2);
	clSetKernelArg(graph->kernel, 25, sizeof(int), &i->move);
	cl_kernel_set_buffers(graph);
}
