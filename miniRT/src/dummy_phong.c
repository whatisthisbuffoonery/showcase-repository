#include "h_minirt.h"

t_color	phong(t_object *hit, t_vec3 D, t_vec3 pixel/*should be int*/, t_rt *rt)
{
	(void) D;
	(void) pixel;
	(void) rt;
	return (hit->material.color);
}
