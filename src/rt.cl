/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.cl                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MIDX				(screen.x / 2)
#define MIDY				(screen.y / 2)
#define MAX_FLOAT			3.40282347E+38F
#define DAMIER				600
#define PLANE				0
#define CYLINDER			1
#define SPHERE				2
#define CONE				3
#define ELLIPSOID			4
#define RGB(r, g, b)		((0xFF & r) | ((0xFF & g) << 8) | ((0xFF & b) << 16))
#define R(r)				(0xFF & r)
#define G(g)				((0xFF00 & g) >> 8)
#define B(b)				((0xFF0000 & b) >> 16)
#define PLANEDIST(fov)		(screen.x / (2 * tan((float)fov / 2)))
#define C1_R				col[0]
#define C1_G				col[1]
#define C1_B				col[2]
#define C2_R				col[3]
#define C2_G				col[4]
#define C2_B				col[5]
#define C3_R				col[6]
#define C3_G				col[7]
#define C3_B				col[8]
#define LIMIT(x, n1, n2)	((x < n1) ? (n1) : (((x) > (n2)) ? (n2) : (x)))
#define SHADE				0.2
#define MARBLE				1
#define WOOD				2
#define FIRE				3
#define WATER				4
#define DISCO				5
#define MERCURY				6
//#define LIGHT_ILLUMINATION

// obj_indice[0] = mat
// obj_indice[1] = spec
// obj_indice[2] = ref
// obj_indice[3] = ind

typedef	struct	s_perl
{
	float		sval[9];
	float		col[9];
	float		pn;
}				t_perl;

__constant unsigned char g_tab[512] = {151,160,137,91,90,15,
	131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
	190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
	88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
	77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
	102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
	135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
	5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
	223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
	129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
	251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
	49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
	138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180,151,
	160,137,91,90,15,
	131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
	190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
	88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
	77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
	102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
	135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
	5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
	223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
	129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
	251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
	49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
	138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180,
};


void	skip_fnumber(__constant char *line, int *i)
{
	while ((line[*i] >= '0' && line[*i] <= '9') || line[*i] == '.' ||
			line[*i] == '-' || line[*i] == '+')
		++(*i);
	if (line[*i] == ',')
		++(*i);
}

void	lower_interpol(uchar *color_obj, float pn, float *sval, float *col)
{
	color_obj[2] = LIMIT(C1_B * ((pn - sval[0]) / (sval[1] - sval[0]))
			+ C2_B * ((sval[1] - pn) / (sval[1] - sval[0]))
			, 0, 255);
	color_obj[1] = LIMIT(C1_G * ((pn - sval[0]) / (sval[1] - sval[0]))
			+ C2_G * ((sval[1] - pn) / (sval[1] - sval[0]))
			, 0, 255);
	color_obj[0] = LIMIT(C1_R * ((pn - sval[0]) / (sval[1] - sval[0])) + C2_R
			* ((sval[1] - pn) / (sval[1] - sval[0]))
			, 0, 255);
}

void	middle_interpol(uchar *color_obj, float pn, float *sval, float *col)
{
	color_obj[2] = LIMIT(C2_B * ((pn - sval[1]) / (sval[2] - sval[1]))
			+ C3_B * ((sval[2] - pn) / (sval[2] - sval[1]))
			, 0, 255);
	color_obj[1] = LIMIT(C2_G * ((pn - sval[1]) / (sval[2] - sval[1]))
			+ C3_G * ((sval[2] - pn) / (sval[2] - sval[1]))
			, 0, 255);
	color_obj[0] = LIMIT(C2_R * ((pn - sval[1]) / (sval[2] - sval[1]))
			+ C3_R * ((sval[2] - pn) / (sval[2] - sval[1]))
			, 0, 255);
}

void	upper_interpol(uchar *color_obj, float pn, float *sval, float *col)
{
	(void)pn;
	(void)sval;
	color_obj[2] = C1_B;
	color_obj[1] = C1_G;
	color_obj[0] = C1_R;
}

void	interpolation(uchar *color_obj, float pn, float *sval, float *col)
{
	if (pn < 0.4)
		lower_interpol(color_obj, pn, sval, col);
	else if (pn < 0.6)
		middle_interpol(color_obj, pn, sval, col);
	else
		upper_interpol(color_obj, pn, sval, col);
}

float	get_deci(__constant char *s1)
{
	float	res = 1;
	float	deci = 1;
	int		pos = 0;

	while (s1[pos] >= '0' && s1[pos] <= '9')
	{
		if (res * 10 / 10 != res)
			return (0);
		res = res * 10 + (s1[pos++] - 48);
		deci *= 10;
	}
	return ((res - deci) / deci);
}

float	ft_fgetnbr(__constant char *s1)
{
	int		i = 0;
	float	nb = 0;
	float	sign = 1;

	while (s1[i] == ' ' || s1[i] == '-' || s1[i] == '+')
		if (s1[i++] == '-')
			sign = -sign;
	while (s1[i] >= '0' && s1[i] <= '9')
	{
		if (((nb * 10) / 10) != nb)
			return (0);
		nb = nb * 10 + (s1[i++] - 48);
	}
	if (s1[i] == '.')
		nb += get_deci(&s1[i + 1]);
	return (nb * sign);
}

void	skip_space(__constant char *line, int *i)
{
	while (line[*i] == ' ')
		++(*i);
}

void	fill_tab_from_str(float *tab, __constant char *str, int size)
{
	int	i = 0;
	int	x = 0;

	while (str[i] && x < size)
	{
		tab[x++] = ft_fgetnbr(&str[i]);
		skip_fnumber(str, &i);
		skip_space(str, &i);
	}
}

uint	recomp_color(uchar *color)
{
	uint	ncolor;

	ncolor = color[0] << 8;
	ncolor = (ncolor | color[1]) << 8;
	ncolor = ncolor | color[2];
	return (ncolor);
}

float	fade(float curve)
{
	return (pow(curve, 3.0f) * (curve * (curve * 6 - 15) + 10));
}

float	perl(float curve, float a, float b)
{
	return (mad(curve, (b - a), a));
}

void	init_noise(int *c_unit, float *x, float *y, float *z)
{
	c_unit[0] = (int)floor(*x) & 255;
	c_unit[1] = (int)floor(*y) & 255;
	c_unit[2] = (int)floor(*z) & 255;
	*x -= floor(*x);
	*y -= floor(*y);
	*z -= floor(*z);
}

float	grad(int hash, float x, float y, float z)
{
	int		h = hash % 25;
	float	vec1;
	float	vec2;

	if (h < 8 || h == 12 || h == 13)
		vec1 = x;
	else
		vec1 = y;
	if (h < 4 || h == 12 || h == 13)
		vec2 = y;
	else
		vec2 = z;
	return (((h % 2) == 0 ? vec1 : -vec1) + ((h & 2) == 0 ? vec2 : -vec2));
}

float	get_perlin(float x, float y, float z)
{
	float	vec[3];
	int		c_unit[3];
	int		coor[6];

	init_noise(c_unit, &x, &y, &z);
	vec[0] = fade(x);
	vec[1] = fade(y);
	vec[2] = fade(z);
	coor[0] = g_tab[c_unit[0]] + c_unit[1];
	coor[1] = g_tab[coor[0]] + c_unit[2];
	coor[2] = g_tab[coor[0] + 1] + c_unit[2];
	coor[3] = g_tab[c_unit[0] + 1] + c_unit[1];
	coor[4] = g_tab[coor[3]] + c_unit[2];
	coor[5] = g_tab[coor[3] + 1] + c_unit[2];
	return (perl(vec[2], perl(vec[1], perl(vec[0], grad(g_tab[coor[1]], x, y, z),
						grad(g_tab[coor[4]], x - 1, y, z)),
					perl(vec[0], grad(g_tab[coor[2]], x, y - 1, z),
						grad(g_tab[coor[5]], x - 1, y - 1, z))),
				perl(vec[1], perl(vec[0], grad(g_tab[coor[1] + 1], x, y, z - 1),
						grad(g_tab[coor[4] + 1], x - 1, y, z - 1)),
					perl(vec[0], grad(g_tab[coor[2] + 1], x, y - 1, z - 1),
						grad(g_tab[coor[5] + 1], x - 1, y - 1, z - 1)))));
}

uint	perlin_marble(float *inter, uchar *color_obj, t_perl *ppt, float frequency)
{
	int	level = 1;

	ppt->pn = 0;
	while (level < 50)
	{
		ppt->pn += (1.0f / level)
			* (get_perlin(level * 0.2 * inter[0],
						level * 0.2 * inter[1],
						level * 0.2 * inter[2]));
		level++;
	}
	color_obj[0] = LIMIT(255 * (1 - ppt->pn), 169, 240);
	color_obj[1] = LIMIT(255 * (1 - ppt->pn), 154, 223);
	color_obj[2] = LIMIT(255 * (1 - ppt->pn), 124, 197);
	return (recomp_color(color_obj));
}

