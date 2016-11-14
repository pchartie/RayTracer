/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_to_bmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libbmp.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static int		write_header(int fd, t_image *img, int palette, int bpp)
{
	char	header[54];

	*((short *)(header + 0x0)) = 0x4d42;
	*((int *)(header + 0x2)) = img->width * img->height * bpp / 8 + 54
	+ BMP_PADDING(img, bpp);
	*((int *)(header + 0x6)) = 0x0;
	*((int *)(header + 0xA)) = 54;
	*((int *)(header + 0xE)) = 40;
	*((int *)(header + 0x12)) = img->width;
	*((int *)(header + 0x16)) = img->height;
	*((short *)(header + 0x1A)) = 0x1;
	*((short *)(header + 0x1C)) = bpp;
	*((int *)(header + 0x1E)) = 0x0;
	*((int *)(header + 0x22)) = img->width * img->height * bpp / 8
		+ BMP_PADDING(img, bpp);
	*((int *)(header + 0x26)) = 0x0b13;
	*((int *)(header + 0x2A)) = 0x0b13;
	*((int *)(header + 0x2E)) = palette;
	*((int *)(header + 0x32)) = 0;
	if (write(fd, header, 54) <= 0)
		return (-1);
	return (0);
}

static int		write_palette(int fd, t_palette *palette)
{
	int		i;
	int		b;

	i = -1;
	while (++i < palette->count)
	{
		b = 0 | palette->colors[i].b | (palette->colors[i].g << 8)
			| (palette->colors[i].r << 16);
		if (write(fd, &b, 4) <= 0)
			return (-1);
	}
	return (0);
}

static void		prepare_24_bits_buf(t_image *img, char *buf)
{
	long	x;
	long	y;
	long	padding;

	y = -1;
	padding = 0;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
		{
			*(buf + padding + (x + y * img->width) * 3) =
				img->data[x + (img->height - y - 1) * img->width].b;
			*(buf + padding + (x + y * img->width) * 3 + 1) =
				img->data[x + (img->height - y - 1) * img->width].g;
			*(buf + padding + (x + y * img->width) * 3 + 2) =
				img->data[x + (img->height - y - 1) * img->width].r;
		}
		padding += BMP_LINE_PADDING(img, 24);
	}
}

int				save_to_bmp_24(char *file, t_image *img)
{
	int		fd;
	char	*buf;

	if ((fd = open(file, O_WRONLY | O_CREAT, 0666)) < 0)
		return (-1);
	if (write_header(fd, img, 0, 24) == -1 || (buf = malloc(
		img->width * img->height * 3 + BMP_PADDING(img, 24))) == NULL)
	{
		close(fd);
		return (-1);
	}
	prepare_24_bits_buf(img, buf);
	write(fd, buf, img->width * img->height * 3 + BMP_PADDING(img, 24));
	free(buf);
	close(fd);
	return (0);
}

int				save_to_bmp_8(char *file, t_image *img, t_palette *palette)
{
	int				fd;
	int				palettec;
	ssize_t			i;
	unsigned char	*buf;

	if ((fd = open(file, O_WRONLY | O_CREAT, 0666)) < 0)
		return (-1);
	palettec = palette ? palette->count : 0;
	if ((write_header(fd, img, palettec, 8) == -1)
		|| (palettec != 0 && write_palette(fd, palette) == -1) || (buf =
		malloc(img->width * img->height)) == NULL)
	{
		close(fd);
		return (-1);
	}
	i = -1;
	while (++i < img->height * img->width)
		buf[i] = get_closest_index_palette(palette, img->data[i %
			img->width + (img->height - i / img->width - 1) * img->width]);
	write(fd, buf, img->width * img->height);
	free(buf);
	close(fd);
	return (0);
}
