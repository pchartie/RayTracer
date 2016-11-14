/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libbmp.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBBMP_H
# define LIBBMP_H

# define BMP_24 24
# define BMP_8 8
# define BMP_LINE_PADDING(img, bpp) ((img->width * bpp / 8) % 4)
# define BMP_PADDING(img, bpp) (((img->width * bpp / 8) % 4) * img->height)

typedef struct		s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_rgb;

typedef struct		s_palette
{
	t_rgb			colors[256];
	int				count;
}					t_palette;

typedef struct		s_image
{
	unsigned int	width;
	unsigned int	height;
	t_rgb			*data;
}					t_image;

int					save_to_bmp_24(char *file, t_image *img);
int					save_to_bmp_8(char *file, t_image *img, t_palette *palette);
t_palette			*create_palette(int size);
t_palette			*create_safety_palette(void);
t_image				*create_image(int width, int height);
void				destroy_image(t_image *img);
unsigned char		get_closest_index_palette(t_palette *palette, t_rgb rgb);
void				set_pixel(t_image *img, int x, int y, t_rgb rgb);
void				set_pixel_p(t_image *img, int x, int y,
									unsigned char palette_index);
t_rgb				get_rgb(unsigned char r, unsigned char g, unsigned char b);
void				set_rgb(t_rgb *rgb, unsigned char r, unsigned char g,
									unsigned char b);

#endif
