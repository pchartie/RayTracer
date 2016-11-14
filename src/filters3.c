/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	set_pixel_mlx(char *dcpy, int *x, float *uv, t_mlx *mlx)
{
	mlx->data[x[0] * mlx->bpp / 8 + mlx->size * x[1] + 2] = (uv[0] < 0
		|| uv[0] > 1 || uv[1] < 0 || uv[1] > 1) ? 0 : (unsigned char)dcpy[(int)
		(uv[0] * SCRX) * mlx->bpp / 8 + mlx->size * (int)(uv[1] * SCRY) + 2]
		* (1 - (uv[2]) * uv[3]);
	mlx->data[x[0] * mlx->bpp / 8 + mlx->size * x[1] + 1] = (uv[0] < 0
		|| uv[0] > 1 || uv[1] < 0 || uv[1] > 1) ? 0 : (unsigned char)dcpy[(int)
		(uv[0] * SCRX) * mlx->bpp / 8 + mlx->size * (int)(uv[1] * SCRY) + 1]
		* (1 - (uv[2]) * uv[3]);
	mlx->data[x[0] * mlx->bpp / 8 + mlx->size * x[1]] = (uv[0] < 0
		|| uv[0] > 1 || uv[1] < 0 || uv[1] > 1) ? 0 : (unsigned char)dcpy[(int)
		(uv[0] * SCRX) * mlx->bpp / 8 + mlx->size * (int)(uv[1] * SCRY)]
		* (1 - (uv[2]) * uv[3]);
}

void		barrel_distortion(t_mlx *mlx, float distortion, float black_dis)
{
	char	*dcpy;
	int		x[2];
	float	uv[4];

	if (!(dcpy = (char *)malloc((unsigned long)(mlx->size * SCRY))))
		return ;
	ft_memcpy(dcpy, mlx->data, (size_t)(mlx->size * SCRY));
	uv[3] = black_dis;
	x[0] = -1;
	while (++x[0] < SCRX)
	{
		x[1] = -1;
		while (++x[1] < SCRY)
		{
			uv[0] = x[0] / (float)SCRX - 0.5f;
			uv[1] = x[1] / (float)SCRY - 0.5f;
			uv[2] = uv[0] * uv[0] + uv[1] * uv[1];
			uv[0] = uv[0] + (uv[0] * distortion * uv[2]) + 0.5f;
			uv[1] = uv[1] + (uv[1] * distortion * uv[2]) + 0.5f;
			set_pixel_mlx(dcpy, x, uv, mlx);
		}
	}
	free(dcpy);
}

void		pixelize(t_mlx *mlx, float intensity)
{
	int		x[2];
	int		x2[2];
	int		bpp;

	bpp = mlx->bpp / 8;
	x[0] = -1;
	while (++x[0] < SCRX)
	{
		x[1] = -1;
		while (++x[1] < SCRY)
		{
			x2[0] = (int)(x[0] / intensity) * intensity;
			x2[1] = (int)(x[1] / intensity) * intensity;
			mlx->data[x[0] * bpp + mlx->size * x[1] + 2] =
				((unsigned char)mlx->data[x2[0] * bpp + mlx->size * x2[1] + 2]);
			mlx->data[x[0] * bpp + mlx->size * x[1] + 1] =
				((unsigned char)mlx->data[x2[0] * bpp + mlx->size * x2[1] + 1]);
			mlx->data[x[0] * bpp + mlx->size * x[1]] =
				((unsigned char)mlx->data[x2[0] * bpp + mlx->size * x2[1]]);
		}
	}
}

void		scanline(t_mlx *mlx, float intensity, int skip)
{
	int		x[2];
	int		bpp;

	bpp = mlx->bpp / 8;
	x[0] = -1;
	while (++x[0] < SCRX)
	{
		x[1] = -1;
		while (++x[1] < SCRY)
		{
			if (x[1] % skip == skip - 1 || x[0] % skip == skip - 1)
			{
				mlx->data[x[0] * bpp + mlx->size * x[1] + 2] =
					((unsigned char)mlx->data[x[0] * bpp + mlx->size
					* x[1] + 2]) / intensity;
				mlx->data[x[0] * bpp + mlx->size * x[1] + 1] =
					((unsigned char)mlx->data[x[0] * bpp + mlx->size
					* x[1] + 1]) / intensity;
				mlx->data[x[0] * bpp + mlx->size * x[1]] =
					((unsigned char)mlx->data[x[0] * bpp + mlx->size
					* x[1]]) / intensity;
			}
		}
	}
}

void		brightness(t_mlx *mlx, int brightness)
{
	int		x;
	int		y;
	int		bpp;

	bpp = mlx->bpp / 8;
	x = -1;
	while (++x < SCRX)
	{
		y = -1;
		while (++y < SCRY)
		{
			mlx->data[x * bpp + mlx->size * y + 2] = (char)ft_clamp(
				(unsigned char)mlx->data[x * bpp + mlx->size * y + 2]
				+ brightness, 0, 255);
			mlx->data[x * bpp + mlx->size * y + 1] = (char)ft_clamp(
				(unsigned char)mlx->data[x * bpp + mlx->size * y + 1]
				+ brightness, 0, 255);
			mlx->data[x * bpp + mlx->size * y] = (char)ft_clamp(
				(unsigned char)mlx->data[x * bpp + mlx->size * y]
				+ brightness, 0, 255);
		}
	}
}
