/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putuni(int c, int fd)
{
	write(fd, &c, 1);
}

void		ft_putchar_fd(int c, int fd)
{
	if (c < 128)
		ft_putuni(c, fd);
	else if (c < 2048)
	{
		ft_putuni(192 | (c >> 6), fd);
		ft_putuni(128 | (c & 63), fd);
	}
	else if (c < 65536)
	{
		ft_putuni(224 | (c >> 12), fd);
		ft_putuni(128 | ((c >> 6) & 63), fd);
		ft_putuni(128 | (c & 63), fd);
	}
	else if (c < 1114112)
	{
		ft_putuni(240 | (c >> 18), fd);
		ft_putuni(128 | ((c >> 12) & 63), fd);
		ft_putuni(128 | ((c >> 6) & 63), fd);
		ft_putuni(128 | (c & 63), fd);
	}
}
