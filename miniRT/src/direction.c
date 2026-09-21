#include "h_minirt.h"

void	ndc_init(t_vec3 *ndc, t_vec3 pixel)
{
	ndc->x = ((2.0f * pixel.x) / WIDTH) - 1.0f;
	ndc->y = 1.0f - ((2.0f * pixel.y) / HEIGHT);
}

void	find_ray_dir(t_vec3 *dst, t_quat master, t_camera *c, t_vec3 ndc)
{
	t_vec3	R;
	t_vec3	U;
	t_vec3	F;

	quat_RUF(&R, &U, &F, master);
	ndc.x *= tan(c->fov * RAD * 0.5);
	ndc.y *= tan(c->fov * RAD * 0.5) * (HEIGHT / WIDTH);
	R = vec_scale(R, ndc.x);
	U = vec_scale(U, ndc.y);
	*dst = vec_norm(vec_add(vec_add(R, U), F));//RHS subtract F instead of adding//dipshit gemini
}
