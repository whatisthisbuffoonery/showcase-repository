/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_minirt.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 00:00:00 by achew             #+#    #+#             */
/*   Updated: 2026/09/04 22:13:38 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_MINIRT_H
# define H_MINIRT_H

# include <stdio.h>
# include "libft.h"
# include "get_next_line_bonus.h"
# include "ft_printf.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/time.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <math.h>
# include <float.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include "mlx.h"

# define A_LIGHT_RATIO_L 0.0
# define A_LIGHT_RATIO_U 1.0
# define RGB_L 0
# define RGB_U 255
# define VECTOR_L -1
# define VECTOR_U 1
# define C_FOV_L 0
# define C_FOV_U 180
# define L_BRIGHTNESS_L 0.0
# define L_BRIGHTNESS_U 1.0

# define NEAR 0.1f
# define FAR 100.0f

# define WIDTH 800.0
# define HEIGHT 600.0

# define EPSILON 1e-4//10^-4, as opposed to 10^-5. supposedly less buggy
						//relegated to just distance check
# define NEPSILON -1e-4//wasnt used
# define EPSILON_SQ 1e-8//pls don't put this near values past 1 or -1
# define DIR_TOL 1e-12

# define TIMEVAL_USEC 1e-6

/*not norminette:*/
# define RAD (M_PI / 180.0f)
# define RAD_MAX (360.0f * RAD)

# define INIT_SPHERE 0
# define INIT_PLANE 1
# define INIT_CYLINDER 2
# define INIT_CONE 3

# define UP 4
# define DOWN 5

# define SECOND_MCS 1000000 //7 digits
# define FRAMES 30

# define BUF_STEP 10

typedef struct s_keys
{
	char	w;
	char	a;
	char	s;
	char	d;
	char	q;
	char	e;
	char	up;
	char	left;
	char	down;
	char	right;
	char	space;
}			t_keys;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_ray//TODO put this in dot math
{
	t_vec3	origin;
	t_vec3	dir;
}	t_ray;

/*colours can use floats*/
typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;

typedef struct s_material
{
	t_color	color;
	double	specular;//strength
	int		checkerboard;
	void	*bump_map;
}	t_material;

typedef enum e_obj_type
{
	OBJ_SPHERE = 0,
	OBJ_PLANE = 1,
	OBJ_CYLINDER = 2,
	OBJ_CONE = 3
}	t_obj_type;

typedef enum e_plane_type
{
	INFINITE,
	ROUND,
	RECTANGLE
}	t_plane_type;

typedef double	(*t_hit_fn)(void *obj, t_ray ray);
typedef t_vec3	(*t_normal_fn)(void *obj, t_vec3 point);

typedef struct s_object
{
	/*basic data*/
	t_obj_type		type;
	t_vec3			pos;
	t_vec3			dir;
	/*pointers*/
	struct s_object	*next;
	struct s_object	*caps;//[plane], [other plane] //different linked list of planes
	int				ind;//determines which part of object

	/*random shi*/
	t_vec3			N;
	double			t;

	t_vec3			U;//plane
	t_vec3			V;

	t_vec3			p_hit;
	t_vec3			p_diff;

	double			radius;
	double			radius_sq;
	double			inv_radius;

	double			y_proj;//cylinder and cone

	double			half_angle;//cone only
	double			slope;
	double			cos_sq;
	double			cap_check;
	double			cone_factor;

	double			diameter;
	double			width;
	double			height;

	double			offset;//plane only
	double			half_w;
	double			half_h;
	t_plane_type	pl_type;

	t_material		material;
}	t_object;

typedef struct s_dot_math
{
	t_object	*obj;
	t_vec3		v;
	t_vec3		p;

	t_vec3		E;
	t_vec3		D;

	double		disc;
	double		root;
	double		denom;
	double		t[2];

	double		radial;

	double		tmp;

	double		dv;
	double		dp;
	double		pp;
	double		dd;
	double		pv;

	double		a;
	double		b;
	double		c;
	double		q;

	double		tol_a;

}	t_dot_math;

typedef struct s_quat
{
	double	w;
	double	x;
	double	y;
	double	z;
}			t_quat;

typedef struct s_light
{
	t_vec3			pos;
	double			brightness;
	t_color			color;
	struct s_light	*next;
}	t_light;

typedef struct s_camera
{
	t_quat	q;
	t_vec3	pos;
	t_vec3	dir;
	double	fov;

	t_vec3	R;//right, up, forward
	t_vec3	U;
	t_vec3	F;
	
	struct timeval	start;//rotation speed adjustment
	struct timeval	last;
}	t_camera;

typedef struct s_scene
{
	double		ambient_ratio;
	t_color		ambient_color;
	int			has_ambient;
	t_camera	camera;
	int			has_camera;
	t_light		*lights;
	t_object	*objects;
}	t_scene;

typedef struct s_rt
{
	t_scene	scene;
	int				fd;
	int				is_bonus;
	char			**tokens;
	int				(*hit[4])(double *, t_dot_math *);//put in scene instead...?
	void			(*normal[4])(t_object *, t_dot_math *m);
	void			(*move[2])(t_camera *, t_keys);
	double			coeff;
	/*see if this works...*/
	void			*mlx;
	void			*win;
	void			*img;
	char			*buf;
	unsigned int	*ubuf;
	int				size;
	int				line;
	int				endian;
	int				bipp;
	int				bypp;
	void			(*buf_edit)(struct s_rt *, t_color, int, int);
	/*mlx structs*/
	t_keys			keys;
}	t_rt;

