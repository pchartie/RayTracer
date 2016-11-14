/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchartie <pchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:16:26 by pchartie          #+#    #+#             */
/*   Updated: 2016/10/23 16:45:35 by pchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <stdlib.h>
# include <math.h>
# include <stdio.h>

# include "../lib/libft/include/libft.h"
# include "../lib/lib_vec/include/lib_vec.h"
# include "../lib/libbmp/include/libbmp.h"

# ifdef __APPLE__
#  include "mlx_keys_macos.h"
#  include "../lib/minilibx_macos/mlx.h"
#  include <OpenCL/opencl.h>
# else
#  include "mlx_keys_linux.h"
#  include "../lib/minilibx_macos/mlx.h"
#  include <CL/cl.h>
# endif

# define SCRX			(800)
# define SCRY			(600)
# define WALKSPEED		100
# define MEM_SIZE		(SCRX * SCRY * 4)
# define PLANE			0
# define CYLINDER		1
# define SPHERE			2
# define CONE			3
# define ELLIPSOID		4
# define R(r)			(0xFF & r)
# define G(g)			((0xFF00 & g) >> 8)
# define B(b)			((0xFF0000 & b) >> 16)
# define MAX_SRC_SIZE	(0x100000)
# define NKEYS			37
# define MIN(a, b)		((a < b) ? (a) : (b))

typedef struct			s_mlx
{
	void				*init;
	void				*win;
	void				*img;
	char				*data;
	int					bpp;
	int					size;
	int					endian;
	int					allign;
}						t_mlx;

typedef struct			s_filter
{
	int					r;
	int					g;
	int					b;
	int					x;
	int					y;
	int					id;
}						t_filter;

typedef struct			s_shift
{
	struct s_mlx		*mlx;
	char				*dcpy;
	int					x;
	int					y;
	int					d;
	int					l;
	int					m;
	int					r;
	int					bpp;
	int					allign;
}						t_shift;

typedef struct			s_parse
{
	int					i_lght;
	int					i_obj;
	int					cam;
	int					ambient;
}						t_parse;

typedef struct			s_graph
{
	cl_command_queue	command_queue;
	cl_platform_id		platform_id;
	cl_device_id		device_id;
	cl_program			program;
	cl_context			context;
	cl_kernel			kernel;
	cl_float4			*fnormals;
	cl_uint				ret_num_devices;
	cl_uint				ret_num_platform;
	cl_mem				memobj;
	cl_mem				data;
	cl_mem				obj_pos;
	cl_mem				obj_dir;
	cl_mem				obj_rayon;
	cl_mem				obj_color;
	cl_mem				obj_type;
	cl_mem				obj_angle;
	cl_mem				obj_id;
	cl_mem				obj_indice;
	cl_mem				obj_lim;
	cl_mem				obj_lim_length;
	cl_mem				light_pos;
	cl_mem				light_coef;
	cl_mem				light_color;
	cl_mem				light_id;
	cl_mem				normals;
	cl_mem				obj_perlin;
	cl_mem				obj_damier;
	cl_mem				elli_rayon;
	cl_int				ret;
	int					allign1;
	size_t				core;
}						t_graph;

typedef struct			s_infos
{
	struct s_graph		*graph;
	struct s_mlx		mlx;
	long				allign;
	cl_float4			cam_pos;
	cl_float4			cam_dir;
	cl_float4			*light_pos;
	cl_float4			*obj_pos;
	cl_float4			*obj_lim;
	cl_float4			*obj_dir;
	cl_float4			*obj_indice;
	cl_float4			*elli_rayon;
	cl_float4			ambient;
	cl_float2			rot_angle;
	cl_short2			screen;
	cl_uchar4			ambient2;
	cl_uchar2			m;
	char				allign2[6];
	cl_float			*obj_lim_length;
	cl_uchar			*light_id;
	cl_uchar			*obj_id;
	cl_uchar			*obj_type;
	cl_uchar			*obj_angle;
	cl_uchar			*obj_perlin;
	cl_uint				*obj_color;
	cl_uint				*light_color;
	cl_int2				*keys;
	float				*light_coef;
	float				*obj_rayon;
	float				*obj_damier;
	cl_uint				filter_color;
	int					move;
}						t_infos;

cl_uchar2				get_m_value(char *scene);
t_infos					*parse(t_infos *i, cl_uchar2 m, char *scene);
t_mlx					ft_mlx(void);
char					*black_white(char *data, int sizeline, int bpp);
char					*sepia(char *data, int sizeline, int bpp);
char					*filter_color(t_mlx *m, cl_uint color, float coef);
void					get_cam_value(t_infos *i, int fd, char *line);
void					get_light_value(t_infos *i, int i_lght, int fd,
						char *line);
void					get_ambient_value(t_infos *i, int fd, char *line);
void					get_ind(t_infos *i, char **split, int i_obj);
void					get_ref(t_infos *i, char **split, int i_obj);
void					get_spec(t_infos *i, char **split, int i_obj);
void					get_mat(t_infos *i, char **split, int i_obj);
void					get_pos(t_infos *i, char **split, int i_obj);
void					get_dir(t_infos *i, char **split, int i_obj, int type);
void					get_lim(t_infos *i, char **split, int i_obj);
void					get_perlin(t_infos *i, char **split, int i_obj);
void					get_bonus_value(t_infos *i, char **split, int i_obj,
						int type);
void					cam_error(int i);
void					light_error(int i);
void					ambient_error(int i);
void					perlin_error(void);
void					plane_error(void);
void					cylinder_error(void);
void					sphere_error(void);
void					cone_error(void);
void					ellipsoid_error(void);
void					get_plane_value(t_infos *i, int i_obj, int fd,
						char *line);
void					get_cylinder_value(t_infos *i, int i_obj, int fd,
						char *line);
void					get_cone_value(t_infos *i, int i_obj, int fd,
						char *line);
void					get_sphere_value(t_infos *i, int i_obj, int fd,
						char *line);
void					get_ellipsoid_value(t_infos *i, int i_obj, int fd,
						char *line);
void					parse_error(int i);
void					free_split(char **split);
void					malloc_t_infos(t_infos *i, cl_uchar2 m);
void					rt_loop(t_infos *i, t_mlx mlx, t_graph *graph);
void					cl_init(t_graph *graph, t_infos *i);
void					cl_reload(t_infos *i, t_graph *graph, cl_uchar2 m);
void					cl_clean(t_graph *graph);
void					cl_kernel_set_arg(t_infos *i, t_graph *graph);
void					cl_kernel_set_buffer(t_graph *graph, cl_uchar2 m,
						t_infos *i);
void					cl_switch(t_infos *i);
void					apply_cel_shad(char *data, int bpp, int sizeline,
						cl_float4 *normals);
void					init_keys(t_infos *i);
int						is_digit(char *str);
int						check_key(int k, t_infos *i);
int						red_cross(int keycode, t_infos *i);
int						loop_hook(t_infos *i);
int						key_press(int k, t_infos *i);
int						key_release(int k, t_infos *i);
int						export_bmp(t_mlx *mlx, char *filename, char eightbits);
void					color_shift(t_mlx *mlx, int shift);
void					anaglyph(t_mlx *mlx, int shift);
void					set_to_zero_infos(t_infos *i, cl_uchar2 m);
void					barrel_distortion(t_mlx *mlx, float distortion,
						float black_dis);
void					scanline(t_mlx *mlx, float intensity, int skip);
void					pixelize(t_mlx *mlx, float intensity);
void					brightness(t_mlx *mlx, int brightness);
void					crt_effect(t_mlx *mlx);
int						ft_clamp(int x, int a, int b);

#endif
