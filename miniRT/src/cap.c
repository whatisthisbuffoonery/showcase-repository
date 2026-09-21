#include "h_minirt.h"

void	init_cap(t_object *obj, double h, t_rt *rt)
{
	t_object	*cap;

	cap = object_new(OBJ_PLANE);
	if (!cap)
		msg_exit("calloc failure", rt);
	object_add_back(&obj->caps, cap);
	cap->pl_type = ROUND;
	cap->dir = obj->dir;
	cap->N = obj->dir;
	plane_UVN(&cap->U, &cap->V, cap->N);
	cap->diameter = obj->diameter;
	cap->radius = obj->radius;
	cap->radius_sq = obj->radius_sq;
	cap->pos = vec_add(obj->pos, vec_scale(obj->dir, h));
	cap->offset = -vec_dot(obj->pos, obj->dir);
	cap->material = obj->material;//TODO bumpmap mapping per object
	//inv radius uuhhhh
}