uint	perlin_mercury(float *inter, uchar *color_obj, t_perl *ppt, float frequency)
{
	fill_tab_from_str(ppt->sval, "0.01, 0.4, 0.6", 3);
	fill_tab_from_str(ppt->col, "84, 255, 95, 28, 59, 255, 100, 37, 17", 9);
	ppt->pn = get_perlin(0.05 * inter[0],
			0.05 * inter[1],
			0.05 * inter[2]);
	interpolation(color_obj, ppt->pn, ppt->sval, ppt->col);
	return (recomp_color(color_obj));
}

uint	perlin_fire(float *inter, uchar *color_obj, t_perl *ppt, float frequency)
{
	fill_tab_from_str(ppt->col, "192, 15, 5, 255, 180, 0", 6);
	ppt->pn = fabs(get_perlin(frequency * inter[0],
				frequency * inter[1],
				frequency * inter[2]));
	color_obj[2] = LIMIT((ppt->col[2] * ppt->pn)
			+ ppt->col[5] * ((1 - ppt->pn)), 0, 255);
	color_obj[1] = LIMIT((ppt->col[1] * ppt->pn)
			+ ppt->col[4] * ((1 - ppt->pn)), 0, 255);
	color_obj[0] = LIMIT((ppt->col[0] * ppt->pn)
			+ ppt->col[3] * ((1 - ppt->pn)), 0, 255);
	return (recomp_color(color_obj));
}

uint	perlin_wood(float *inter, uchar *color_obj, t_perl *ppt, float frequency)
{
	ppt->pn = 0;
	fill_tab_from_str(ppt->sval, "0.2, 0.4, 0.6", 3);
	fill_tab_from_str(ppt->col, "206, 103, 0, 128, 64, 0, 89, 45, 0", 9);
	ppt->pn += 20 * fabs((get_perlin(frequency * inter[0],
					frequency * inter[1],
					frequency * inter[2])));
	ppt->pn = ppt->pn - (int)ppt->pn;
	interpolation(color_obj, ppt->pn, ppt->sval, ppt->col);
	return (recomp_color(color_obj));
}

uint	perlin_zebra(float *inter, uchar *color_obj, t_perl *ppt, float frequency)
{
	ppt->pn = half_cos(get_perlin(0.02 * inter[0],
				0.02 * inter[1],
				0.02 * inter[2]) * 70);
	color_obj[2] = LIMIT(255 * (1 - ppt->pn), 0, 255);
	color_obj[1] = LIMIT(255 * (1 - ppt->pn), 0, 255);
	color_obj[0] = LIMIT(255 * (1 - ppt->pn), 0, 255);
	return (recomp_color(color_obj));
}

uint	perlin_disco(float *inter, uchar *color_obj, t_perl *ppt, float frequency)
{
	frequency *= 2.0;
	float pn_r = get_perlin(inter[0] * 0.1 * frequency * 7,
			inter[1] * 0.1 * frequency * 7,
			inter[2] * 0.1 * frequency * 7);
	float pn_v = get_perlin(inter[0] * 0.3 * frequency * 7,
			inter[1] * 0.3 * frequency * 7,
			inter[2] * 0.3 * frequency * 7);
	float pn_b = get_perlin(inter[0] * 0.5 * frequency * 7,
			inter[1] * 0.5 * frequency * 7,
			inter[2] * 0.5 * frequency * 7);
	color_obj[0] = LIMIT(pn_r * 200 + 50, 0, 255);
	color_obj[1] = LIMIT(pn_v * 200 + 50, 0, 255);
	color_obj[2] = LIMIT(pn_b * 200 + 100, 0, 255);
	return (recomp_color(color_obj));
}

uint	colorize_obj(float3 ambient, uint color, float coef)
{
	short r = R(color) * coef;
	short g = G(color) * coef;
	short b = B(color) * coef;
	r = LIMIT(r, (ambient.x * R(color)), 255);
	g = LIMIT(g, (ambient.x * G(color)), 255);
	b = LIMIT(b, (ambient.x * B(color)), 255);
	return (RGB(r, g, b));
}

uint	damier(float4 obj_inters, float3 ambient, uint color, float obj_damier)
{
	int	x1;
	int	y1;
	int	z1;
	int	a;

	a = 0;
	if (obj_inters.x < 0 && obj_inters.z > 0)
	{
		a = 1;
		obj_inters = -obj_inters;
	}
	x1 = (int)(obj_inters.x / DAMIER);
	y1 = (int)(obj_inters.y / DAMIER);
	z1 = (int)(obj_inters.z / DAMIER);
	if ((obj_inters.x < 0 && obj_inters.z < 0) || (obj_inters.x > 0 && obj_inters.z > 0))
	{
		if (a == 1)
			obj_inters = -obj_inters;
		if (x1 % 2 == 0)
		{
			if (((y1 % 2 == 0) && (z1 % 2 == 0)) ||
					(((y1 % 2 != 0) && (z1 % 2 != 0))))
				return (color);
			else
				return (colorize_obj(ambient, color, obj_damier));
		}
		else
		{
			if ((((y1 % 2 == 0) && (z1 % 2 == 0))) ||
					(((y1 % 2 != 0) && (z1 % 2 != 0))))
				return (colorize_obj(ambient, color, obj_damier));
			else
				return (color);
		}
	}
	else
	{
		if (a == 1)
			obj_inters = -obj_inters;
		if (x1 % 2 == 1)
		{
			if (((y1 % 2 == 0) && (z1 % 2 == 0)) ||
					(((y1 % 2 != 0) && (z1 % 2 != 0))))
				return (color);
			else
				return (colorize_obj(ambient, color, obj_damier));
		}
		else
		{
			if ((((y1 % 2 == 0) && (z1 % 2 == 0))) ||
					(((y1 % 2 != 0) && (z1 % 2 != 0))))
				return (colorize_obj(ambient, color, obj_damier));
			else
				return (color);
		}
	}
}

uint	hub_perlin(							uint	color,
											uchar	perlin,
											float4	*obj_inters,
					__global	read_only	uchar	*obj_type,
											short	index,
											float3	ambient,
											float	obj_damier,
											int		move,
											float	*perl)
{
	if (perlin == 0)
		return (color);
	float	tabinters[3];
	t_perl	ppt;

	if (obj_type[index] == PLANE)
		color = damier(obj_inters[index], ambient.x, color, obj_damier);
	if (perlin == MARBLE || perlin == FIRE)
	{
		*perl = get_perlin((obj_inters[index].x / 100), (obj_inters[index].y / 100), (obj_inters[index].z / 100));
		tabinters[0] = (obj_inters[index].x / 100);
		tabinters[1] = (obj_inters[index].y / 100);
		tabinters[2] = (obj_inters[index].z / 100);
	}
	else if (perlin == WATER)
	{
		*perl = get_perlin(((obj_inters[index].x) / 100), ((obj_inters[index].y - move) / 100), ((obj_inters[index].z) / 100));
		tabinters[0] = ((obj_inters[index].x) / 100);
		tabinters[1] = ((obj_inters[index].y - move) / 100);
		tabinters[2] = ((obj_inters[index].z) / 100);

	}
	else if (perlin == MERCURY)
	{
		*perl = get_perlin((obj_inters[index].x), (obj_inters[index].y), (obj_inters[index].z));
		tabinters[0] = (obj_inters[index].x);
		tabinters[1] = (obj_inters[index].y);
		tabinters[2] = (obj_inters[index].z);
	}
	else
	{
		*perl = get_perlin((obj_inters[index].x / 1000), (obj_inters[index].y / 1000), (obj_inters[index].z / 1000));
		tabinters[0] = (obj_inters[index].x / 1000);
		tabinters[1] = (obj_inters[index].y / 1000);
		tabinters[2] = (obj_inters[index].z / 1000);
	}
	uchar tabcolor[3] = {R(color), G(color), B(color)};
	color = (perlin == 1) ? perlin_marble(tabinters, tabcolor, &ppt, *perl) : (color);
	color = (perlin == 2) ? perlin_wood(tabinters, tabcolor, &ppt, *perl) : (color);
	color = (perlin == 3) ? perlin_fire(tabinters, tabcolor, &ppt, *perl) : (color);
	color = (perlin == 5) ? perlin_disco(tabinters, tabcolor, &ppt, *perl) : (color);
	color = (perlin == 6) ? perlin_mercury(tabinters, tabcolor, &ppt, *perl) : (color);
	return (color);
}

float	set_lim(float4 raydir, float4 obj_pos, float4 obj_lim, float4 s_pos)
{
	float t;
	float4 dist;

	dist = s_pos - obj_pos;		
	t = -dot(dist, obj_lim) / dot(raydir, obj_lim);
	return (t >= 1 ? t : MAX_FLOAT);
}

