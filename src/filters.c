/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char	*sepia(char *data, int sizeline, int bpp)
{
	t_filter f;

	f.y = 0;
	while (f.y < SCRY)
	{
		f.x = 0;
		while (f.x < SCRX)
		{
			f.id = f.y * sizeline + f.x * (bpp / 8);
			f.r = (unsigned char)data[f.id + 2];
			f.g = (unsigned char)data[f.id + 1];
			f.b = (unsigned char)data[f.id];
			data[f.id + 2] = (unsigned char)MIN(255, .393 * f.r + .769 * f.g
			+ .189 * f.b);
			data[f.id + 1] = (unsigned char)MIN(255, .349 * f.r + .686 * f.g
			+ .168 * f.b);
			data[f.id] = (unsigned char)MIN(255, .272 * f.r + .534 * f.g
			+ .131 * f.b);
			f.x++;
		}
		f.y++;
	}
	return (data);
}

char	*black_white(char *data, int sizeline, int bpp)
{
	t_filter f;

	f.y = 0;
	while (f.y < SCRY)
	{
		f.x = 0;
		while (f.x < SCRX)
		{
			f.id = f.y * sizeline + f.x * (bpp / 8);
			f.r = (unsigned char)data[f.id + 2];
			f.g = (unsigned char)data[f.id + 1];
			f.b = (unsigned char)data[f.id];
			data[f.id + 2] = (char)((f.r + f.g + f.b) / 3.0f);
			data[f.id + 1] = (char)((f.r + f.g + f.b) / 3.0f);
			data[f.id] = (char)((f.r + f.g + f.b) / 3.0f);
			f.x++;
		}
		f.y++;
	}
	return (data);
}

char	*filter_color(t_mlx *m, cl_uint color, float coef)
{
	t_filter f;

	f.y = 0;
	while (f.y < SCRY)
	{
		f.x = 0;
		while (f.x < SCRX)
		{
			f.id = f.y * m->size + f.x * (m->bpp / 8);
			f.r = (unsigned char)m->data[f.id + 2];
			f.g = (unsigned char)m->data[f.id + 1];
			f.b = (unsigned char)m->data[f.id];
			m->data[f.id + 2] = (char)MIN(255, (f.r + B(color) * coef));
			m->data[f.id + 1] = (char)MIN(255, (f.g + G(color) * coef));
			m->data[f.id] = (char)MIN(255, (f.b + R(color) * coef));
			f.x++;
		}
		f.y++;
	}
	return (m->data);
}
