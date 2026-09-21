#include "h_minirt.h"

/*global notes

the alternate formulas on normal_cylinder, normal_sphere and normal_cone
are not guaranteed to be normalised

*/
void	normal_sphere(t_object *hit, t_dot_math *m)
{
	t_vec3	P;
	t_vec3	p;

	P = vec_add(m->E, vec_scale(m->D, hit->t));//export
	p = vec_sub(P, hit->pos);
//	hit->N = vec_norm(vec_sub(P, hit->pos));
	/*or*/
	hit->N = vec_scale(p, hit->inv_radius);
	hit->p_hit = P;
	hit->p_diff = p;//checkerboard
}

void	normal_plane(t_object *hit, t_dot_math *m)
{
	(void) m;
	hit->N = hit->dir;//would be stuck acculumating floating error from scale(-1) otherwise;
}

//side wall
void	normal_cylinder(t_object *hit, t_dot_math *m)
{
	t_vec3	P;
	t_vec3	p;
	double	y;
	t_vec3	radial;

	P = vec_add(m->E, vec_scale(m->D, hit->t));//export
	p = vec_sub(P, hit->pos);
//	y = vec_dot(p, hit->dir);
	y = hit->y_proj;
//	radial = vec_sub(p, vec_scale(hit->dir, y));
//	hit->N = vec_norm(radial)
	/*or:*/
	hit->N = vec_scale(vec_sub(p, vec_scale(hit->dir, y)), hit->inv_radius);//1 / radius//cache
	(void) radial;
}

//side wall
void	normal_cone(t_object *hit, t_dot_math *m)
{
	t_vec3	P;
	t_vec3	p;
	double	y;
	t_vec3	normal;
	t_vec3	radial;

	P = vec_add(m->E, vec_scale(m->D, hit->t));//export
	p = vec_sub(P, hit->pos);
	//y = vec_dot(p, hit->dir);
	y = hit->y_proj;
	//radial = vec_sub(p, vec_scale(hit->dir, y));
	//k = hit->slope;//cache slope^2//slope = tan(angle)
	//normal = vec_sub(radial, vec_scale(hit->dir, hit->slope * hit->slope * y));
	/*or*/
	normal = vec_sub(p, vec_scale(hit->dir, hit->cone_factor * y));
	if (vec_dot(normal, normal) == 0.0f)//no epsilon
		hit->N = vec_scale(hit->dir, -1.0f);
	else
		hit->N = vec_norm(normal);
	(void) radial;
}
