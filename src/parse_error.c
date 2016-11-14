/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	parse_error3(int i)
{
	if (i == 10)
		ft_putstr("LIGHT:\n\tCOEF: should be between 0 and 1\n");
	else if (i == 11)
		ft_putstr("AMBIENT:\n\tCOEF: should be between 0 and 1\n");
	else if (i == 23)
		ft_putstr("FILTER: should be between 0 and 1\n");
	else if (i == 24)
		ft_putstr("ANTIALIASING: should be between 1 and 4\n");
	else if (i == 25)
		perlin_error();
	else if (i == 26)
		ft_putstr("NBREFLET: should be between 0 and 255\n");
	else if (i == 27)
		ft_putstr("NBREFRACT: should be between 0 and 255\n");
	else if (i == 28)
		ft_putstr("Maximum object: 255\n");
	else if (i == 29)
		ft_putstr("Maximum light: 255\n");
	else if (i == 30)
		ft_putstr("LIM:DIR: should be between -1 and 1\n");
	else
		ft_putstr("LIM:DIR:x:y:z:LEN:x\n else it's an error!\n");
}

static void	parse_error2(int i)
{
	if (i == 12)
		ft_putstr("Just only one AMBIENT: is needed\n");
	else if (i == 13)
		ambient_error(i);
	else if (i == 14)
		ft_putstr("REF: should be between 0 and 1\n");
	else if (i == 15)
		ft_putstr("DIR: should be between -1 and 1\n");
	else if (i == 16)
		ambient_error(i);
	else if (i == 17)
		light_error(i);
	else if (i == 18)
		cam_error(i);
	else if (i == 19)
		ft_putstr("MAT: should be between 0 and 1\n");
	else if (i == 20)
		ft_putstr("SPEC: must be greater than 0\n");
	else if (i == 21)
		ft_putstr("DAMIER: should be between 0 and 1\n");
	else if (i == 22)
		ft_putstr("RAYON: must be greater than 0\n");
	else
		parse_error3(i);
}

void		parse_error(int i)
{
	if (i == 0)
		plane_error();
	else if (i == 1)
		cylinder_error();
	else if (i == 2)
		sphere_error();
	else if (i == 3)
		cone_error();
	else if (i == 4)
		ellipsoid_error();
	else if (i == 5)
		ft_putstr("Error fd!\n");
	else if (i == 6)
		cam_error(i);
	else if (i == 7)
		light_error(i);
	else if (i == 8)
		ft_putstr("Just only one CAM: is needed\n");
	else if (i == 9)
		ft_putstr("IND: should be between 0 and 1\n");
	else
		parse_error2(i);
	exit(0);
}
