#include "h_minirt.h"

/*extra user input params:*/
double	shininess = 32.0;//veto float casts, TODO in discriminant files
double	specular_strength = 0.3;

void	phong(t_object *hit, t_vec3 D, t_rt *rt)
{
	t_vec3	L;//t_light_math
	t_vec3	V;
	t_vec3	R;
	double	diffuse;
	double	specular;
	t_color	out;//american spelling wwwaaaaaaaa

	t_light	*curr;

	curr = rt->scene->lights;
	out = /*cache scale(ambient_colour, ambient_ratio)*/ * hit->color
	while (curr)
	{
		L = vec_norm(vec_sub(curr->pos, P));//P_hit import
		V = vec_norm(vec_scale(D, -1.0));
		diffuse = vec_dot(hit->N, L);
		if (diffuse > 0.0 && /*light not blocked*/)
		{
			R = vec_sub(vec_scale(hit->N, 2.0 * diffuse), L);
			specular = pow(fmax(vec_dot(R, V), 0.0), shininess);
			out.r += /*cache curr->colour * curr->brightness*/ * (hit->color.r * diffuse + specular_strength * specular);
			//repeat for green and blue //r can exceed 1.0, just clamp it to [0.0, 1.0] afterwards

		}
		curr = curr->next;
