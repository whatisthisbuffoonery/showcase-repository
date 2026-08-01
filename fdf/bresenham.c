/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 06:57:42 by dthoo             #+#    #+#             */
/*   Updated: 2026/03/28 06:58:27 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_mlx.h"

void	bresen_plot(int x, int y, t_data *data, unsigned int colour)
{
	char	*buf;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	buf = &data->buf[(y * data->line) + (x * data->bypp)];
	*(unsigned int *) buf = colour;
}

static int	swap_wrapper(t_pt *src, t_pt *dst, int *dx, int *dy)
{
	int		steep;
	t_pt	tmp;

	*dx = dst->fx - src->fx;
	*dy = dst->fy - src->fy;
	steep = (ft_abs(*dy) > ft_abs(*dx));
	if (steep)
	{
		ft_swapf(&src->fx, &src->fy);
		ft_swapf(&dst->fx, &dst->fy);
		ft_swap(dx, dy);
	}
	if (*dx < 0)
	{
		tmp = *src;
		*src = *dst;
		*dst = tmp;
		*dx = -*dx;
		*dy = -*dy;
	}
	return (steep);
}

unsigned int	grab_colour(t_pt *src, t_pt *dst, int index, int dx)
{
	int		s[3];
	int		d[3];
	int		r[3];
	float	scale;

	scale = (float) index / (float) dx;
	d[0] = dst->colour & 0xFF;
	d[1] = ((dst->colour >> 8) & 0xFF);
	d[2] = ((dst->colour >> 16) & 0xFF);
	s[0] = src->colour & 0xFF;
	s[1] = (src->colour >> 8) & 0xFF;
	s[2] = (src->colour >> 16) & 0xFF;
	r[0] = s[0] + (int)((d[0] - s[0]) * scale);
	r[1] = s[1] + (int)((d[1] - s[1]) * scale);
	r[2] = s[2] + (int)((d[2] - s[2]) * scale);
	return ((unsigned int)(r[0] | (r[1] << 8) | (r[2] << 16)));
}

static int	bre_init(int *steep, int *i, int *dy)
{
	steep[1] = (*dy >= 0) - (*dy < 0);
	*dy *= steep[1];
	*i = 0;
	return (2 * (*dy));
}

void	bresenham(t_pt src, t_pt dst, t_data *data)
{
	int	dx;
	int	dy;
	int	deez;
	int	steep[2];
	int	i;

	steep[0] = swap_wrapper(&src, &dst, &dx, &dy);
	deez = bre_init(steep, &i, &dy) - dx;
	while (i <= dx)
	{
		if (steep[0])
			bresen_plot((int) src.fy, (int) src.fx + i, data,
				grab_colour(&src, &dst, i, dx));
		else
			bresen_plot((int) src.fx + i, (int) src.fy, data,
				grab_colour(&src, &dst, i, dx));
		if (deez >= 0)
		{
			src.fy += steep[1];
			deez -= 2 * dx;
		}
		deez += 2 * dy;
		i ++;
	}
}
