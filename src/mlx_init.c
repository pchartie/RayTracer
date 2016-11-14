/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_mlx	ft_mlx(void)
{
	t_mlx mlx;

	mlx.init = mlx_init();
	mlx.win = mlx_new_window(mlx.init, SCRX, SCRY, "RT");
	mlx.img = mlx_new_image(mlx.init, SCRX, SCRY);
	mlx.data = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.size, &mlx.endian);
	return (mlx);
}
