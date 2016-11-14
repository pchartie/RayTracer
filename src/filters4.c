/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		crt_effect(t_mlx *mlx)
{
	pixelize(mlx, 3);
	color_shift(mlx, 1);
	brightness(mlx, 50);
	scanline(mlx, 1.1f, 3);
	barrel_distortion(mlx, 0.2f, 1.8f);
}
