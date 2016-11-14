/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	*ft_sort(int *tab, int beg, int end)
{
	int			left;
	int			right;
	int			pivot;

	left = beg - 1;
	right = end + 1;
	pivot = tab[beg];
	if (beg >= end)
		return (tab);
	while (1)
	{
		while (tab[--right] > pivot)
			;
		while (tab[++left] < pivot)
			;
		if (left < right)
			ft_swap(&tab[left], &tab[right]);
		else
			break ;
	}
	ft_sort(tab, beg, right);
	ft_sort(tab, right + 1, end);
	return (tab);
}

int			*ft_qsort(int *tab, int size)
{
	return (ft_sort(tab, 0, size));
}
