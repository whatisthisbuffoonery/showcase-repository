/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_mand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:49:26 by dthoo             #+#    #+#             */
/*   Updated: 2026/03/25 13:49:26 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_mlx.h"

int	perspective_flag(char *v)
{
	(void) v;
	return (0);
}

int	pressed_key(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *) param;
	if (keycode == XK_Escape)
		return (fdf_cleanup(data));
	return (0);
}

int	loop_me(t_data data)
{
	mlx_hook(data.win, DestroyNotify, StructureNotifyMask, clicked_x, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, pressed_key, &data);
	mlx_loop_hook(data.mlx, draw_frame, &data);
	mlx_loop(data.mlx);
	return (0);
}
