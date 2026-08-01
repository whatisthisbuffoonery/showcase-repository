/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:49:27 by dthoo             #+#    #+#             */
/*   Updated: 2026/03/28 18:38:45 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_mlx.h"

int	clicked_x(void *param)
{
	return (fdf_cleanup((t_data *) param));
}

int	data_init(t_data *data, char **v)
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
	data->shade = SHADE;
	data->bypp = data->bipp / 8;
	data->ubuf = (unsigned int *) data->buf;
	data->buf_edit = buf_edit_uint;
	if (data->bipp != 32)
		data->buf_edit = buf_edit_char;
	data->rasterise = rasterise_isometric;
	if (perspective_flag(v[2]))
		data->rasterise = rasterise_perspective;
	return (0);
}

int	fd_init(char *v, int *fd)
{
	fd[0] = open(v, O_RDONLY);
	if (fd[0] < 0)
		return (1);
	fd[1] = open(v, O_RDONLY);
	if (fd[1] < 0)
	{
		close(fd[0]);
		return (1);
	}
	return (0);
}

int	fdf_cleanup(t_data *d)
{
	t_data	data;
	t_pt	*pt;

	data = *d;
	pt = data.param.pt;
	free(pt);
	if (data.img)
		mlx_destroy_image(data.mlx, data.img);
	if (data.win)
		mlx_destroy_window(data.mlx, data.win);
	if (data.mlx)
		mlx_destroy_display(data.mlx);
	free(data.mlx);
	exit(0);
	return (1);
}

int	main(int c, char **v)
{
	t_data	data;
	int		fd[2];

	if (c != 2 + (v[1] && perspective_flag(v[2])) || fd_init(v[1], fd))
		return (usage(v));
	ft_memset(&data, 0, sizeof(t_data));
	if (pt_init(&data.param.pt, &data, fd) || data_init(&data, v))
		return (fdf_cleanup(&data));
	data.y -= 1;
	close(fd[0]);
	close(fd[1]);
	data.param.view = angle_init();
	center_init(&data, data.size);
	data.offset_x = 0.0f;
	data.offset_y = 0.0f;
	data.rasterise(data.param.pt, data.param.view, data.size, &data);
	data.offset_x = (float) WIDTH * 0.5f;
	data.offset_y = (float) HEIGHT * 0.5f;
	scale_init(data.param.pt, data.size, &data,
		(float []){FLT_MAX, FLT_MAX, -FLT_MAX, -FLT_MAX});
	return (loop_me(data));
}