//faster computations + norminette
/*doubles for calculations*/
typedef struct s_math
{
	double	xx;
	double	yy;
	double	zz;

	double	xy;
	double	xz;
	double	yz;

	double	wx;
	double	wy;
	double	wz;

	double	x2;
	double	y2;
	double	z2;
}	t_math;


/* main.c */
int			mand_or_bonus(void);

/* rt_init.c */
t_rt		*init_rt(void);
int			rt_mlx(t_rt *data, char **v);

/* tokenize.c */
void		tokenize_file(char *file, t_rt *rt);

/* fd_ops.c */
int			open_fd(char *file, t_rt *rt);
void		close_fd(int *fd, t_rt *rt);

/* exit.c */
void		msg_exit(char *msg, t_rt *rt);
void		perror_exit(char *msg, t_rt *rt);

/* cleanup.c */
int			clicked_x(void *param);
void		free_scene(t_rt *rt);
void		free_rt(t_rt *rt);

/* valid_ext.c */
int			correct_file_type(char *file);

/* vec3.c */
t_vec3		vec_add(t_vec3 a, t_vec3 b);
t_vec3		vec_sub(t_vec3 a, t_vec3 b);
t_vec3		vec_scale(t_vec3 a, double s);
double		vec_dot(t_vec3 a, t_vec3 b);
int			vec_in_range(t_vec3 v, double lo, double hi);
t_vec3		vec_cross(t_vec3 a, t_vec3 b);
double		vec_magnitude(t_vec3 a);
t_vec3		vec_norm(t_vec3 a);

/* parse_utils.c */
int			is_numeric_token(char *s);
t_vec3		parse_vec3(char *s, t_rt *rt);
t_color		parse_color(char *s, t_rt *rt);

/* token_utils.c */
char		*require_token(char **tokens, int i, t_rt *rt);
void		free_tokens(char **tokens);

/* parse_dispatch.c */
void		parse_tokens(char **tokens, t_rt *rt);

/* parse_ambient.c */
int			parse_ambient(char **tokens, int i, t_rt *rt);

/* parse_camera.c */
int			parse_camera(char **tokens, int i, t_rt *rt);

/* parse_light.c */
int			parse_light(char **tokens, int i, t_rt *rt);

/* parse_sphere.c */
int			parse_sphere(char **tokens, int i, t_rt *rt);

/* parse_plane.c */
int			parse_plane(char **tokens, int i, t_rt *rt);
void		plane_UVN(t_vec3 *U, t_vec3 *V, t_vec3 N);

/* parse_cylinder.c */
int			parse_cylinder(char **tokens, int i, t_rt *rt);

/* parse_cone.c */
int	parse_cone(char **tokens, int i, t_rt *rt);

/* object_list.c */
t_object	*object_new(t_obj_type type);
void		object_add_back(t_object **lst, t_object *new);

/* light_list.c */
t_light		*light_new(void);
void		light_add_back(t_light **lst, t_light *new);

/* debug_scene.c */
void		display_scene(t_scene *scene);

/* loop.c */
int	loop_me(t_rt *rt);

/* hit functions */
int	hit_sphere(double *t, t_dot_math *m);
int	hit_cylinder(double *t, t_dot_math *m);
int	hit_cone(double *t, t_dot_math *m);
int	hit_plane(double *t, t_dot_math *m);

/* buf_edit.c */
void	buf_edit_uint(t_rt *rt, t_color rgb, int x, int y);
void	buf_edit_char(t_rt *rt, t_color rgb, int x, int y);

/* what we dont have strcmp */
int	ft_strcmp(char *a, char *b);

/* cap.c */
void	init_cap(t_object *obj, double h, t_rt *rt);

/* normal.c */
void	normal_sphere(t_object *hit, t_dot_math *m);
void	normal_plane(t_object *hit, t_dot_math *m);
void	normal_cylinder(t_object *hit, t_dot_math *m);
void	normal_cone(t_object *hit, t_dot_math *m);

/* quaternion.c */
void	quat_RUF(t_vec3 *R, t_vec3 *U, t_vec3 *F, t_quat q);
t_quat	build_quat(t_vec3 a, t_vec3 b);
t_quat	mod_quat(t_quat a, t_quat b);

/* color.c */
t_color	color_add(t_color a, t_color b);
t_color	color_mul(t_color a, t_color b);
t_color	color_scale(t_color a, double b);

/* draw_frame.c */
int	draw_frame(void *param);
void	change_position(t_camera *camera, t_keys keys);
void	change_rotation(t_camera *camera, t_keys keys);

/* direction.c */
void	find_ray_dir(t_vec3 *dst, t_quat master, t_camera *c, t_vec3 ndc);
void	ndc_init(t_vec3 *ndc, t_vec3 pixel);

/* discriminant.c */
int	find_hit_normal(t_object **dst, t_vec3 D, t_rt *rt);

/* phong.c */
t_color	phong(t_object *hit, t_vec3 D, t_vec3 pixel, t_rt *rt);

#endif