float	inter_sphere(						float	rayon,
											float4	obj_pos,
											float4	dist,
											float4	raydir,
											int		op,
					__global	read_only	float4	*obj_lim,
					__global	read_only	float	*obj_lim_length,
											float4	pos,
											short	index,
											int		*tmp_normale)
{
	float a, b, c, delta, t1, t2;
	float	toto, plane1, plane2, sol2;

	a = dot(raydir, raydir);
	b = 2.0 * dot(raydir, dist);
	c = dot(dist, dist) - (rayon * rayon);
	*tmp_normale = 0;
	if ((delta = b * b - 4 * a * c) < 0.0)
		return (MAX_FLOAT);
	if (delta == 0.0)
		return (-b / (2.0 * a));
	else
	{
		t1 = (-b + half_sqrt(delta)) / (2.0 * a);
		t2 = (-b - half_sqrt(delta)) / (2.0 * a);
		sol2 = t1;
		if (op == 0)
		{
			toto = (t1 < t2) ? t1 : t2;
			sol2 = (t1 < t2) ? t2 : t1;
		}
		else
		{
			if (t1 > 1 && t2 > 1)
				toto = (t1 < t2) ? t1 : t2;
			else if (t2 > 1 && t1 < 1)
				toto = t2;
			else if (t1 < 1 && t2 < 1)
				toto = 0;
		}
	}
	if (obj_lim[index].x == 0.0 && obj_lim[index].y == 0.0 && obj_lim[index].z == 0.0)
		return (toto);
	plane1 = set_lim(raydir, obj_pos, -obj_lim[index], pos);
	plane2 = set_lim(raydir, obj_pos - (obj_lim[index] * obj_lim_length[index]), -obj_lim[index], pos);
	if (plane1 == MAX_FLOAT && plane2 == MAX_FLOAT)
		return (MAX_FLOAT);
	if (toto < plane1 && toto < plane2 && sol2 > plane1 && sol2 > plane2)
	{
		*tmp_normale = 1;
		return ((plane1 < plane2) ? plane1 : plane2);
	}
	if ((toto < plane1 && plane2 == MAX_FLOAT) || (toto < plane2 && plane1 == MAX_FLOAT))
		return (toto);
	if (((plane1 < toto && toto < plane2) || (plane2 < toto && toto < plane1)) && plane1 != MAX_FLOAT && plane2 != MAX_FLOAT)
		return (toto);
	if (toto < plane1 && plane1 < sol2)
	{
		*tmp_normale = 1;
		return (plane1);
	}
	if (toto < plane2 && plane2 < sol2)
	{
		*tmp_normale = 1;
		return (plane2);
	}
	return (MAX_FLOAT);
}

float	inter_plane(float4 obj_dir, float4 dist, float4 raydir)
{
	float t = -dot(dist, obj_dir) / dot(raydir, obj_dir);
	return ((t < 0.0) ? MAX_FLOAT : t);
}

float	inter_cylinder(							float4	obj_dir,
												float4	obj_pos,
												float	rayon,
												float4	dist,
												float4	raydir,
												int		op,
						__global	read_only	float4	*obj_lim,
						__global	read_only	float	*obj_lim_length,
												float4	pos,
												short	index,
												int		*tmp_normale)
{
	float	a, b, c, delta, t1, t2;
	float4	tmp;
	float	plane1, plane2, sol2;
	float	toto;

	tmp = (raydir - (obj_dir * dot(raydir, obj_dir)));
	a = dot(tmp, tmp);
	b = 2.0 * dot((raydir - (obj_dir * dot(raydir, obj_dir))), (dist - (obj_dir * dot(dist, obj_dir))));
	tmp = (dist - (obj_dir * dot(dist, obj_dir)));
	c = dot(tmp, tmp) - (rayon * rayon);
	*tmp_normale = 0;
	if ((delta = b * b - 4.0 * a * c) < 0.0)
		return (MAX_FLOAT);
	if (delta == 0.0)
		return (-b / (2.0 * a));
	else
	{
		t1 = (-b + half_sqrt(delta)) / (2.0 * a);
		t2 = (-b - half_sqrt(delta)) / (2.0 * a);
		sol2 = t1;
		if (op == 0)
		{
			toto = (t1 < t2) ? t1 : t2;
			sol2 = (t1 < t2) ? t2 : t1;
		}
		else
		{
			if (t1 > 1 && t2 > 1)
				toto = (t1 < t2) ? t1 : t2;
			else if (t2 > 1 && t1 < 1)
				toto = t2;
			else if (t1 < 1 && t2 < 1)
				toto = MAX_FLOAT;
		}
	}
	if (obj_lim[index].x == 0.0 && obj_lim[index].y == 0.0 && obj_lim[index].z == 0.0)
		return (toto);
	plane1 = set_lim(raydir, obj_pos, obj_lim[index], pos);
	plane2 = set_lim(raydir, obj_pos - (obj_dir * (obj_lim_length[index])), obj_lim[index], pos);
	if (plane1 == MAX_FLOAT && plane2 == MAX_FLOAT)
		return (MAX_FLOAT);
	if (toto < plane1 && toto < plane2 && sol2 > plane1 && sol2 > plane2)
	{
		*tmp_normale = 1;
		return ((plane1 < plane2) ? plane1 : plane2);
	}
	if ((toto < plane1 && plane2 == MAX_FLOAT) || (toto < plane2 && plane1 == MAX_FLOAT))
		return (toto);
	if (((plane1 < toto && toto < plane2) || (plane2 < toto && toto < plane1)) && plane1 != MAX_FLOAT && plane2 != MAX_FLOAT)
		return (toto);
	if (toto < plane1 && plane1 < sol2)
	{
		*tmp_normale = 1;
		return (plane1);
	}
	if (toto < plane2 && plane2 < sol2)
	{
		*tmp_normale = 1;
		return (plane2);
	}
	return (MAX_FLOAT);
}

float	inter_cone(							float4	obj_dir,
											float4	obj_pos,
											uchar	angle,
											float4	dist,
											float4	raydir,
											int		op,
					__global	read_only	float4	*obj_lim,
					__global	read_only	float	*obj_lim_length,
											float4	pos,
											short	index,
											int		*tmp_normale)
{
	float	a, b, c, delta, t1, t2;
	float4	tmp;
	float	toto, sol2, plane1, plane2;

	tmp = (raydir - (obj_dir * dot(raydir, obj_dir)));
	a = pow(half_cos((float)angle), 2.0f) * dot(tmp, tmp)
		- pow(half_sin((float)angle), 2.0f) * pow(dot(raydir, obj_dir), 2.0f);
	b = 2.0 * pow(half_cos((float)angle), 2.0f) * dot((raydir - (obj_dir * dot(raydir, obj_dir))),
			(dist - (obj_dir * dot(dist, obj_dir))))
		- 2.0 * pow(half_sin((float)angle), 2.0f) * dot(raydir, obj_dir)
		* dot(dist, obj_dir);
	tmp = (dist - (obj_dir * dot(dist, obj_dir)));
	c = pow(half_cos((float)angle), 2.0f) * dot(tmp, tmp) - (half_sin((float)angle)
			* half_sin((float)angle)) * pow(dot(dist, obj_dir), 2.0f);
	delta = b * b - 4.0 * a * c;
	*tmp_normale = 0;
	if (delta < 0.0)
	{
		return (MAX_FLOAT);
	}
	if (delta == 0.0)
		return (-b / (2.0 * a));
	else
	{
		t1 = (-b + half_sqrt(delta)) / (2.0 * a);
		t2 = (-b - half_sqrt(delta)) / (2.0 * a);
		sol2 = t1;
		if (op == 0)
		{
			if (t1 > 0 && t2 > 0)
			{
				toto = (t1 < t2) ? t1 : t2;
				sol2 = (t1 < t2) ? t2 : t1;
			}
			else if (t2 > 0 && t1 < 0)
				toto = t2;
			else if (t1 < 0 && t2 < 0)
				toto = MAX_FLOAT;
		}
		else
		{
			if (t1 > 1 && t2 > 1)
				toto = (t1 < t2) ? t1 : t2;
			else if (t2 > 1 && t1 < 1)
				toto = t2;
			else if (t1 < 1 && t2 < 1)
				toto = 0;
		}
	}
	if (obj_lim[index].x == 0.0 && obj_lim[index].y == 0.0 && obj_lim[index].z == 0.0)
		return (toto);
	plane1 = set_lim(raydir, obj_pos, obj_lim[index], pos);
	plane2 = set_lim(raydir, obj_pos + (obj_dir * (obj_lim_length[index])), obj_lim[index], pos);
	if (plane1 == MAX_FLOAT && plane2 == MAX_FLOAT)
		return (MAX_FLOAT);
	if (toto < plane1 && toto < plane2 && sol2 > plane1 && sol2 > plane2)
	{
		*tmp_normale = 1;
		return ((plane1 < plane2) ? plane1 : plane2);
	}
	if ((toto < plane1 && plane2 == MAX_FLOAT) || (toto < plane2 && plane1 == MAX_FLOAT))
		return (toto);
	if (((plane1 < toto && toto < plane2) || (plane2 < toto && toto < plane1)) && plane1 != MAX_FLOAT && plane2 != MAX_FLOAT)
		return (toto);
	if (toto < plane1 && plane1 < sol2)
	{
		*tmp_normale = 1;
		return (plane1);
	}
	if (toto < plane2 && plane2 < sol2)
	{	
		*tmp_normale = 1;
		return (plane2);
	}
	return (MAX_FLOAT);
}

