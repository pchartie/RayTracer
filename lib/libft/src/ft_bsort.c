/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_bsort(int *tab, int size)
{
	int x;
	int y;

	y = 0;
	while (y < (size - 1))
	{
		x = 0;
		while (x < (size - y - 1))
		{
			if (tab[x] > tab[x + 1])
				ft_swap(&tab[x], &tab[x + 1]);
			x++;
		}
		y++;
	}
	return (tab);
}
