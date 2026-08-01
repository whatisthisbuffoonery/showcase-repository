/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthoo <dthoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:49:13 by dthoo             #+#    #+#             */
/*   Updated: 2026/03/28 06:48:21 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_mlx.h"

int	perspective_flag(char *v)
{
	return (v && v[0] == '-' && v[1] == 'p' && !v[2]);
}

int	pressed_key(int keycode, void *param)
{
	t_keys	*keys;
	t_data	*data;

	data = (t_data *) param;
	if (keycode == XK_Escape)
		return (fdf_cleanup(data));
	keys = &data->param.keys;
	keys->w += (!keys->w) * (keycode == 'w');
	keys->s += (!keys->s) * (keycode == 's');
	keys->a += (!keys->a) * (keycode == 'a');
	keys->d += (!keys->d) * (keycode == 'd');
	keys->q += (!keys->q) * (keycode == 'q');
	keys->e += (!keys->e) * (keycode == 'e');
	keys->left += (!keys->left) * (keycode == XK_Left);
	keys->right += (!keys->right) * (keycode == XK_Right);
	keys->up += (!keys->up) * (keycode == XK_Up);
	keys->down += (!keys->down) * (keycode == XK_Down);
	if (keycode == 'r')
		data->shade ^= RED;
	if (keycode == 'g')
		data->shade ^= GREEN;
	if (keycode == 'b')
		data->shade ^= BLUE;
	return (0);
}

int	released_key(int keycode, void *param)
{
	t_keys	*keys;

	keys = (t_keys *) param;
	keys->w -= (keys->w != 0) * (keycode == 'w');
	keys->s -= (keys->s != 0) * (keycode == 's');
	keys->a -= (keys->a != 0) * (keycode == 'a');
	keys->d -= (keys->d != 0) * (keycode == 'd');
	keys->q -= (keys->q != 0) * (keycode == 'q');
	keys->e -= (keys->e != 0) * (keycode == 'e');
	keys->left -= (keys->left != 0) * (keycode == XK_Left);
	keys->right -= (keys->right != 0) * (keycode == XK_Right);
	keys->up -= (keys->up != 0) * (keycode == XK_Up);
	keys->down -= (keys->down != 0) * (keycode == XK_Down);
	return (0);
}

int	mouse_wheel(int keycode, int x, int y, void *param)
{
	t_data	*data;

	(void) x;
	(void) y;
	data = (t_data *) param;
	if (keycode == DOWN && data->param.view.scale_mult > 0.3f)
		data->param.view.scale_mult -= 0.2f;
	else if (keycode == UP)
		data->param.view.scale_mult += 0.2f;
	return (0);
}

//colour: 0x00RRGGBB
int	loop_me(t_data data)
{
	data.param.keys = (t_keys){.w = 0, .a = 0, .s = 0, .d = 0, .q = 0, .e = 0};
	mlx_hook(data.win, DestroyNotify, StructureNotifyMask, clicked_x, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, pressed_key, &data);
	mlx_hook(data.win,
		KeyRelease, KeyReleaseMask, released_key, &data.param.keys);
	mlx_mouse_hook(data.win, mouse_wheel, &data);
	mlx_loop_hook(data.mlx, draw_frame, &data);
	mlx_loop(data.mlx);
	return (0);
}
