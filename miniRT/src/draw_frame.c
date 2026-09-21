#include "h_minirt.h"

double	dt(t_camera *camera)
{
	double	start;
	double	last;

	last = (camera->last.tv_usec * TIMEVAL_USEC) + camera->last.tv_sec;
	start = (camera->start.tv_usec * TIMEVAL_USEC) + camera->start.tv_sec;
	return (start - last);
}

void	change_rotation(t_camera *camera, t_keys keys)
{
	double	theta;
	double	c;
	double	s;
	int		cond[3];

	theta = 90.0 * RAD * dt(camera);
	c = cos(theta * 0.5);
	s = sin(theta * 0.5);
	cond[0] = (keys.w != keys.s);
	cond[1] = (keys.a != keys.d);
	cond[2] = (keys.q != keys.e);
	if (cond[0])
		camera->q = mod_quat(camera->q,
				(t_quat){c, s * (keys.w - keys.s), 0.0, 0.0});
	if (cond[1])
		camera->q = mod_quat(camera->q,
				(t_quat){c, 0.0, s * (keys.a - keys.d), 0.0});
	if (cond[2])
		camera->q = mod_quat(camera->q,
				(t_quat){c, 0.0, 0.0, s * (keys.q - keys.e)});
	if (cond[0] || cond[1] || cond[2])
		quat_RUF(&camera->R, &camera->U, &camera->F, camera->q);
}

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

t_color	colour_in(t_rt *rt, t_vec3 pixel)
{
	t_vec3		ndc;
	t_vec3		ray_dir;//D
	t_object	*hit;

	hit = NULL;
	ndc_init(&ndc, pixel);
	find_ray_dir(&ray_dir, rt->scene.camera.q, &rt->scene.camera, ndc);
	if (find_hit_normal(&hit, ray_dir, rt))
		return(phong(hit, ray_dir, pixel, rt));//lighting, shadows, brdf if that will fit
	return ((t_color){0.0, 0.0, 0.0});
}

void	fill_buf(t_rt *rt, t_vec3 p, t_color c)
{
	int	x;
	int	y;

	y = 0;
	while (y < BUF_STEP)
	{
		x = 0;
		while (x < BUF_STEP)
		{
			if (p.x + x < WIDTH && p.y + y < HEIGHT)
				rt->buf_edit(rt, c, p.x + x, p.y + y);
			x ++;
		}
		y ++;
	}
}

//draws stuff pixelated to save frames
//TODO make a version that goes one line per frame and renders every pixel
void	draw_stuff(t_rt *rt)
{
	t_vec3	pixel;
	t_color	c;

	pixel.y = 0;
	pixel.z = 0;
	while (pixel.y < HEIGHT)
	{
		pixel.x = 0;
		while (pixel.x < WIDTH)
		{
			c = colour_in(rt, pixel);
			fill_buf(rt, pixel, c);
			pixel.x += BUF_STEP;
		}
		pixel.y += BUF_STEP;
	}
}

void	change_position(t_camera *camera, t_keys keys)
{
	t_vec3	delta;
	double	speed;

	delta = vec_add(
		vec_scale(camera->U, (keys.q - keys.e)),
		vec_add(vec_scale(camera->R, (keys.d - keys.a)),
			vec_scale(camera->F, (keys.w - keys.s)))
	);
	if (vec_dot(delta, delta) > EPSILON_SQ)
	{
		delta = vec_norm(delta);
		speed = 50.0 * dt(camera);
		camera->pos = vec_add(camera->pos, vec_scale(delta, speed));
	}
}

int	draw_frame(void *param)
{
	t_rt			*rt;

	rt = (t_rt *) param;
	gettimeofday(&rt->scene.camera.start, NULL);
	ft_memset(rt->buf, 0, rt->line * (HEIGHT));//clear img buf
/*	change_rotation(&rt->scene.camera, rt->keys);
	change_position(&rt->scene.camera, rt->keys);*/
	rt->move[(unsigned char) rt->keys.space](&rt->scene.camera, rt->keys);
	draw_stuff(rt);
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img, 0, 0);
	gettimeofday(&rt->scene.camera.last, NULL);
	frame_wait(rt->scene.camera.start);
	return (0);
}
