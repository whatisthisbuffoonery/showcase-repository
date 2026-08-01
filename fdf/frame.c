/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:49:02 by dthoo             #+#    #+#             */
/*   Updated: 2026/03/28 06:58:54 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_mlx.h"
/*
int stuff = 0;

void timer(struct timeval start, struct timeval end)
{
	ft_putstr("time: ");
	if (start.tv_sec == end.tv_sec)
	{
		ft_putnbr(end.tv_usec - start.tv_usec);
		ft_putstr("usec\n");
	}
	else
	{
		ft_putnbr(end.tv_sec - start.tv_sec);
		ft_putstr("sec, ");
		ft_putnbr(end.tv_usec - start.tv_usec);
		ft_putstr("usec\n");
	}
}
*/

int	frame_wait(struct timeval start)
{
	struct timeval	end;
	int				flag;
	int				frame_mcs;

	frame_mcs = (SECOND_MCS / FRAMES) + 1;
	gettimeofday(&end, NULL);
	flag = (start.tv_usec + frame_mcs >= SECOND_MCS);
	while (!flag && end.tv_usec - start.tv_usec < frame_mcs)
		gettimeofday(&end, NULL);
	while (flag && start.tv_sec == end.tv_sec)
		gettimeofday(&end, NULL);
	return (0);
}

//sooooo lagggggg
void	pt_wrapper(t_pt *src, t_pt *dst, t_data *data)
{
	if (src->colour_flag || dst->colour_flag)
		bresenham(*src, *dst, data);
	else
		xiaolin_wu(*src, *dst, data);
}

void	goodlines(t_data *data)
{
	int		src;
	int		y_lim;
	int		size;
	int		line;
	t_pt	*pt;

	src = 0;
	pt = data->param.pt;
	line = data->x + 1;
	size = data->size;
	y_lim = size-- - line;
	while (src < size)
	{
		if (src / line == (src + 1) / line)
			pt_wrapper(&pt[src], &pt[src + 1], data);
		if (src < y_lim)
			pt_wrapper(&pt[src], &pt[src + line], data);
		src ++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

void	change_view(t_view *v, t_keys keys)
{
	float	rad_max;

	rad_max = M_PI * 2.0f;
	v->x += v->step * (keys.s - keys.w);
	v->y += v->step * (keys.a - keys.d);
	v->z += v->step * (keys.e - keys.q);
	v->x += rad_max * ((v->x < 0) - (v->x > v->rad_max));
	v->y += rad_max * ((v->y < 0) - (v->y > v->rad_max));
	v->z += rad_max * ((v->z < 0) - (v->z > v->rad_max));
	if (keys.w != keys.s)
	{
		v->cosx = cosf(v->x);
		v->sinx = sinf(v->x);
	}
	if (keys.a != keys.d)
	{
		v->cosy = cosf(v->y);
		v->siny = sinf(v->y);
	}
	if (keys.q != keys.e)
	{
		v->cosz = cosf(v->z);
		v->sinz = sinf(v->z);
	}
}

int	draw_frame(void *param)
{
	struct timeval	start;
	t_data			*data;
	t_keys			*keys;

	gettimeofday(&start, NULL);
	data = (t_data *) param;
	keys = &data->param.keys;
	data->param.view.scale = data->param.view.scale_base
		* data->param.view.scale_mult;
	ft_memset(data->buf, 0, data->line * (HEIGHT + 1));
	change_view(&data->param.view, data->param.keys);
	data->offset_x += 5 * ((keys->right) - (keys->left));
	data->offset_y += 5 * ((keys->down) - (keys->up));
	data->rasterise(data->param.pt, data->param.view, data->size, data);
	goodlines(data);
	frame_wait(start);
	return (0);
}
