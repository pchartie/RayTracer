/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		rt_loop(t_infos *i, t_mlx mlx, t_graph *graph)
{
	graph->ret = clEnqueueNDRangeKernel(graph->command_queue, graph->kernel, 1,
									NULL, &graph->core, NULL, 0, NULL, NULL);
	clEnqueueReadBuffer(graph->command_queue, graph->data, CL_FALSE, 0,
						(MEM_SIZE) * sizeof(char), mlx.data, 0, NULL, NULL);
	clEnqueueReadBuffer(graph->command_queue, graph->normals, CL_FALSE, 0,
			(SCRY * SCRX) * sizeof(cl_float4), graph->fnormals, 0, NULL, NULL);
	clFlush(graph->command_queue);
	clFinish(graph->command_queue);
	if (!ft_isequal((double)i->ambient.y, 0))
		mlx.data = filter_color(&mlx, i->filter_color, i->ambient.y);
	if (ft_isequal((double)i->ambient.z, 1))
		apply_cel_shad(mlx.data, mlx.bpp, mlx.size, graph->fnormals);
	if (i->keys[28].y == 1)
		mlx.data = black_white(mlx.data, mlx.size, mlx.bpp);
	if (i->keys[29].y == 1)
		mlx.data = sepia(mlx.data, mlx.size, mlx.bpp);
	if (i->keys[32].y == 1)
		crt_effect(&mlx);
	if (i->keys[33].y == 1)
		anaglyph(&mlx, 2);
	mlx_put_image_to_window(mlx.init, mlx.win, mlx.img, 0, 0);
}

static void	init_values(t_infos *i, char *file)
{
	(void)file;
	i->mlx = ft_mlx();
	i->m = get_m_value(file);
	i->graph->core = MEM_SIZE / 4;
	i->screen.x = SCRX;
	i->screen.y = SCRY;
	i->graph->fnormals = ft_memalloc(SCRY * SCRX * sizeof(cl_float4));
	i->ambient.z = 0;
	i->allign = 0;
	i->move = 0;
}

int			main(int ac, char **av)
{
	t_infos *i;

	if (ac != 2)
		return (1);
	i = (t_infos *)malloc(sizeof(t_infos));
	i->graph = (t_graph *)malloc(sizeof(t_graph));
	i->keys = (cl_int2 *)malloc(sizeof(cl_int2) * NKEYS);
	init_values(i, av[1]);
	init_keys(i);
	parse(i, i->m, av[1]);
	i->rot_angle.x = (cl_float)(i->cam_dir.x * (float)M_PI);
	i->rot_angle.y = (cl_float)(i->cam_dir.y * (float)M_PI);
	cl_init(i->graph, i);
	rt_loop(i, i->mlx, i->graph);
	mlx_hook(i->mlx.win, 17, (1L << 17), red_cross, i);
	mlx_hook(i->mlx.win, 2, (1L << 0), key_press, i);
	mlx_hook(i->mlx.win, 3, (1L << 1), key_release, i);
	mlx_loop_hook(i->mlx.init, loop_hook, i);
	mlx_loop(i->mlx.init);
	cl_clean(i->graph);
	return (EXIT_SUCCESS);
}