float	inter_ellipsoid(					float4	obj_dir,
											float4	obj_pos,
											uchar	angle,
											float4	dist,
											float4	raydir,
											int		op,
					__global	read_only	float4	*obj_lim,
					__global	read_only	float	*obj_lim_length,
											float4	pos,
											short	index,
											int		*tmp_normale,
											float4	obj_size)
{
	float	a, b, c, delta, t1, t2;
	float	toto, sol2, plane1, plane2;
	a = ((raydir.x * raydir.x) / (obj_size.x * obj_size.x))
	+ ((raydir.y * raydir.y) / (obj_size.y * obj_size.y))
	+ ((raydir.z * raydir.z) / (obj_size.z * obj_size.z));
	b = ((2.0f * dist.x * raydir.x) / (obj_size.x * obj_size.x))
	+ ((2.0f * dist.y * raydir.y) / (obj_size.y * obj_size.y))
	+ ((2.0f * dist.z * raydir.z) / (obj_size.z * obj_size.z));
	c = ((dist.x * dist.x) / (obj_size.x * obj_size.x))
	+ ((dist.y * dist.y) / (obj_size.y * obj_size.y))
	+ ((dist.z * dist.z) / (obj_size.z * obj_size.z)) - 1.0f;
	if ((delta = b * b - 4 * a * c) < 0.0)
		return (MAX_FLOAT);
	else
	{
		t1 = (-b + sqrt(delta)) / (2.0f * a);
		t2 = (-b - sqrt(delta)) / (2.0f * a);
		if (op == 0)
		{
			if (t1 > 0 && t2 > 0)
			{
				toto = (t1 < t2) ? t1 : t2;
				sol2 = (t1 < t2) ? t2 : t1;
			}
			else if (t2 > 0 && t1 < 0)
				toto = t2;
			else if (t1 < 0 && t2 < 0)
				toto = MAX_FLOAT;
		}
		else
		{
			if (t1 > 1 && t2 > 1)
				toto = (t1 < t2) ? t1 : t2;
			else if (t2 > 1 && t1 < 1)
				toto = t2;
			else if (t1 < 1 && t2 < 1)
				toto = 0;
		}
	}
	if (obj_lim[index].x == 0.0 && obj_lim[index].y == 0.0 && obj_lim[index].z == 0.0)
		return (toto);
	plane1 = set_lim(raydir, obj_pos, obj_lim[index], pos);
	plane2 = set_lim(raydir, obj_pos + (obj_dir * (obj_lim_length[index])), obj_lim[index], pos);
	if (plane1 == MAX_FLOAT && plane2 == MAX_FLOAT)
		return (MAX_FLOAT);
	if (toto < plane1 && toto < plane2 && sol2 > plane1 && sol2 > plane2)
	{
		*tmp_normale = 1;
		return ((plane1 < plane2) ? plane1 : plane2);
	}
	if ((toto < plane1 && plane2 == MAX_FLOAT) || (toto < plane2 && plane1 == MAX_FLOAT))
		return (toto);
	if (((plane1 < toto && toto < plane2) || (plane2 < toto && toto < plane1)) && plane1 != MAX_FLOAT && plane2 != MAX_FLOAT)
		return (toto);
	if (toto < plane1 && plane1 < sol2)
	{
		*tmp_normale = 1;
		return (plane1);
	}
	if (toto < plane2 && plane2 < sol2)
	{	
		*tmp_normale = 1;
		return (plane2);
	}
	return (MAX_FLOAT);
}

float	cast_ray(__global	read_only	uchar	*obj_type,
				__global	read_only	float4	*obj_pos,
				__global	read_only	float4	*obj_dir,
				__global	read_only	uchar	*obj_angle,
				__global	read_only	float	*obj_rayon,
										short	index,
										float4	dist,
										float4	raydir,
										int		op,
				__global	read_only	float4	*obj_lim,
				__global	read_only	float	*obj_lim_length,
										float4	pos,
										int		*tmp_normale,
				__global	read_only	float4	*elli_rayon)
{
	float	t = MAX_FLOAT;
	int		tmp;

	tmp = *tmp_normale;
	if (obj_type[index] == PLANE)
		t = inter_plane(obj_dir[index], dist, raydir);
	else if (obj_type[index] == SPHERE)
		t = inter_sphere(obj_rayon[index], obj_pos[index], dist, raydir, op, obj_lim, obj_lim_length, pos, index, &tmp);
	else if (obj_type[index] == CYLINDER)
		t = inter_cylinder(obj_dir[index], obj_pos[index], obj_rayon[index], dist, raydir, op, obj_lim, obj_lim_length, pos, index, &tmp);
	else if (obj_type[index] == ELLIPSOID)
		t = inter_ellipsoid(obj_dir[index], obj_pos[index], obj_angle[index], dist, raydir, op, obj_lim, obj_lim_length, pos, index, &tmp, elli_rayon[index]);
	else
		t = inter_cone(obj_dir[index], obj_pos[index], obj_angle[index], dist, raydir, op, obj_lim, obj_lim_length, pos, index, &tmp);
	*tmp_normale = tmp;
	return (t);
}

float4	get_inters(float4 origin, float4 raydir, float t)
{
	return (mad(raydir, t, origin));
}

float4	project(float4 a, float4 b)
{
	float t = dot(b, b);

	if (t)
		return (b * ((dot(a, b)) / (t)));
	return (a);
}

float4	get_normale(						short	index,
											float4	*obj_inters,
					__global	read_only	float4	*obj_pos,
					__global	read_only	float4	*obj_dir,
					__global	read_only	uchar	*obj_type,
					__global	read_only	float4	*obj_lim,
											int		*tmp_normale,
					__global	read_only	float4	*elli_rayon,
					__global	read_only	uchar	*obj_perlin,
											int		move,
											float	*perl)
{
	float4	normale;

	if (obj_type[index] == PLANE)
		normale = obj_dir[index];
	else if (*tmp_normale == 0)
	{
		if (obj_type[index] == SPHERE)
			normale = normalize(obj_inters[index] - obj_pos[index]);
		else if (obj_type[index] == CONE || obj_type[index] == CYLINDER)
			normale = normalize(((obj_inters[index] - obj_pos[index]) -
						project((obj_inters[index] - obj_pos[index]), obj_dir[index])));
		else if (obj_type[index] == ELLIPSOID)
		{
			normale = obj_inters[index] - obj_pos[index];
			normale.x = 2.0f * normale.x / (elli_rayon[index].x * elli_rayon[index].x);
			normale.y = 2.0f * normale.y / (elli_rayon[index].y * elli_rayon[index].y);
			normale.z = 2.0f * normale.z / (elli_rayon[index].z * elli_rayon[index].z);
			normale = normalize(normale);
		}
		else
			normale = obj_dir[index];
	}
	else
		normale = -obj_lim[index];
	if (obj_perlin[index] != 0 && obj_perlin[index] != MARBLE)
		normale *= 1 - *perl;
	return (normale);
}

uint	hsl(uint color, float ambient, float shade, uint obj_color)
{
//	printf("%f\n", shade);
//	shade = ambient / shade;
	shade = 1 - 1 / shade * ambient;
//	shade = shade - 0.5;
//	shade = ambient - (ambient / shade);
	short r = shade * (color & 0xFF);
	short g = shade * ((color & 0xFF00) >> 8);
	short b = shade * ((color & 0xFF0000) >> 16);

//	printf("RGB : %d : %d : %d\n", r, g, b);
	r = LIMIT(r, ambient * R(color), 255);
	g = LIMIT(g, ambient * G(color), 255);
	b = LIMIT(b, ambient * B(color), 255);
	return (RGB(r, g, b));
}

uint	lambert(						float3	ambient,
				__global	read_only	uint	*light_color,
				__global	read_only	float	*light_coef,
										uint	color,
										float	dot,
										uint	obj_color,
										int		ilight)
{
	dot = dot < 0 ? 0 : dot;
	if (ambient.z == 1)
	{
		if (dot < 0.2f)
			dot = 0;
		else if (dot >= 0.2f && dot < 0.4f)
			dot = 0.2f;
		else if (dot >= 0.4f && dot < 0.5f)
			dot = 0.4f;
		else if (dot >= 0.5f)
			dot = 1;
	}
	short r = (R(color) + R(light_color[ilight]) * light_coef[ilight]) * dot;
	short g = (G(color) + G(light_color[ilight]) * light_coef[ilight]) * dot;
	short b = (B(color) + B(light_color[ilight]) * light_coef[ilight]) * dot;
	r = LIMIT(r, (ambient.x * R(color)), 255);
	g = LIMIT(g, (ambient.x * G(color)), 255);
	b = LIMIT(b, (ambient.x * B(color)), 255);
	return (RGB(r, g, b));
}

