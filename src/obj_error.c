/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	cylinder_error(void)
{
	ft_putstr("CYLINDER:\n\tPOS:x:y:z\n\tDIR:x:y:z\n\tRAYON:x\n\tREF:x\n");
	ft_putstr("\tIND:x\n\tMAT:x\n\tSPEC:x\n");
	ft_putstr("\tPERLIN:x\n\tCOLOR:x\n\tLIM:DIR:x:y:z:LEN:x\n\n");
}

void	sphere_error(void)
{
	ft_putstr("SPHERE:\n\tPOS:x:y:z\n\tRAYON:x\n\tREF:x\n");
	ft_putstr("\tIND:x\n\tMAT:x\n\tSPEC:x\n");
	ft_putstr("\tPERLIN:x\n\tCOLOR:x\n\tLIM:DIR:x:y:z:LEN:x\n\n");
}

void	cone_error(void)
{
	ft_putstr("CONE:\n\tPOS:x:y:z\n\tDIR:x:y:z\n\tANGLE:x\n\tREF:x\n");
	ft_putstr("\tIND:x\n\tMAT:x\n\tSPEC:x\n");
	ft_putstr("\tPERLIN:x\n\tCOLOR:x\n\tLIM:DIR:x:y:z:LEN:x\n\n");
}

void	ellipsoid_error(void)
{
	ft_putstr("ELLIPSOID:\n\tPOS:x:y:z\n\tRAYON:x:y:z\n\tREF:x\n");
	ft_putstr("\tIND:x\n\tMAT:x\n\tSPEC:x\n");
	ft_putstr("\tPERLIN:x\n\tCOLOR:x\n\tLIM:DIR:x:y:z:LEN:x\n\n");
}

void	plane_error(void)
{
	ft_putstr("PLANE:\n\tPOS:x:y:z\n\tDIR:x:y:z\n\tREF:x\n");
	ft_putstr("\tIND:x\n\tMAT:x\n\tSPEC:x\n\tDAMIER:x\n");
	ft_putstr("\tPERLIN:x\n\tCOLOR:x\n\tLIM:DIR:x:y:z:LEN:x\n\n");
}
