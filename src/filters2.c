/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	set_rgb_tab(t_shift *t, int lmr, char *rgb)
{
	int		m;
	int		d;

	if (lmr == -1)
		m = t->l;
	else if (lmr == 0)
		m = t->m;
	else
		m = t->r;
	d = t->d * lmr;
	rgb[0] |= t->dcpy[(t->x + d) * t->bpp + t->mlx->size * t->y + 2]
		& ((m >> 16) & 0xFF);
	rgb[1] |= t->dcpy[(t->x + d) * t->bpp + t->mlx->size * t->y + 1]
		& ((m >> 8) & 0xFF);
	rgb[2] |= t->dcpy[(t->x + d) * t->bpp + t->mlx->size * t->y]
		& (m & 0xFF);
}

static void	shift_p(t_shift *t)
{
	char	rgb[3];

	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;
	set_rgb_tab(t, 0, rgb);
	if (t->x - t->d >= 0)
		set_rgb_tab(t, -1, rgb);
	if (t->x + t->d < SCRX)
		set_rgb_tab(t, 1, rgb);
	t->mlx->data[t->x * t->bpp + t->mlx->size * t->y + 2] = rgb[0];
	t->mlx->data[t->x * t->bpp + t->mlx->size * t->y + 1] = rgb[1];
	t->mlx->data[t->x * t->bpp + t->mlx->size * t->y] = rgb[2];
}

void		color_shift(t_mlx *mlx, int shift)
{
	t_shift	t;

	t.bpp = mlx->bpp / 8;
	t.mlx = mlx;
	t.d = shift;
	t.l = 0xFF0000;
	t.m = 0x00FF00;
	t.r = 0x0000FF;
	if (!(t.dcpy = (char *)malloc((unsigned long)(mlx->size * SCRY))))
		return ;
	ft_memcpy(t.dcpy, mlx->data, (size_t)(mlx->size * SCRY));
	t.x = -1;
	while (++t.x < SCRX)
	{
		t.y = -1;
		while (++t.y < SCRY)
			shift_p(&t);
	}
	free(t.dcpy);
}

void		anaglyph(t_mlx *mlx, int shift)
{
	t_shift	t;

	t.bpp = mlx->bpp / 8;
	t.mlx = mlx;
	t.d = shift;
	t.l = 0x00FFFF;
	t.m = 0x000000;
	t.r = 0xFF0000;
	if (!(t.dcpy = (char *)malloc((unsigned long)(mlx->size * SCRY))))
		return ;
	ft_memcpy(t.dcpy, mlx->data, (size_t)(mlx->size * SCRY));
	t.x = -1;
	while (++t.x < SCRX)
	{
		t.y = -1;
		while (++t.y < SCRY)
			shift_p(&t);
	}
	free(t.dcpy);
}