uint	spec_light(__global	read_only	uint	*light_color,
				__global	read_only	float4	*obj_indice,
										short	index,
										uint	color,
										float	alpha,
										uint	obj_color,
										int		ilight)
{
	short r = ((R(color) + R(light_color[ilight])) * obj_indice[index].x) * pow((alpha), obj_indice[index].y);
	short g = ((G(color) + G(light_color[ilight])) * obj_indice[index].x) * pow((alpha), obj_indice[index].y);
	short b = ((B(color) + B(light_color[ilight])) * obj_indice[index].x) * pow((alpha), obj_indice[index].y);
	r = LIMIT(r, (short)R(color), 255);
	g = LIMIT(g, (short)G(color), 255);
	b = LIMIT(b, (short)B(color), 255);
	return (RGB(r, g, b));
}

uint	reflect(float ambient, uint reflect, uint color, float coef, uint obj_color)
{
	short r = (R(reflect) * coef + R(color));
	short g = (G(reflect) * coef + G(color));
	short b = (B(reflect) * coef + B(color));
	r = LIMIT(r, (ambient * R(color)), 255);
	g = LIMIT(g, (ambient * G(color)), 255);
	b = LIMIT(b, (ambient * B(color)), 255);
	return (RGB(r, g, b));
}

uint		darker(uint color1, uint color2)
{
	short r1 = R(color1);
	short g1 = G(color1);
	short b1 = B(color1);
	
	short r2 = R(color2);
	short g2 = G(color2);
	short b2 = B(color2);

	if (r2 < r1)
		r1 = r2;
	if (g2 < g1)
		g1 = g2;
	if (b2 < b1)
		b1 = b2;
	return (RGB(r1, g1, b1));
}

uint		lighter(uint color1, uint color2)
{
	short r1 = R(color1);
	short g1 = G(color1);
	short b1 = B(color1);
	
	short r2 = R(color2);
	short g2 = G(color2);
	short b2 = B(color2);

	if (r2 > r1)
		r1 = r2;
	if (g2 > g1)
		g1 = g2;
	if (b2 > b1)
		b1 = b2;
	return (RGB(r1, g1, b1));
}

uint		specular(					uint	color,
										float3	ambient,
				__global	read_only	float	*light_coef,
				__global	read_only	float4	*obj_pos,
				__global	read_only	float4	*obj_dir,
				__global	read_only	uchar	*obj_type,
				__global	read_only	uint	*light_color,
				__global	read_only	float4	*obj_indice,
										short	index,
				__global	read_only	float4	*light_pos,
										float4	*obj_inters,
										float	dot_lambert,
				__global	read_only	float4	*obj_lim,
										int		*tmp_normale,
				__global	read_only	uint	*obj_color,
										int		ilight,
				__global	read_only	float4	*elli_rayon,
				__global	read_only	uchar	*obj_perlin,
										int		move,
										float	*perl)
{
	float	alpha;
	float4	rayd;
	float4	v2;
	float4	r;
	float4	normale;

	if (ambient.z == 0)
	{
		rayd = normalize(obj_inters[index] - light_pos[ilight]);
		normale = get_normale(index, obj_inters, obj_pos, obj_dir, obj_type, obj_lim, tmp_normale, elli_rayon, obj_perlin, move, perl);
		v2 = normale * 2.0f * (dot(-normale, rayd));
		r = normalize(rayd + v2);
		alpha = dot(-rayd, r);
		if (alpha >= 0.0f && dot(normale, rayd) < 0.0f && obj_indice[index].x != 0.0f)
			color = (spec_light(light_color, obj_indice, index, color, alpha, obj_color[index], ilight));
	}
	if (dot_lambert >= 0.0f)
		return (lambert(ambient, light_color, light_coef, color, dot_lambert, obj_color[index], ilight));
	return (colorize_obj(ambient.x, color, ambient.x));
}

float4	rot(float4 v, float anglex, float angley)
{
	float tmpx = v.x;
	float tmpy = v.y;
	v.y = (v.y * half_cos(anglex)) - (v.z * half_sin(anglex));
	v.z = (tmpy * half_sin(anglex)) + (v.z * half_cos(anglex));
	tmpx = v.x;
	v.x = (v.x * half_cos(angley)) + (v.z * half_sin(angley));
	v.z = (tmpx * (-half_sin(angley))) + (v.z * half_cos(angley));
	return (v);
}


uint		is_in_shadow(					uint	color,
					__global	read_only	float4	*light_pos,
											float4	*obj_inters,
					__global	read_only	uchar	*obj_id,
					__global	read_only	float4	*obj_pos,
					__global	read_only	float4	*obj_dir,
					__global	read_only	uchar	*obj_angle,
					__global	read_only	uchar	*obj_type,
					__global	read_only	float	*obj_rayon,
					__global	read_only	uint	*light_color,
					__global	read_only	float	*light_coef,
											short	index,
											uchar2	m,
											float3	ambient,
					__global	read_only	float4	*obj_indice,
					__global	read_only	float4	*obj_lim,
					__global	read_only	float	*obj_lim_length,
											int		*tmp_normale,
					__global	read_only	uint	*obj_color,
											int		ilight,
					__global	read_only	float	*obj_damier,
					__global	read_only	float4	*elli_rayon,
					__global	read_only	uchar	*obj_perlin,
											int		move,
											uint	true_color,
											float	*perl)
{
	float	t;
	float	dist;
	float4	raydir;
	float4	inters;
	float4	newraydir;
	float4	distance;
	int		tmp;
	int		i = 0;
	int		j = 0;
	int 	nb_light = 0;
	uint	colors;
	uint	tmp_colors;
	float	dot_lambert = -2.0f;

	while (j < m.x)
	{
		raydir = light_pos[j] - obj_inters[index];
		dist = fast_length(raydir);
		raydir = normalize(raydir);
		t = MAX_FLOAT;
		i = 0;
		while (i < m.y)
		{
			if (obj_id[index] != obj_id[i])
			{
				distance = light_pos[j] - obj_pos[i];
				t = cast_ray(obj_type, obj_pos, obj_dir, obj_angle, obj_rayon, i, distance, -raydir, 0, obj_lim, obj_lim_length, light_pos[j], &tmp, elli_rayon);
				if (t != MAX_FLOAT && t >= 0)
				{
					inters = get_inters(light_pos[j], raydir, t);
					newraydir = light_pos[j] - inters;
					if  (dist > fast_length(newraydir))
					{
						dot_lambert = dot(get_normale(index, obj_inters, obj_pos, obj_dir, obj_type, obj_lim, tmp_normale, elli_rayon, obj_perlin, move, perl), raydir);
						colors = lambert(ambient, light_color, light_coef, color, dot_lambert, obj_color[i], ilight);
						if (nb_light != 0)
							colors = darker(colors, tmp_colors);
						else
							tmp_colors = colors;
						nb_light++;
						break;
					}
				}
			}
			i++;
		}
		j++;
	}
	if (nb_light > 0 && ilight > 0)
		return (true_color);
	if (nb_light > 0)
	{
		uint colorz = hsl(color, ambient.x, (float)m.x / (float)nb_light, color);
		return (darker(colorz, colors));
	}
	raydir = light_pos[ilight] - obj_inters[index];
	raydir = normalize(raydir);
	if (obj_type[index] == PLANE)
		color = damier(obj_inters[index], ambient, color, obj_damier[index]);
	if (dot_lambert == -2.0f)
		dot_lambert = dot(get_normale(index, obj_inters, obj_pos, obj_dir, obj_type, obj_lim, tmp_normale, elli_rayon, obj_perlin, move, perl), raydir);
	return (specular(color, ambient, light_coef, obj_pos, obj_dir, obj_type, light_color, obj_indice, index, light_pos, obj_inters, dot_lambert, obj_lim, tmp_normale, obj_color, ilight, elli_rayon, obj_perlin, move, perl));
}

