/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	cl_program_kernel(t_graph *graph, const char *source,
															size_t source_size)
{
	char error[MAX_SRC_SIZE];

	graph->program = clCreateProgramWithSource(graph->context, 1,
			(const char **)&source, (const size_t *)&source_size, &graph->ret);
	graph->ret = clBuildProgram(graph->program, 1, &graph->device_id, NULL,
			NULL, NULL);
	graph->ret = clGetProgramBuildInfo(graph->program, graph->device_id,
			CL_PROGRAM_BUILD_LOG, MAX_SRC_SIZE, error, NULL);
	graph->kernel = clCreateKernel(graph->program, "rt", &graph->ret);
}

void		cl_switch(t_infos *i)
{
	clReleaseMemObject(i->graph->data);
	clReleaseMemObject(i->graph->obj_pos);
	clReleaseMemObject(i->graph->obj_dir);
	clReleaseMemObject(i->graph->obj_rayon);
	clReleaseMemObject(i->graph->obj_color);
	clReleaseMemObject(i->graph->obj_type);
	clReleaseMemObject(i->graph->obj_angle);
	clReleaseMemObject(i->graph->obj_id);
	clReleaseMemObject(i->graph->obj_indice);
	clReleaseMemObject(i->graph->light_pos);
	clReleaseMemObject(i->graph->light_coef);
	clReleaseMemObject(i->graph->light_color);
	clReleaseMemObject(i->graph->light_id);
	clReleaseMemObject(i->graph->obj_lim);
	clReleaseMemObject(i->graph->obj_lim_length);
	clReleaseMemObject(i->graph->obj_perlin);
	clReleaseMemObject(i->graph->obj_damier);
	clReleaseMemObject(i->graph->normals);
	clReleaseMemObject(i->graph->elli_rayon);
	cl_kernel_set_buffer(i->graph, i->m, i);
	cl_kernel_set_arg(i, i->graph);
	rt_loop(i, i->mlx, i->graph);
}

void		cl_init(t_graph *graph, t_infos *i)
{
	FILE	*fp;
	char	*filename;
	char	*source;
	size_t	source_size;

	filename = ft_strdup("src/rt.cl");
	if (!(fp = fopen(filename, "r")))
		exit(1);
	source = (char *)malloc(sizeof(char) * MAX_SRC_SIZE);
	source_size = fread(source, 1, MAX_SRC_SIZE, fp);
	clGetPlatformIDs(1, &graph->platform_id, &graph->ret_num_platform);
	clGetDeviceIDs(graph->platform_id, CL_DEVICE_TYPE_CPU, 1, &graph->device_id,
			&graph->ret_num_devices);
	graph->context = clCreateContext(NULL, 1, &graph->device_id, NULL, NULL,
			&graph->ret);
	graph->command_queue = clCreateCommandQueue(graph->context,
			graph->device_id, 0, &graph->ret);
	cl_program_kernel(graph, source, source_size);
	cl_kernel_set_buffer(i->graph, i->m, i);
	cl_kernel_set_arg(i, i->graph);
	free(source);
	free(filename);
}

void		cl_reload(t_infos *i, t_graph *graph, cl_uchar2 m)
{
	clReleaseMemObject(i->graph->data);
	clReleaseMemObject(i->graph->light_pos);
	clReleaseMemObject(i->graph->normals);
	i->graph->data = clCreateBuffer(i->graph->context, CL_MEM_READ_WRITE,
			(MEM_SIZE) * sizeof(char), NULL, &i->graph->ret);
	i->graph->light_pos = clCreateBuffer(i->graph->context, CL_MEM_READ_ONLY |
	CL_MEM_COPY_HOST_PTR, m.x * sizeof(cl_float4), i->light_pos, &graph->ret);
	i->graph->normals = clCreateBuffer(i->graph->context, CL_MEM_READ_WRITE,
			(SCRY * SCRX) * sizeof(cl_float4), NULL, &i->graph->ret);
	clSetKernelArg(i->graph->kernel, 0, sizeof(cl_mem), &i->graph->data);
	clSetKernelArg(i->graph->kernel, 3, sizeof(cl_float4), &i->cam_pos);
	clSetKernelArg(i->graph->kernel, 12, sizeof(cl_mem), &i->graph->light_pos);
	clSetKernelArg(i->graph->kernel, 16, sizeof(cl_float4), &i->ambient);
	clSetKernelArg(i->graph->kernel, 17, sizeof(cl_float2), &i->rot_angle);
	clSetKernelArg(i->graph->kernel, 23, sizeof(cl_mem), &i->graph->normals);
	clSetKernelArg(i->graph->kernel, 25, sizeof(int), &i->move);
	rt_loop(i, i->mlx, i->graph);
}

void		cl_clean(t_graph *graph)
{
	clFlush(graph->command_queue);
	clFinish(graph->command_queue);
	clReleaseKernel(graph->kernel);
	clReleaseProgram(graph->program);
	clReleaseMemObject(graph->data);
	clReleaseMemObject(graph->obj_pos);
	clReleaseMemObject(graph->obj_dir);
	clReleaseMemObject(graph->obj_rayon);
	clReleaseMemObject(graph->obj_color);
	clReleaseMemObject(graph->obj_type);
	clReleaseMemObject(graph->obj_angle);
	clReleaseMemObject(graph->obj_id);
	clReleaseMemObject(graph->obj_indice);
	clReleaseMemObject(graph->light_pos);
	clReleaseMemObject(graph->light_coef);
	clReleaseMemObject(graph->light_color);
	clReleaseMemObject(graph->light_id);
	clReleaseMemObject(graph->obj_lim);
	clReleaseMemObject(graph->obj_lim_length);
	clReleaseMemObject(graph->normals);
	clReleaseMemObject(graph->obj_perlin);
	clReleaseMemObject(graph->obj_damier);
	clReleaseMemObject(graph->elli_rayon);
	clReleaseCommandQueue(graph->command_queue);
	clReleaseContext(graph->context);
}
