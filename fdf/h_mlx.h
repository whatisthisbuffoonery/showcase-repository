/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_mlx.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:50:56 by dthoo             #+#    #+#             */
/*   Updated: 2026/03/28 08:30:56 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_MLX_H
# define H_MLX_H

# include "mlx.h"
# include <math.h>
# include <float.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <sys/time.h>
# include "libft.h"
# include "get_next_line.h"

# ifndef WIDTH
#  define WIDTH 800
# endif

# ifndef HEIGHT
#  define HEIGHT 600
# endif

# define SECOND_MCS 1000000 //7 digits

# ifndef FRAMES
#  define FRAMES 60
# endif

//# define FRAME_MCS ((SECOND_MCS / FRAMES) + 1)

# define EPSILON 1e-6f
//# define RAD (M_PI / 180.0f)
//# define STEP (1.0f * RAD)
//# define RAD_MAX (360.0f * RAD)

# define SHADE 0x00010101
# define RED 0x00010000
# define GREEN 0x00000100
# define BLUE 0x00000001
# define WHITE 0x00FFFFFF

# define UP 4
# define DOWN 5

typedef struct s_view
{
	float	x;
	float	y;
	float	z;
	float	scale;
	float	scale_mult;
	float	scale_base;
	float	step;
	float	cosx;
	float	sinx;
	float	cosy;
	float	siny;
	float	cosz;
	float	sinz;
	float	rad_max;
}			t_view;

typedef struct s_pt
{
	int				x;
	int				y;
	int				z;
	float			fx;
	float			fy;
	float			fz;
	unsigned int	colour;
	char			colour_flag;
}			t_pt;

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
}			t_keys;

typedef struct s_param
{
	t_view	view;
	t_pt	*pt;
	t_keys	keys;
}			t_param;

typedef struct s_trig
{
	float	x;
	float	y;
	float	z;
}			t_trig;

typedef struct s_data
{
	t_param			param;
	void			*mlx;
	void			*win;
	void			*img;
	char			*buf;
	unsigned int	*ubuf;
	void			(*buf_edit)(struct s_data *, float, float);
	void			(*rasterise)(t_pt *, t_view, int, struct s_data *);
	int				size;
	int				endian;
	int				line;
	int				bipp;
	int				bypp;
	unsigned int	shade;
	int				x;
	int				y;
	int				f;
	float			cx;
	float			cy;
	float			cz;
	float			offset_x;
	float			offset_y;
}					t_data;

t_view	angle_init(void);
void	view_init(t_pt *pt, int size, char **v, t_data *data);
void	center_init(t_data *data, int size);
int		pt_init(t_pt **pt, t_data *data, int *fd);
void	scale_init(t_pt *pt, int size, t_data *data, float *f);

int		fdf_cleanup(t_data *d);
int		fd_err(int *fd);
int		perspective_flag(char *v);

void	buf_edit_uint(t_data *data, float fx, float fy);
void	buf_edit_char(t_data *data, float fx, float fy);

void	rasterise_isometric(t_pt *pt, t_view view, int size, t_data *data);
void	rasterise_perspective(t_pt *pt, t_view view, int size, t_data *data);

void	xiaolin_wu(t_pt src, t_pt dst, t_data *data);
void	bresenham(t_pt src, t_pt dst, t_data *data);
void	goodlines(t_data *data);

void	change_view(t_view *view, t_keys keys);
int		frame_wait(struct timeval start);
int		draw_frame(void *param);
int		loop_me(t_data data);

int		clicked_x(void *param);

int		usage(char **v);

#endif
