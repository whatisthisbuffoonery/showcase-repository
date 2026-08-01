/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xiaoxiao.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:49:31 by dthoo             #+#    #+#             */
/*   Updated: 2026/03/28 06:49:15 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_mlx.h"

static int	swap_wrapper(t_pt *src, t_pt *dst, float *dx, float *dy)
{
	int		steep;
	t_pt	tmp;

	*dx = dst->fx - src->fx;
	*dy = dst->fy - src->fy;
	steep = (fabsf(*dy) > fabsf(*dx));
	if (steep)
	{
		ft_swapf(&src->fx, &src->fy);
		ft_swapf(&dst->fx, &dst->fy);
		ft_swapf(dx, dy);
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

//cant do it baws, go ask bresenham
void	buf_edit_uint(t_data *data, float fx, float fy)
{
	unsigned int	value;
	unsigned int	*buf;
	int				x;
	int				y;
	int				line;

	x = fx;
	y = fy;
	if (x < 0 || x >= WIDTH || y >= HEIGHT || y < 0)
		return ;
	line = data->line / data->bypp;
	buf = &data->ubuf[x + (y * line)];
	value = 0xFF * (fy - y);
	if (y >= 0 && y < HEIGHT)
		*buf = (0xFF - value) * data->shade;
	y += 1;
	if (y >= 0 && y < HEIGHT)
		*(buf + line) = value * data->shade;
}

void	buf_edit_char(t_data *data, float fx, float fy)
{
	int		value;
	char	*buf;
	int		x;
	int		y;
	int		line;

	x = fx;
	y = fy;
	if (x < 0 || x >= WIDTH || y >= HEIGHT || y < 0)
		return ;
	line = data->line;
	buf = &data->buf[(x * data->bypp) + (y * line)];
	value = 0xFF * (fy - y);
	if (data->bipp == 24)
	{
		if (y >= 0 && y < HEIGHT)
			*(unsigned int *) buf = (0xFF - value) * data->shade;
		y += 1;
		if (y >= 0 && y < HEIGHT)
			*(unsigned int *)(buf + line) = value * data->shade;
		return ;
	}
	if (y >= 0 && y < HEIGHT)
		*(unsigned int *)(buf + line) = 0xFF;
}

void	xiaolin_wu(t_pt src, t_pt dst, t_data *data)
{
	float	m;
	float	dx;
	float	dy;
	float	*args[2];

	args[0] = &src.fx;
	args[1] = &src.fy;
	if (swap_wrapper(&src, &dst, &dx, &dy))
	{
		args[0] = &src.fy;
		args[1] = &src.fx;
	}
	m = 0.0f;
	if (fabsf(dx) > EPSILON)
		m = dy / dx;
	while (src.fx < dst.fx)
	{
		src.fx += 1;
		src.fy += m;
		data->buf_edit(data, *args[0], *args[1]);
	}
}
