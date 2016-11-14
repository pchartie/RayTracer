/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*gnl_strjoin(char *line, char *save)
{
	char	*str;

	if (!(str = (char *)malloc(ft_strlen(line) + ft_strlen(save) + 1)))
		return (NULL);
	ft_strcpy(str, line);
	ft_strcat(str, save);
	free((char*)line);
	return (str);
}

static int	ft_read_line(int fd, char **save, char **line, char *str)
{
	int	ret;

	*line = ft_strdup(*save);
	while (!str)
	{
		if ((ret = read(fd, *save, BUFF_SIZE)) < 0)
			return (-1);
		if ((str = ft_strchr(*save, '\n')) == NULL && !ret)
			return ((*save)[0] = '\0');
		else if (str)
		{
			(*save)[ret] = ret ? 0 : (*save)[ret];
			str[0] = '\0';
			*line = gnl_strjoin(*line, *save);
			ft_strcpy(*save, str + 1);
		}
		else
		{
			(*save)[ret] = ret ? 0 : (*save)[ret];
			*line = gnl_strjoin(*line, *save);
			(*save)[0] = '\0';
		}
	}
	return (*line ? 1 : -1);
}

int			get_next_line(int const fd, char **line)
{
	static char	*save = NULL;
	char		*buf;
	int			ret;

	if (BUFF_SIZE < 1 || !line || fd < 0)
		return (-1);
	if (!save && !(save = ft_strnew(BUFF_SIZE + 1)))
		return (-1);
	if ((buf = ft_strchr(save, '\n')) != NULL)
	{
		*buf = '\0';
		*line = ft_strdup(save);
		ft_strcpy(save, buf + 1);
		return (*line ? 1 : -1);
	}
	else
		ret = ft_read_line(fd, &save, line, NULL);
	if (ret == 0 && ft_strlen(*line) == 0)
		ft_strdel(&save);
	if (ret == -1)
		return (-1);
	return (ret ? 1 : ft_strlen(*line) != 0);
}