uint		multiple_shadow(				uint	color,
					__global	read_only	float4	*light_pos,
											float4	*obj_inters,
					__global	read_only	uchar	*obj_id,
					__global	read_only	float4	*obj_pos,
					__global	read_only	float4	*obj_dir,
					__global	read_only	uchar	*obj_angle,
					__global	read_only	uchar	*obj_type,
					__global	read_only	float	*obj_rayon,
					__global	read_only	uint	*light_color,
					__global	read_only	float	*light_coef,
											short	index,
											uchar2	m,
											float3	ambient,
					__global	read_only	float4	*obj_indice,
					__global	read_only	float4	*obj_lim,
					__global	read_only	float	*obj_lim_length,
											int		*tmp_normale,
					__global	read_only	uint	*obj_color,
					__global	read_only	float	*obj_damier,
					__global	read_only	float4	*elli_rayon,
					__global	read_only	uchar	*obj_perlin,
											int		move,
											float	*perl)
{
	if (obj_perlin[index] != 0)
		color = hub_perlin(color, obj_perlin[index], obj_inters, obj_type, index, ambient, obj_damier[index], move, perl);
	int ilight = 0;
	uint true_color = is_in_shadow(color, light_pos, obj_inters, obj_id, obj_pos, obj_dir, obj_angle, obj_type, obj_rayon, light_color, light_coef, index, m, ambient, obj_indice, obj_lim, obj_lim_length, tmp_normale, obj_color, ilight, obj_damier, elli_rayon, obj_perlin, move, true_color, perl);
	ilight++;
	uint tmp_color = color;
	while (ilight < m.x)
	{
		tmp_color = is_in_shadow(tmp_color, light_pos, obj_inters, obj_id, obj_pos, obj_dir, obj_angle, obj_type, obj_rayon, light_color, light_coef, index, m, ambient, obj_indice, obj_lim, obj_lim_length, tmp_normale, obj_color, ilight, obj_damier, elli_rayon, obj_perlin, move, true_color, perl);
		true_color = lighter(tmp_color, true_color);
		ilight++;
	}
	color = true_color;
	return (color);
}

uint	reflexion(						uint	color,
										float4	raydir,
										uchar	nb_reflet,
										short	index,
										float4	*obj_inters,
				__global	read_only	float4	*obj_pos,
				__global	read_only	float4	*obj_dir,
				__global	read_only	uchar	*obj_type,
										float4	cam_pos,
										uchar2	m,
				__global	read_only	uchar	*obj_id,
				__global	read_only	uchar	*obj_angle,
				__global	read_only	float	*obj_rayon,
				__global	read_only	float4	*light_pos,
				__global	read_only	uint	*light_color,
				__global	read_only	float	*light_coef,
										float3	ambient,
				__global	read_only	float4	*obj_indice,
				__global	read_only	uint	*obj_color,
										float	*tmp_t,
										float4	*tmp_inters,
										float4	*tmp_raydir,
										short	*tmp_index,
				__global	read_only	float4	*obj_lim,
				__global	read_only	float	*obj_lim_length,
										int		*tmp_normale,
				__global	read_only	uchar	*obj_perlin,
				__global	read_only	float	*obj_damier,
				__global	read_only	float4	*elli_rayon,
										int		move,
										float	*perl)
{
	float	tmin;
	float	t;
	float4	dist;
	float4	v;
	float4	normale;
	int		tmp;
	uchar	i = 0;
	short	index2 = -1;

	normale = get_normale(index, obj_inters, obj_pos, obj_dir, obj_type, obj_lim, tmp_normale, elli_rayon, obj_perlin, move, perl);
	if (nb_reflet == 0)
		v = obj_inters[index] - cam_pos;
	else
		v = raydir;

	if ((obj_lim[index].x == 0 && obj_lim[index].y == 0 && obj_lim[index].z == 0) || obj_type[index] == PLANE || obj_type[index] == CYLINDER)
		raydir = (v - (normale * (2 * dot(normale, v))));
	else
	{
		if (fabs(obj_lim[index].x) >= fabs(obj_lim[index].y) && fabs(obj_lim[index].x) >= fabs(obj_lim[index].z))
		{
			v.x = -v.x;
			raydir = (v - (normale * (2 * dot(normale, v))));
			v.x = -v.x;
		}
		else if (fabs(obj_lim[index].y) >= fabs(obj_lim[index].x) && fabs(obj_lim[index].y) >= fabs(obj_lim[index].z))
		{
			v.y = -v.y;
			raydir = (v - (normale * (2 * dot(normale, v))));
			v.y = -v.y;
		}
		else if (fabs(obj_lim[index].z) >= fabs(obj_lim[index].y) && fabs(obj_lim[index].z) >= fabs(obj_lim[index].x))
		{
			v.z = -v.z;
			raydir = (v - (normale * (2 * dot(normale, v))));
			v.z = -v.z;
		}
	}
	raydir = normalize(raydir);
	t = MAX_FLOAT;
	tmin = MAX_FLOAT;
	while (i < m.y)
	{
		if (obj_id[i] != obj_id[index])
		{
			dist = obj_inters[index] - obj_pos[i];
			t = cast_ray(obj_type, obj_pos, obj_dir, obj_angle, obj_rayon, i, dist, raydir, 0, obj_lim, obj_lim_length, obj_inters[index], tmp_normale, elli_rayon);
			if (t < tmin && t >= 0.0)
			{
				tmp = *tmp_normale;
				tmin = t;
				index2 = i;
			}
		}
		i++;
	}
	*tmp_normale = tmp;
	*tmp_t = tmin;
	*tmp_index = index2;
	*tmp_raydir = raydir;
	*tmp_inters = get_inters(obj_inters[index], raydir, tmin) - obj_inters[index];
	obj_inters[index2] = get_inters(obj_inters[index], raydir, tmin);
	if (tmin != MAX_FLOAT)
	{
		if (obj_type[index2] == PLANE)
			return (reflect(ambient.x, damier(obj_inters[index2], ambient, hub_perlin(multiple_shadow(obj_color[index2], light_pos, obj_inters, obj_id, obj_pos, obj_dir, obj_angle, obj_type, obj_rayon, light_color, light_coef, index2, m, ambient, obj_indice, obj_lim, obj_lim_length, tmp_normale, obj_color, obj_damier, elli_rayon, obj_perlin, move, perl), obj_perlin[index2], obj_inters, obj_type, index2, ambient, obj_damier[index2], move, perl), obj_damier[index2]), color, obj_indice[index].z, obj_color[index2]));
		return (reflect(ambient.x, hub_perlin(multiple_shadow(obj_color[index2], light_pos, obj_inters, obj_id, obj_pos, obj_dir, obj_angle, obj_type, obj_rayon, light_color, light_coef, index2, m, ambient, obj_indice, obj_lim, obj_lim_length, tmp_normale, obj_color, obj_damier, elli_rayon, obj_perlin, move, perl), obj_perlin[index2], obj_inters, obj_type, index2, ambient, obj_damier[index2], move, perl), color, obj_indice[index].z, obj_color[index2]));
	}
	return (reflect(ambient.x, 0, color, obj_indice[index].z, obj_color[index]));
}

float4	calc_trans_ray(							float4	raydir,
												short	index,
												float4	*obj_inters,
						__global	read_only	float4	*obj_pos,
						__global	read_only	float4	*obj_dir,
						__global	read_only	uchar	*obj_type,
												float	n1,
												float	n2,
						__global	read_only	float4	*obj_lim,
												int		*tmp_normale,
						__global	read_only	float4	*elli_rayon,
						__global	read_only	uchar	*obj_perlin,
												int		move,
												float	*perl)
{
	float	i1;
	float	i2;
	float4	normale = get_normale(index, obj_inters, obj_pos, obj_dir, obj_type, obj_lim, tmp_normale, elli_rayon, obj_perlin, move, perl);

	i1 = dot(raydir, normale);
	i2 = ((n1 / n2) * (n1 / n2)) * (1 - (i1 * i1));
	return (raydir * (n1 / n2)) + (normale * ((i1 * (n1 / n2)) - half_sqrt(1 - i2)));
}

