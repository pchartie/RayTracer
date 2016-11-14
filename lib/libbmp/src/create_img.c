/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libbmp.h"
#include <stdlib.h>
#include <unistd.h>

t_palette	*create_palette(int size)
{
	t_palette	*pal;
	size_t		i;

	if (!(pal = (t_palette *)malloc(sizeof(t_palette))))
		return (NULL);
	pal->count = size;
	i = 0;
	while (i < 256 * sizeof(t_rgb))
	{
		((unsigned char *)pal->colors)[i] = 0;
		i++;
	}
	return (pal);
}

t_palette	*create_safety_palette(void)
{
	t_palette	*pal;
	int			i;
	int			rgb[3];

	if (!(pal = create_palette(256)))
		return (NULL);
	rgb[0] = -51;
	i = 2;
	pal->colors[0] = get_rgb(0, 0, 0);
	pal->colors[1] = get_rgb(255, 255, 255);
	while ((rgb[0] += 51) <= 255)
	{
		rgb[1] = -51;
		while ((rgb[1] += 51) <= 255)
		{
			rgb[2] = -51;
			while ((rgb[2] += 51) <= 255)
			{
				pal->colors[i] = get_rgb(rgb[0], rgb[1], rgb[2]);
				i++;
			}
		}
	}
	return (pal);
}

t_image		*create_image(int width, int height)
{
	t_image		*img;

	if ((img = (t_image *)malloc(sizeof(t_image))) == NULL)
		return (NULL);
	img->width = width;
	img->height = height;
	if ((img->data = malloc(img->height * img->width * sizeof(t_rgb))) == NULL)
	{
		free(img);
		return (NULL);
	}
	return (img);
}
