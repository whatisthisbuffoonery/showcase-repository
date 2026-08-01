/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ras.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 13:04:48 by dthoo             #+#    #+#             */
/*   Updated: 2026/03/28 07:26:25 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_mlx.h"

void	scale_init(t_pt *pt, int size, t_data *data, float *f)
{
	int		i;
	t_view	*view;

	i = 0;
	view = &data->param.view;
	while (i < size)
	{
		if (pt[i].fx > f[2])
			f[2] = pt[i].fx;
		if (pt[i].fy > f[3])
			f[3] = pt[i].fy;
		if (pt[i].fx < f[0])
			f[0] = pt[i].fx;
		if (pt[i].fy < f[1])
			f[1] = pt[i].fy;
		i ++;
	}
	view->scale_base = (fminf(WIDTH / fmaxf(f[2] - f[0], 1.0f),
				HEIGHT / fmaxf(f[3] - f[1], 1.0f))) * 0.5;
}

void	center_init(t_data *data, int size)
{
	t_pt	*pt;
	int		i;
	int		z_min;
	int		z_max;

	pt = data->param.pt;
	i = 0;
	z_min = INT_MAX;
	z_max = INT_MIN;
	while (i < size)
	{
		if (pt[i].z > z_max)
			z_max = pt[i].z;
		if (pt[i].z < z_min)
			z_min = pt[i].z;
		i ++;
	}
	data->cx = (float)(data->x) * 0.5f;
	data->cy = (float)(data->y) * 0.5f;
	data->cz = (z_min + z_max) * 0.5f;
}

void	rasterise_perspective(t_pt *pt, t_view view, int size, t_data *data)
{
	t_trig	t;
	t_trig	r;
	int		i;

	i = 0;
	while (i < size)
	{
		t.x = pt[i].x - data->cx;
		t.y = pt[i].y - data->cy;
		t.z = pt[i].z - data->cz;
		pt[i].fx = (t.x * view.cosz) - (t.y * view.sinz);
		pt[i].fy = (t.x * view.sinz) + (t.y * view.cosz);
		r.z = -(pt[i].fx * view.siny) + (t.z * view.cosy);
		r.x = (pt[i].fx * view.cosy) + (t.z * view.siny);
		r.y = (pt[i].fy * view.cosx) - (r.z * view.sinx);
		r.z = (pt[i].fy * view.sinx) + (r.z * view.cosx);
		r.z = data->f / (data->f - r.z);
		pt[i].fx = (r.x * view.scale * r.z) + data->offset_x;
		pt[i].fy = (r.y * view.scale * r.z) + data->offset_y;
		i ++;
	}
}

void	rasterise_isometric(t_pt *pt, t_view view, int size, t_data *data)
{
	t_trig	t;
	t_trig	r;
	int		i;

	i = 0;
	while (i < size)
	{
		t.x = pt[i].x - data->cx;
		t.y = pt[i].y - data->cy;
		t.z = pt[i].z - data->cz;
		pt[i].fx = (t.x * view.cosz) - (t.y * view.sinz);
		pt[i].fy = (t.x * view.sinz) + (t.y * view.cosz);
		r.z = -(pt[i].fx * view.siny) + (t.z * view.cosy);
		r.x = (pt[i].fx * view.cosy) + (t.z * view.siny);
		r.y = (pt[i].fy * view.cosx) - (r.z * view.sinx);
		r.y *= view.scale;
		r.x *= view.scale;
		pt[i].fx = r.x + data->offset_x;
		pt[i].fy = r.y + data->offset_y;
		i ++;
	}
}
/*
#include <stdio.h>

void	matrix_zyx_iso(float R[3][3])
{
	R[0][0] = v.cosz * v.cosy;//zyx apparent
	R[0][1] = (v.cosz * v.siny * v.sinx) - (v.cosx * v.sinz);
	R[0][2] = (v.sinz * v.sinx) + (v.cosz * v.cosx * v.siny);

	R[1][0] = v.cosy * v.sinz;
	R[1][1] = (v.cosz * v.cosx) + (v.sinz * v.siny * v.sinx);
	R[1][2] = (v.cosx * v.sinz * v.siny) - (v.cosz * v.sinx);

	R[2][0] = -v.siny;
	R[2][1] = v.cosy * v.sinx;
	R[2][2] = v.cosy * v.cosx;
}

void	matrix_xzy(float R[3][3])
{
	R[0][0] = v.cosy * v.cosx;
	R[0][1] = -v.siny;
	R[0][2] = v.cosy * v.sinx;

	R[1][0] = (v.sinz * v.sinx) + (v.cosz * v.cosx * v.siny);
	R[1][1] = v.cosz * v.cosy;
	R[1][2] = (v.cosz * v.siny * v.sinx) - (v.cosx * v.sinz);

	R[2][0] = (v.cosx * v.sinz * v.siny) - (v.cosz * v.sinx);
	R[2][1] = v.cosy * v.sinz;
	R[2][2] = (v.cosz * v.cosx) + (v.sinz * v.siny * v.sinx);
}

void	matrix_homecooked(float R[3][3])
{
	R[0][0] = v.cosy * v.cosz;
	R[0][1] = -v.cosy * v.sinz;
	R[0][2] = v.siny;

	R[1][0] = (v.cosx * v.sinz) + (v.sinx * v.siny * v.cosz);
	R[1][1] = (v.cosx * v.cosz) - (v.sinx * v.siny * v.sinz);
	R[1][2] = -v.sinx * v.cosy;

	R[2][0] = (v.sinx * v.sinz) - (v.cosx * v.siny * v.cosz);
	R[2][1] = (v.sinx * v.cosz) + (v.cosx * v.siny * v.sinz);
	R[2][2] = v.cosx * v.cosy;
}

void	rasterise_yee(t_pt *pt, t_view v, int size, t_data *data)
{
	int		i;
	float	R[3][3];

	float denom;
	float d = 20;
	float focal = 20;

	t_trig	t;
	i = 0;
	matrix_homecooked(R);
	while (i < size)
	{
		t.x = pt[i].x - data->cx;
		t.y = pt[i].y - data->cy;
		t.z = pt[i].z - data->cz;
		pt[i].fx = (t.x * R[0][0]) + (t.y * R[0][1]) + (t.z * R[0][2]);
		pt[i].fy = (t.x * R[1][0]) + (t.y * R[1][1]) + (t.z * R[1][2]);
		pt[i].fz = (t.x * R[2][0]) + (t.y * R[2][1]) + (t.z * R[2][2]);
		denom = d - pt[i].fz;
		if (denom < 0.1f)
			denom = 0.1f;
		denom = focal / denom;
		printf("\nz: %f, %d\n", pt[i].fz, pt[i].z);
		pt[i].fx *= denom;
		pt[i].fy *= denom;
		pt[i].fx = (pt[i].fx * v.scale) + data->offset_x;
		pt[i].fy = (pt[i].fy * v.scale) + data->offset_y;
		i ++;
	}
	(void) denom;
}
*/
