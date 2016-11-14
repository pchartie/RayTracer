/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	get_after_dot(const char *str)
{
	double			nbr;
	unsigned int	div;

	div = 10;
	nbr = 0;
	while (*str >= '0' && *str <= '9')
	{
		nbr += (*str - '0') / (double)div;
		div *= 10;
		str++;
	}
	return (nbr);
}

double			ft_atof(const char *str)
{
	double			nbr;
	int				isnegative;

	nbr = 0;
	while (ft_isspace(*str))
		str++;
	isnegative = *str == '-' ? -1 : 1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nbr = 10 * nbr + *str - '0';
		str++;
	}
	if (*str == '.')
		nbr += get_after_dot(++str);
	nbr *= isnegative;
	return (nbr);
}
