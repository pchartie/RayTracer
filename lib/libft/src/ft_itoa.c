/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digit_counter(int n)
{
	int count;

	count = 0;
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char		*ft_itoa(int n)
{
	char	*res;
	int		digit;
	int		i;

	i = (n < 0 ? 1 : 0);
	if (n == 0)
		return (ft_strdup("0"));
	if (n == (-2147483647 - 1))
		return (ft_strdup("-2147483648"));
	digit = digit_counter(n);
	if (n < 0 && (n = -n))
	{
		if (!(res = (char *)malloc(sizeof(char) * digit + 2)))
			return (NULL);
		res[0] = '-';
	}
	else if (!(res = (char *)malloc(sizeof(char) * digit-- + 1)))
		return (NULL);
	res[digit + 1] = '\0';
	while (i <= digit)
	{
		res[digit--] = (n % 10) + '0';
		n /= 10;
	}
	return (res);
}
