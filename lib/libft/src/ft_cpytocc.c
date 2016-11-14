/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpytocc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_cpytocc(char *str, char c)
{
	char	*ret;
	int		i;

	i = 0;
	while (str[i] != c)
		i++;
	ret = (char *)malloc(sizeof(char) * i);
	ret[i - 1] = 0;
	i = -1;
	while (str[++i] != c)
		ret[i] = str[i];
	return (ret);
}
