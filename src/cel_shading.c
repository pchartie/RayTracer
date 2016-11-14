/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cel_shading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static cl_float3	get_float3(float x, float y, float z)
{
	cl_float3	f;

	f.x = x;
	f.y = y;
	f.z = z;
	return (f);
}

static cl_float3	get_f3_4(cl_float4 f1)
{
	cl_float3	f;

	f.x = f1.x;
	f.y = f1.y;
	f.z = f1.z;
	return (f);
}

static char			test_cel(int x, int y, cl_float4 *normals)
{
	cl_float3	norms[5];

	norms[0] = (y > 0) ? get_f3_4(normals[x + (y - 1) * SCRX])
		: get_float3(0, 0, 0);
	norms[1] = (x > 0) ? get_f3_4(normals[(x - 1) + y * SCRX])
		: get_float3(0, 0, 0);
	norms[2] = (x < SCRX - 1) ? get_f3_4(normals[(x + 1) + y * SCRX])
		: get_float3(0, 0, 0);
	norms[3] = (y < SCRY - 1) ? get_f3_4(normals[x + (y + 1) * SCRX])
		: get_float3(0, 0, 0);
	norms[4] = get_f3_4(normals[x + y * SCRX]);
	return (((y > 0) && dot(norms[4], norms[0]) <= 0.98) ||
			((x > 0) && dot(norms[4], norms[1]) <= 0.98) ||
			((x < SCRX - 1) && dot(norms[4], norms[2]) <= 0.98) ||
			((y < SCRX - 1) && dot(norms[4], norms[3]) <= 0.98));
}

void				apply_cel_shad(char *data, int bpp, int sizeline,
													cl_float4 *normals)
{
	int		x;
	int		y;

	bpp /= 8;
	x = -1;
	while (++x < SCRX)
	{
		y = -1;
		while (++y < SCRY)
		{
			if (ft_isequal((double)normals[x + y * SCRX].x, 0) &&
					ft_isequal((double)normals[x + y * SCRX].y, 0)
					&& ft_isequal((double)normals[x + y * SCRX].z, 0))
				continue ;
			if (test_cel(x, y, normals))
			{
				data[x * bpp + y * sizeline] = 0;
				data[x * bpp + y * sizeline + 1] = 0;
				data[x * bpp + y * sizeline + 2] = 0;
			}
		}
	}
}