uint	refraction(							uint	color,
											float4	raydir,
											uchar	nb_reflet,
											short	index,
											float4	*obj_inters,
					__global	read_only	float4	*obj_pos,
					__global	read_only	float4	*obj_dir,
					__global	read_only	uchar	*obj_type,
											float4	cam_pos,
											uchar2	m,
					__global	read_only	uchar	*obj_id,
					__global	read_only	uchar	*obj_angle,
					__global	read_only	float	*obj_rayon,
					__global	read_only	float4	*light_pos,
					__global	read_only	uint	*light_color,
					__global	read_only	float	*light_coef,
											float3	ambient,
					__global	read_only	float4	*obj_indice,
					__global	read_only	uint	*obj_color,
											float	*tmp_t,
											float4	*tmp_inters,
											float4	*tmp_raydir,
											short	*tmp_index,
											uchar	tmp_type,
					__global	read_only	float4	*obj_lim,
					__global	read_only	float	*obj_lim_length,
											int		*tmp_normale,
					__global	read_only	uchar	*obj_perlin,
					__global	read_only	float	*obj_damier,
					__global	read_only	float4	*elli_rayon,
											int		move,
											float	*perl)
{
	float	t;
	float	tmin;
	float4	dist;
	int		tmp;
	uchar	i = 0;
	short	index2 = -1;

	if (tmp_type == 1 && nb_reflet == 0)
		raydir = calc_trans_ray(raydir, index, obj_inters, obj_pos, obj_dir, obj_type, 1.0, obj_indice[index].w, obj_lim, tmp_normale, elli_rayon, obj_perlin, move, perl);
	else if (tmp_type == 2 && nb_reflet == 0)
		raydir = calc_trans_ray(raydir, index, obj_inters, obj_pos, obj_dir, obj_type, obj_indice[index].w, 1.0, obj_lim, tmp_normale, elli_rayon, obj_perlin, move, perl);
	else if (nb_reflet > 0)
		raydir = calc_trans_ray(raydir, index, obj_inters, obj_pos, obj_dir, obj_type, 1.0, 1.0, obj_lim, tmp_normale, elli_rayon, obj_perlin, move, perl);

	raydir = normalize(raydir);
	t = MAX_FLOAT;
	tmin = MAX_FLOAT;
	while (i < m.y)
	{
		dist = obj_inters[index] - obj_pos[i];
		t = cast_ray(obj_type, obj_pos, obj_dir, obj_angle, obj_rayon, i, dist, raydir, 1, obj_lim, obj_lim_length, obj_inters[index], tmp_normale, elli_rayon);
		if (t < tmin && t > 1)
		{
			tmp = *tmp_normale;
			tmin = t;
			index2 = i;
		}
		i++;
	}
//	if (obj_type[index] == PLANE && obj_type[index2] == CYLINDER)
//		*tmp_normale = (*tmp_normale == 1) ? 0 : 1;
	*tmp_normale = tmp;
	*tmp_t = tmin;
	*tmp_raydir = raydir;
	*tmp_inters = get_inters(obj_inters[index], raydir, tmin);
	obj_inters[index2] = get_inters(obj_inters[index], raydir, tmin);
	if (tmin != MAX_FLOAT)
	{
		*tmp_index = index2;
		if (obj_type[index2] == PLANE)
			return (reflect(ambient.x, damier(obj_inters[index2], ambient, hub_perlin(multiple_shadow(obj_color[index2], light_pos, obj_inters, obj_id, obj_pos, obj_dir, obj_angle, obj_type, obj_rayon, light_color, light_coef, index2, m, ambient, obj_indice, obj_lim, obj_lim_length, tmp_normale, obj_color, obj_damier, elli_rayon, obj_perlin, move, perl), obj_perlin[index2], obj_inters, obj_type, index2, ambient, obj_damier[index2], move, perl), obj_damier[index2]), color, 1 - obj_indice[index2].z, obj_color[index2]));	
		return (reflect(ambient.x, hub_perlin(multiple_shadow(obj_color[index2], light_pos, obj_inters, obj_id, obj_pos, obj_dir, obj_angle, obj_type, obj_rayon, light_color, light_coef, index2, m, ambient, obj_indice, obj_lim, obj_lim_length, tmp_normale, obj_color, obj_damier, elli_rayon, obj_perlin, move, perl), obj_perlin[index2], obj_inters, obj_type, index2, ambient, obj_damier[index2], move, perl), color, 1 - obj_indice[index2].z, obj_color[index2]));
	}
	return (reflect(ambient.x, 0, color, 1 - obj_indice[index].z, obj_color[index]));
}

uint		calc_ray(					float2	plan,
										short2	screen,
										uchar2	m,
										float4	cam_pos,
				__global	read_only	float4	*obj_pos,
				__global	read_only	float4	*obj_dir,
				__global	read_only	float	*obj_rayon,
				__global	read_only	uint	*obj_color,
				__global	read_only	uchar	*obj_type,
				__global	read_only	uchar	*obj_angle,
				__global	read_only	float4	*obj_indice,
				__global	read_only	uchar	*obj_id,
				__global	read_only	float4	*light_pos,
				__global	read_only	float	*light_coef,
				__global	read_only	uint	*light_color,
				__global	read_only	uchar	*light_id,
										float3	ambient,
										float4	*obj_inters,
										float2	rot_angle,
				__global	read_only	float4	*obj_lim,
				__global	read_only	float	*obj_lim_length,
										float	*closest,
										float4	*cam_dir,
										uchar4	ambient2,
				__global	read_only	uchar	*obj_perlin,
				__global	read_only	float	*obj_damier,
				__global	read_write	float4	*closest_normal,
				__global	read_only	float4	*elli_rayon,
										int		move)
{
	float4	raydir;
	float	t, tmin = MAX_FLOAT;
	float4	dist;
	uint	color = 0;
	uchar	i = 0;
	short	index = -1;
	float	tmp_t = 0;
	uchar	nb_reflet = 0;
	short	tmp_index = -1;
	float4	tmp_raydir;
	float4	tmp_inters;
	int		tmp_normale;
	int		save_n;
	short	tmp_index2;
	float4	tmp_raydir2;
	uchar	tmp_type;
	float	perl;


	tmp_normale = 0;
	raydir.x = -MIDX + plan.x;
	raydir.y = -MIDY + plan.y;
	raydir.z = -PLANEDIST(120);
	raydir.w = 0;
	raydir = normalize(rot(raydir, rot_angle.x, rot_angle.y));
	*cam_dir = raydir;
	while (i < m.y)
	{
		dist = cam_pos - obj_pos[i];
		t = cast_ray(obj_type, obj_pos, obj_dir, obj_angle, obj_rayon, i, dist, raydir, 0, obj_lim, obj_lim_length, cam_pos, &tmp_normale, elli_rayon);
		if (t < tmin && t >= 0.0)
		{
			save_n = tmp_normale;
			tmin = t;
			if (tmin < *closest || *closest == -1)
				*closest = tmin;
			index = i;
		}
		i++;
	}
	tmp_normale = save_n;
	if (tmin != MAX_FLOAT)
	{
		color = obj_color[index];
		obj_inters[index] = get_inters(cam_pos, raydir, tmin);
		if (obj_perlin[index] != 0)
			color = hub_perlin(color, obj_perlin[index], obj_inters, obj_type, index, ambient, obj_damier[index], move, &perl);
		*closest_normal = get_normale(index, obj_inters, obj_pos, obj_dir, obj_type, obj_lim, &tmp_normale, elli_rayon, obj_perlin, move, &perl);
		int ilight = 0;

		uint true_color = is_in_shadow(color, light_pos, obj_inters, obj_id, obj_pos, obj_dir, obj_angle, obj_type, obj_rayon, light_color, light_coef, index, m, ambient, obj_indice, obj_lim, obj_lim_length, &tmp_normale, obj_color, ilight, obj_damier, elli_rayon, obj_perlin, move, true_color, &perl);
		ilight++;
		uint tmp_color = color;
		while (ilight < m.x)
		{
			tmp_color = is_in_shadow(tmp_color, light_pos, obj_inters, obj_id, obj_pos, obj_dir, obj_angle, obj_type, obj_rayon, light_color, light_coef, index, m, ambient, obj_indice, obj_lim, obj_lim_length, &tmp_normale, obj_color, ilight, obj_damier, elli_rayon, obj_perlin, move, true_color, &perl);
			true_color = lighter(tmp_color, true_color);
			ilight++;
		}
		color = true_color;
		if (obj_type[index] == PLANE)
			color = damier(obj_inters[index], ambient, color, obj_damier[index]);
		if (ambient.z == 0)
		{
			tmp_index2 = index;
			tmp_normale = save_n;
			tmp_raydir2 = raydir;
			while (nb_reflet < ambient2.y && tmp_t != MAX_FLOAT && obj_indice[index].z)
			{
				if (nb_reflet > 0)
				{
					index = tmp_index;
					raydir = tmp_raydir;
				}
				if (obj_indice[index].w != 0.0 && nb_reflet == 1)
				{
					color = refraction(color, raydir, nb_reflet, index, obj_inters, obj_pos, obj_dir, obj_type, cam_pos, m, obj_id, obj_angle, obj_rayon, light_pos, light_color, light_coef, ambient, obj_indice, obj_color, &tmp_t, &tmp_inters, &tmp_raydir, &tmp_index, tmp_type, obj_lim, obj_lim_length, &tmp_normale, obj_perlin, obj_damier, elli_rayon, move, &perl);
					index = tmp_index;
					raydir = tmp_raydir;
					color = refraction(color, raydir, nb_reflet, index, obj_inters, obj_pos, obj_dir, obj_type, cam_pos, m, obj_id, obj_angle, obj_rayon, light_pos, light_color, light_coef, ambient, obj_indice, obj_color, &tmp_t, &tmp_inters, &tmp_raydir, &tmp_index, tmp_type, obj_lim, obj_lim_length, &tmp_normale, obj_perlin, obj_damier, elli_rayon, move, &perl);
					index = tmp_index;
					raydir = tmp_raydir;	
					color = refraction(color, raydir, nb_reflet, index, obj_inters, obj_pos, obj_dir, obj_type, cam_pos, m, obj_id, obj_angle, obj_rayon, light_pos, light_color, light_coef, ambient, obj_indice, obj_color, &tmp_t, &tmp_inters, &tmp_raydir, &tmp_index, tmp_type, obj_lim, obj_lim_length, &tmp_normale, obj_perlin, obj_damier, elli_rayon, move, &perl);
				break;	
				}
				color = reflexion(color, raydir, nb_reflet, index, obj_inters, obj_pos, obj_dir, obj_type, cam_pos, m, obj_id, obj_angle, obj_rayon, light_pos, light_color, light_coef, ambient, obj_indice, obj_color, &tmp_t, &tmp_inters, &tmp_raydir, &tmp_index, obj_lim, obj_lim_length, &tmp_normale, obj_perlin, obj_damier, elli_rayon, move, &perl);
				nb_reflet++;
			}
			nb_reflet = 0;
			tmp_t = 0;
			index = tmp_index2;
			tmp_normale = save_n;
			raydir = tmp_raydir2;
			if (obj_indice[index].w != 0.0)
			{
				while (nb_reflet < ambient2.z && tmp_t != MAX_FLOAT)
				{
					if (nb_reflet % 2 == 0)
						tmp_type = 1;
					else
						tmp_type = 2;
					if (nb_reflet > 0)
					{
						index = tmp_index;
						raydir = tmp_raydir;
					}
					if (obj_indice[index].w == 0.0 && nb_reflet == 1)
					{
						color = reflexion(color, raydir, 0, index, obj_inters, obj_pos, obj_dir, obj_type, cam_pos, m, obj_id, obj_angle, obj_rayon, light_pos, light_color, light_coef, ambient, obj_indice, obj_color, &tmp_t, &tmp_inters, &tmp_raydir, &tmp_index, obj_lim, obj_lim_length, &tmp_normale, obj_perlin, obj_damier, elli_rayon, move, &perl);
						index = tmp_index;
						raydir = tmp_raydir;
						color = reflexion(color, raydir, 1, index, obj_inters, obj_pos, obj_dir, obj_type, cam_pos, m, obj_id, obj_angle, obj_rayon, light_pos, light_color, light_coef, ambient, obj_indice, obj_color, &tmp_t, &tmp_inters, &tmp_raydir, &tmp_index, obj_lim, obj_lim_length, &tmp_normale, obj_perlin, obj_damier, elli_rayon, move, &perl);
						index = tmp_index;
						raydir = tmp_raydir;
						color = reflexion(color, raydir, 2, index, obj_inters, obj_pos, obj_dir, obj_type, cam_pos, m, obj_id, obj_angle, obj_rayon, light_pos, light_color, light_coef, ambient, obj_indice, obj_color, &tmp_t, &tmp_inters, &tmp_raydir, &tmp_index, obj_lim, obj_lim_length, &tmp_normale, obj_perlin, obj_damier, elli_rayon, move, &perl);
					}
					color = refraction(color, raydir, nb_reflet, index, obj_inters, obj_pos, obj_dir, obj_type, cam_pos, m, obj_id, obj_angle, obj_rayon, light_pos, light_color, light_coef, ambient, obj_indice, obj_color, &tmp_t, &tmp_inters, &tmp_raydir, &tmp_index, tmp_type, obj_lim, obj_lim_length, &tmp_normale, obj_perlin, obj_damier, elli_rayon, move, &perl);
					nb_reflet++;
				}
			}
		}
	}
	return (color);
}

