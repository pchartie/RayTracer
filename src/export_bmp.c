/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	export(t_image *image, char *filename, char eightbits)
{
	int					ret;
	t_palette			*pal;

	ret = 0;
	if (access(filename, F_OK) != -1 && unlink(filename) == -1)
		ret = -1;
	if (ret == 0 && eightbits)
	{
		if (!(pal = create_safety_palette()))
			ret = -1;
		else
		{
			ret = save_to_bmp_8(filename, image, pal);
			free(pal);
		}
	}
	else if (ret == 0)
		ret = save_to_bmp_24(filename, image);
	destroy_image(image);
	return (ret);
}

int			export_bmp(t_mlx *m, char *filename, char eightbits)
{
	int					o;
	unsigned int		x[2];
	t_image				*i;

	o = m->bpp / 8;
	if ((i = create_image(SCRX, SCRY)) == NULL)
		return (-1);
	x[0] = 0;
	while (x[0] < i->width)
	{
		x[1] = 0;
		while (x[1] < i->height)
		{
			set_pixel(i, (int)x[0], (int)x[1], get_rgb(
				(unsigned char)m->data[(x[0] + x[1] * i->width)
				* (unsigned int)o + 2],
				(unsigned char)m->data[(x[0] + x[1] * i->width)
				* (unsigned int)o + 1],
				(unsigned char)m->data[(x[0] + x[1] * i->width)
				* (unsigned int)o]));
			x[1]++;
		}
		x[0]++;
	}
	return (export(i, filename, eightbits));
}
