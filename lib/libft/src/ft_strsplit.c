/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_str(const char *s, char c)
{
	int count;
	int i;

	count = 0;
	i = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		if (s[i] != c && s[i])
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
		i++;
	}
	return (count);
}

static size_t	len_str(const char *s, int i, char c)
{
	int len;

	len = 0;
	while (s[i] != c && s[i])
	{
		len++;
		i++;
	}
	return (len);
}

char			**ft_strsplit(char const *s, char c)
{
	int		i;
	int		y;
	char	**map;

	y = 0;
	i = -1;
	map = (char **)malloc(sizeof(char *) * count_str(s, c) + 1);
	if (!map)
		return (NULL);
	while (s[++i])
	{
		if (s[i] != c && s[i])
		{
			map[y] = ft_strsub(s, i, len_str(s, i, c));
			while (s[i] != c && s[i])
				i++;
			i--;
			y++;
		}
	}
	map[y] = NULL;
	return (map);
}
