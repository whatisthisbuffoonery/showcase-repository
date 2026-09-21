#include "h_minirt.h"

t_dot_math	init_dot_math(t_rt *rt, t_vec3 D)
{
	t_dot_math	m;

	m.E = rt->scene.camera.pos;//actually yes.
	m.D = D;
	m.dd = 1.0f;
	//cache
	m.tol_a = rt->coeff;
//	m.tol_b = rt->coeff * 2.0f * /*wtf i need sqrt m.pp*/;//just for cone ig
//	m.tol_c = rt->coeff * m.pp;//also cone exclusive
	return (m);
}

void	resolve_hit(t_object **dst, double t, t_dot_math *m, t_rt *rt)
{
	t_object	*curr;

	curr = *dst;
	if ((*dst)->ind > 0)
		curr = curr->caps;
	if ((*dst)->ind > 1)
		curr = curr->next;
	curr->t = t;
	*dst = curr;
	rt->normal[curr->type](curr/*has N*/, m);
	if (vec_dot(curr->N, m->D) > 0.0f)
		curr->N = vec_scale(curr->N, -1.0f);
}

//should export dist too
int	find_hit_normal(t_object **dst, t_vec3 D, t_rt *rt)
{
	t_object	*curr;
	t_object	*hit;
	double		t[2];
	t_dot_math	m;

	hit = NULL;
	curr = rt->scene.objects;
	m = init_dot_math(rt, D);
	while(curr)
	{
		m.obj = curr;
		m.v = curr->dir;
		curr->ind = 0;
		if (rt->hit[curr->type](&t[0], &m) && (!hit || t[0] < t[1]))//allergic to if condition
		{
			t[1] = t[0];
			hit = curr;
		}
		curr = curr->next;
	}
	*dst = hit;
	if (hit)//could include a function for null hit
		resolve_hit(dst, t[1], &m, rt);
	return (hit != NULL);
}
