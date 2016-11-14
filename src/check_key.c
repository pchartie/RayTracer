/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	move(t_infos *i, int k)
{
	cl_float4 dir;

	dir.x = 0;
	dir.y = 0;
	dir.z = -1;
	if (k == KEY_UP || k == KEY_DOWN)
		dir = rot(dir, (double)i->rot_angle.x, (double)i->rot_angle.y);
	if (k == KEY_LEFT)
		dir = rot(dir, (double)i->rot_angle.x, (double)i->rot_angle.y - M_PI_2);
	if (k == KEY_RIGHT)
		dir = rot(dir, (double)i->rot_angle.x, (double)i->rot_angle.y + M_PI_2);
	dir = normalize(dir);
	if (k == KEY_UP)
		i->cam_pos = add_vec(i->cam_pos, multiply_vec(dir, WALKSPEED));
	if (k == KEY_DOWN)
		i->cam_pos = sub_vec(i->cam_pos, multiply_vec(dir, WALKSPEED));
	if (k == KEY_LEFT || k == KEY_RIGHT)
	{
		i->cam_pos.x -= dir.x * WALKSPEED;
		i->cam_pos.z -= dir.z * WALKSPEED;
	}
}

int			red_cross(int keycode, t_infos *i)
{
	(void)keycode;
	(void)i;
	exit(0);
	return (0);
}

static void	switch_scene(t_infos *i, char *path)
{
	free(i->light_pos);
	free(i->light_coef);
	free(i->light_color);
	free(i->light_id);
	free(i->obj_pos);
	free(i->obj_dir);
	free(i->obj_angle);
	free(i->obj_rayon);
	free(i->obj_lim);
	free(i->obj_lim_length);
	free(i->obj_color);
	free(i->obj_id);
	free(i->obj_type);
	free(i->obj_indice);
	free(i->obj_damier);
	free(i->obj_perlin);
	free(i->elli_rayon);
	i->m = get_m_value(path);
	parse(i, i->m, path);
	i->rot_angle.x = i->cam_dir.x * M_PI;
	i->rot_angle.y = i->cam_dir.y * M_PI;
	cl_switch(i);
}

static void	check_key_scenes(int k, t_infos *i)
{
	if (k == KEY_DOWN)
		move(i, k);
	else if (k == KEY_O)
		export_bmp(&i->mlx, "output.bmp", 0);
	else if (k == KEY_P)
		export_bmp(&i->mlx, "output.bmp", 1);
	else if (k == KEY_1)
		switch_scene(i, "scenes/scene_1");
	else if (k == KEY_2)
		switch_scene(i, "scenes/scene_disco");
	else if (k == KEY_3)
		switch_scene(i, "scenes/scene_10");
	else if (k == KEY_4)
		switch_scene(i, "scenes/scene_deadmau5");
	else if (k == KEY_5)
		switch_scene(i, "scenes/scene_water");
	else if (k == KEY_6)
		switch_scene(i, "scenes/scene_st_denis");
	else if (k == KEY_7)
		switch_scene(i, "scenes/scene_avion");
	else if (k == KEY_8)
		switch_scene(i, "scenes/scene_8_verre");
	else if (k == KEY_9)
		switch_scene(i, "scenes/scene_8_perlin");
	(k == KEY_0) ? switch_scene(i, "scenes/scene_sablier") : 0;
}

int			check_key(int k, t_infos *i)
{
	(k == KEY_W) ? i->rot_angle.x -= M_PI_2 / 12 : 0;
	(k == KEY_A) ? i->rot_angle.y += M_PI_2 / 12 : 0;
	(k == KEY_S) ? i->rot_angle.x += M_PI_2 / 12 : 0;
	(k == KEY_D) ? i->rot_angle.y -= M_PI_2 / 12 : 0;
	(k == KEY_PAD_SUB) ? i->cam_pos.y -= 100 : 0;
	(k == KEY_PAD_ADD) ? i->cam_pos.y += 100 : 0;
	(k == KEY_PAD_8) ? i->light_pos->z -= 100 : 0;
	(k == KEY_PAD_4) ? i->light_pos->x -= 100 : 0;
	(k == KEY_PAD_5) ? i->light_pos->z += 100 : 0;
	(k == KEY_PAD_6) ? i->light_pos->x += 100 : 0;
	(k == KEY_PAGE_UP) ? i->light_pos->y -= 100 : 0;
	(k == KEY_PAGE_DOWN) ? i->light_pos->y += 100 : 0;
	(k == KEY_C) ? i->ambient.z = 1 : 0;
	(k == KEY_SPACEBAR) ? i->ambient.z = 0 : 0;
	(k == KEY_SPACEBAR) ? i->ambient.w = 0 : 0;
	(k == KEY_M) ? i->move += 10 : 0;
	(k == KEY_L) ? i->ambient.w = 1 : 0;
	if (k == KEY_ESCAPE)
		exit(0);
	else if (k == KEY_RIGHT || k == KEY_LEFT || k == KEY_UP || k == KEY_DOWN)
		move(i, k);
	else
		check_key_scenes(k, i);
	return (1);
}
