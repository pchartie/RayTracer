/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	cam_error(int i)
{
	if (i == 18)
		ft_putstr("Add\n ");
	ft_putstr("CAM:\n\tPOS:x:y:z\n\tDIR:x:y:z\n\n");
	if (i == 6)
		ft_putstr(" else it's an error!\n");
}

void	light_error(int i)
{
	if (i == 17)
		ft_putstr("Add\n ");
	ft_putstr("LIGHT:\n\tPOS:x:y:z\n\tCOEF:x\n\tCOLOR:x\n\n");
	if (i == 7)
		ft_putstr(" else it's an error!\n");
}

void	ambient_error(int i)
{
	if (i == 16)
		ft_putstr("Add\n ");
	ft_putstr("AMBIENT:\n\tCOEF:x\n\tFILTER:x\n\tFILTERCOLOR:x\n");
	ft_putstr("\tANTIALIASING:x\n\tNBREFLET:x\n\tNBREFRACT:x\n\n");
	if (i == 13)
		ft_putstr(" else it's an error!\n");
}

void	perlin_error(void)
{
	ft_putstr("PERLIN:MARBLE, WOOD, FIRE, CLOUD, DISCO");
	ft_putstr(" or MERCURY\n");
}
