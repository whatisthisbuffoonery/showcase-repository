/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 13:13:53 by achew             #+#    #+#             */
/*   Updated: 2026/09/04 18:20:21 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minirt.h"

//move to after obj init
int	rt_mlx(t_rt *data, char **v)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (1);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, v[1]);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (data->img)
		data->buf = mlx_get_data_addr(data->img,
				&data->bipp,
				&data->line,
				&data->endian);
	if (!data->win || !data->img || !data->buf)
		return (1);
	data->bypp = data->bipp / 8;
	data->ubuf = (unsigned int *) data->buf;
	data->buf_edit = buf_edit_uint;
	if (data->bipp != 32)
		data->buf_edit = buf_edit_char;
	return (0);
}

t_rt	*init_rt(void)
{
	t_rt	*rt;

	rt = ft_calloc(1, sizeof(t_rt));
	if (!rt)
		msg_exit("malloc failure", rt);
	rt->fd = -1;
	rt->hit[INIT_SPHERE] = hit_sphere;
	rt->hit[INIT_PLANE] = hit_plane;
	rt->hit[INIT_CYLINDER] = hit_cylinder;
	rt->hit[INIT_CONE] = hit_cone;
	rt->normal[INIT_SPHERE] = normal_sphere;
	rt->normal[INIT_PLANE] = normal_plane;
	rt->normal[INIT_CYLINDER] = normal_cylinder;
	rt->normal[INIT_CONE] = normal_cone;
	rt->move[0] = change_rotation;
	rt->move[1] = change_position;
	rt->coeff = 64.0f * DBL_EPSILON;
	return (rt);
}