float4	light_glare(						short2	screen,
											float	closest,
											float4	cam_pos,
											float2	plan,
											float2	rot_angle,
											int		planedist,
					__global	read_only	float4	*light_pos,
					__global	read_only	float	*light_coef,
					__global	read_only	uint	*light_color,
											int		n_light)
{
	int		id = -1;
	float4	colorf = (float4)(0);
	float4	cam_dir4 = (float4)(-MIDX, -MIDY, -planedist, 0.0f);
	cam_dir4 = rot(cam_dir4, rot_angle.x, rot_angle.y);
	float4	cam_dir42 = (float4)(-MIDX + plan.x, -MIDY + plan.y, -planedist, 0.0f);
	cam_dir42 = rot(cam_dir42, rot_angle.x, rot_angle.y);
	float	light_dist;
	float4	light_colorf;
	float	intensity;
#ifdef LIGHT_ILLUMINATION
	float	intensity2;
#endif

	while (++id < n_light)
	{
		light_dist = fast_length(cam_pos - light_pos[id]);
		if ((light_dist > closest && closest > 0) || dot(cam_dir42, normalize(cam_pos - light_pos[id])) > 0.0)
			continue ;
		intensity = (inter_plane(cam_dir4, cam_pos - light_pos[id], cam_dir4) * light_coef[id] * (inter_plane(normalize(cam_pos - light_pos[id]), cam_pos - light_pos[id], cam_dir42)) / pow(dot(normalize(light_pos[id] - cam_pos), normalize(cam_dir42)), 50.0f / light_coef[id] * 0.01f * fast_length(cam_pos - light_pos[id])));
#ifdef LIGHT_ILLUMINATION
		intensity2 = inter_plane(cam_dir4, cam_pos - light_pos[id], cam_dir4) * light_coef[id] / fast_length(cam_pos - light_pos[id]) * (inter_plane(normalize(cam_pos - light_pos[id]), cam_pos - light_pos[id], cam_dir42)) / (clamp(dot(normalize(light_pos[id] - cam_pos), normalize(cam_dir42)) - 0.6f, 0.00001f, 1.0f) / fast_length(cam_pos - light_pos[id]));
#endif
		light_colorf = ((float4)(R(light_color[id]) / 255.0f, G(light_color[id]) / 255.0f, B(light_color[id]) / 255.0f, 0));
		colorf += light_colorf * light_coef[id] * 100.0f / (intensity)
#ifdef LIGHT_ILLUMINATION
			+ light_colorf * light_coef[id] * 20.0f / intensity2
#endif
			;
	}
	return (colorf);
}

__kernel void			rt(__global	read_write	char	*data,
												short2	screen,
												uchar2	m,
												float4	cam_pos,
						__global	read_only	float4	*obj_pos,
						__global	read_only	float4	*obj_dir,
						__global	read_only	float	*obj_rayon,
						__global	read_only	uint	*obj_color,
						__global	read_only	uchar	*obj_type,
						__global	read_only	uchar	*obj_angle,
						__global	read_only	float4	*obj_indice,
						__global	read_only	uchar	*obj_id,
						__global	read_only	float4	*light_pos,
						__global	read_only	float	*light_coef,
						__global	read_only	uint	*light_color,
						__global	read_only	uchar	*light_id,
												float4	ambient,
												float2	rot_angle,
						__global	read_only	float4	*obj_lim,
						__global	read_only	float	*obj_lim_length,
												uchar4	ambient2,
						__global	read_only	uchar	*obj_perlin,
						__global	read_only	float	*obj_damier,
						__global	read_write	float4	*normals,
						__global	read_only	float4	*elli_rayon,
												int		move)
{
	uint	color;
	float2	plan;
	float4	aacolor;
	char	aapixelx = 0;
	char	aapixely;
	size_t	id = get_global_id(0);
	float	closest = -1;
	float4	cam_dir;
	float4	obj_inters[256] = {(float4)(0)};
	float4	tmp;

	aacolor = (float4)(0);
	while (aapixelx < ambient2.x)
	{
		aapixely = 0;
		while (aapixely < ambient2.x)
		{
			plan.x = id % screen.x + (aapixelx / (float)ambient2.x);
			plan.y = id / screen.x + (aapixely / (float)ambient2.x);
			color = calc_ray(plan, screen, m, cam_pos, obj_pos, obj_dir, obj_rayon, obj_color, obj_type, obj_angle, obj_indice, obj_id, light_pos, light_coef, light_color, light_id, ambient.xyz, obj_inters, rot_angle, obj_lim, obj_lim_length, &closest, &cam_dir, ambient2, obj_perlin, obj_damier, &normals[id], elli_rayon, move);
			aacolor += (float4)(R(color) / 255.0f, G(color) / 255.0f, B(color) / 255.0f, 0);
			aapixely++;
		}
		aapixelx++;
	}
	aacolor /= (float)(ambient2.x * ambient2.x);
	tmp = clamp(aacolor, 0.0f, 1.0f);
	if (ambient.w == 1)
	{
		tmp += clamp(light_glare(screen, closest, cam_pos, plan, rot_angle, PLANEDIST(120), light_pos, light_coef, light_color, m.x), 0.0f, 1.0f);
		tmp = clamp(tmp, 0.0f, 1.0f);
	}
	color = RGB((int)(tmp.x * 255), (int)(tmp.y * 255), (int)(tmp.z * 255));
	id *= 4;
	data[id + 2] = B(color);
	data[id + 1] = G(color);
	data[id] = R(color);
}
