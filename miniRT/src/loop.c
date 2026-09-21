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

#include "h_minirt.h"

int	pressed_key(int keycode, void *param)
{
	t_keys	*keys;
	t_rt	*data;

	data = (t_rt *) param;
	if (keycode == XK_Escape)
		return (clicked_x(param));
	keys = &data->keys;
	keys->w += (!keys->w) * (keycode == 'w');
	keys->s += (!keys->s) * (keycode == 's');
	keys->a += (!keys->a) * (keycode == 'a');
	keys->d += (!keys->d) * (keycode == 'd');
	keys->q += (!keys->q) * (keycode == 'q');
	keys->e += (!keys->e) * (keycode == 'e');
	keys->space += (!keys->space) * (keycode == ' ');
/*	keys->left += (!keys->left) * (keycode == XK_Left);
	keys->right += (!keys->right) * (keycode == XK_Right);
	keys->up += (!keys->up) * (keycode == XK_Up);
	keys->down += (!keys->down) * (keycode == XK_Down);*/
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
	keys->space -= (keys->space != 0) * (keycode == ' ');
/*	keys->left -= (keys->left != 0) * (keycode == XK_Left);
	keys->right -= (keys->right != 0) * (keycode == XK_Right);
	keys->up -= (keys->up != 0) * (keycode == XK_Up);
	keys->down -= (keys->down != 0) * (keycode == XK_Down);*/
	return (0);
}

/*
int	mouse_wheel(int keycode, int x, int y, void *param)
{
	t_data	*data;

	(void) x;
	(void) y;
	data = (t_data *) param;
	if (keycode == DOWN && data->param.view.scale_mult > 0.3f)//TODO decide what this does
		data->param.view.scale_mult -= 0.2f;
	else if (keycode == UP)
		data->param.view.scale_mult += 0.2f;
	return (0);
}*/

//colour: 0x00RRGGBB
//q and e tilt the camera sideways, planning to migrate to mouse
int	loop_me(t_rt *rt)
{
	t_camera	*c;
	gettimeofday(&rt->scene.camera.last, NULL);
	rt->keys = (t_keys){.w = 0, .a = 0, .s = 0, .d = 0, .q = 0, .e = 0};
	rt->scene.camera.q = build_quat((t_vec3){0.0, 0.0, -1.0}, rt->scene.camera.dir);
	c = &rt->scene.camera;
	quat_RUF(&c->R, &c->U, &c->F, c->q);
	mlx_hook(rt->win, DestroyNotify, StructureNotifyMask, clicked_x, rt);
	mlx_hook(rt->win, KeyPress, KeyPressMask, pressed_key, rt);
	mlx_hook(rt->win, KeyRelease, KeyReleaseMask, released_key, &rt->keys);
	//mlx_mouse_hook(rt->win, mouse_wheel, &rt);
	mlx_loop_hook(rt->mlx, draw_frame, rt);
	mlx_loop(rt->mlx);
	return (0);
}
