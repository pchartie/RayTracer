/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_keys_scenes(t_infos *i)
{
	i->keys[17].x = KEY_1;
	i->keys[18].x = KEY_2;
	i->keys[19].x = KEY_3;
	i->keys[20].x = KEY_4;
	i->keys[21].x = KEY_5;
	i->keys[22].x = KEY_6;
	i->keys[23].x = KEY_7;
	i->keys[24].x = KEY_8;
	i->keys[25].x = KEY_9;
	i->keys[28].x = KEY_CTRL_LEFT;
	i->keys[29].x = KEY_CTRL_RIGHT;
	i->keys[30].x = KEY_SPACEBAR;
	i->keys[31].x = KEY_C;
	i->keys[32].x = KEY_SHIFT_LEFT;
	i->keys[33].x = KEY_SHIFT_RIGHT;
	i->keys[34].x = KEY_L;
	i->keys[35].x = KEY_0;
	i->keys[36].x = KEY_M;
}

void		init_keys(t_infos *i)
{
	int ind;

	ind = 0;
	i->keys[0].x = KEY_UP;
	i->keys[1].x = KEY_DOWN;
	i->keys[2].x = KEY_LEFT;
	i->keys[3].x = KEY_RIGHT;
	i->keys[4].x = KEY_PAD_8;
	i->keys[5].x = KEY_PAD_4;
	i->keys[6].x = KEY_PAD_5;
	i->keys[7].x = KEY_PAD_6;
	i->keys[8].x = KEY_PAGE_UP;
	i->keys[9].x = KEY_PAGE_DOWN;
	i->keys[10].x = KEY_W;
	i->keys[11].x = KEY_A;
	i->keys[12].x = KEY_S;
	i->keys[13].x = KEY_D;
	i->keys[14].x = KEY_PAD_ADD;
	i->keys[15].x = KEY_PAD_SUB;
	i->keys[16].x = KEY_ESCAPE;
	i->keys[26].x = KEY_O;
	i->keys[27].x = KEY_P;
	init_keys_scenes(i);
	while (ind < NKEYS)
		i->keys[ind++].y = 0;
}
