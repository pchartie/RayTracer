/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		loop_hook(t_infos *i)
{
	int	screen_shot;
	int	ind;

	screen_shot = 0;
	ind = -1;
	while (++ind < NKEYS)
		if (i->keys[ind].y == 1)
		{
			if (i->keys[ind].x != KEY_O && i->keys[ind].x != KEY_P)
				screen_shot = 1;
			check_key(i->keys[ind].x, i);
		}
	if (screen_shot == 1)
		cl_reload(i, i->graph, i->m);
	return (0);
}

int		key_press(int k, t_infos *i)
{
	int	ind;

	ind = -1;
	while (++ind < NKEYS)
		if (k == i->keys[ind].x)
			i->keys[ind].y = 1;
	return (0);
}

int		key_release(int k, t_infos *i)
{
	int ind;

	ind = -1;
	while (++ind < NKEYS)
		if (k == i->keys[ind].x)
			i->keys[ind].y = 0;
	return (0);
}
