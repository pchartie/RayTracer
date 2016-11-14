/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_closest_index_palette.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libbmp.h"

static int			pow2(int a)
{
	return (a * a);
}

unsigned char		get_closest_index_palette(t_palette *palette, t_rgb rgb)
{
	int				i;
	int				dist;
	int				tdist;
	unsigned char	closest;

	i = -1;
	dist = 0xFFFFFF;
	while (++i < palette->count)
	{
		tdist = pow2(rgb.r - palette->colors[i].r)
			+ pow2(rgb.g - palette->colors[i].g)
			+ pow2(rgb.b - palette->colors[i].b);
		if (tdist < dist)
		{
			dist = tdist;
			closest = i;
		}
	}
	return (closest);
}
