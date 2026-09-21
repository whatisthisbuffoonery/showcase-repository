#include "h_minirt.h"

/*
   GLOBAL NOTE: add fields for t_object inside cone and cylinder.
   				there are optimised checks rather than doing a separate plane check

	VETO T_CAP GRAAAAA FUCK YOU GEMINI

	discriminant = b^2 - 4ac
	roots = -b +- sqrt(disc) / 2a

	make m a ptr

	math will not be reused for light blocking
*/

void	sphere_disc(t_dot_math *m, int *root)
{
	m->t[1] = -1.0;
	m->disc = (m->b * m->b) - (4.0 * m->a * m->c);
	if (m->disc == 0.0)
		m->t[0] = -0.5 * m->b;
	*root = (m->disc >= 0.0) + (m->disc > 0.0);
	if (*root < 2)
		return ;
	m->q = -0.5 * (m->b + copysign(sqrt(m->disc), m->b));
	m->t[0] = m->q;
	m->t[1] = m->c / m->q;
	if (m->t[0] > m->t[1])
	{
		m->tmp = m->t[0];
		m->t[0] = m->t[1];
		m->t[1] = m->tmp;
	}
}

//may or may not consider far clipping by comparing t_hit against some distance //t_hit is exported to *t
//find vector N elsewhere //sphere case done
int	hit_sphere(double *t, t_dot_math *m)
{
	int		roots;
	int		hit;

	m->p = vec_sub(m->E, m->obj->pos);
	m->a = 1.0;
	m->b = 2.0 * vec_dot(m->p, m->D);
	m->c = vec_dot(m->p, m->p) - (m->obj->radius_sq);
	sphere_disc(m, &roots);
	if (!roots)
		return (0);
	*t = m->t[0];
	hit = (*t > EPSILON);
	if (hit || roots == 1)
		return (hit);
	*t = m->t[1];
	return (*t > EPSILON);
}

//note t2 is not checked with +ve t1, assuming opaque materials
int	cylinder_side(double *t, t_dot_math *m)
{
	double	y_proj;//y_proj to obj
	int		hit;

	if (m->t[0] > EPSILON)
	{
		*t = m->t[0];
		y_proj = m->pv + (m->t[0] * m->dv);
	}
	else if (m->t[1] > EPSILON)
	{
		*t = m->t[1];
		y_proj = m->pv + (m->t[1] * m->dv);
	}
	else
		return (0);
	hit = (0.0 <= y_proj && y_proj <= m->obj->height);
	m->obj->y_proj = y_proj;
	return (hit);
}//thank god we dont have translucent objects

//C is on one end of the cylinder OOPS
int	cylinder_cap(double *t, t_dot_math *m, int *hit)
{
	double	cap;
	double	h[2];
	double	denom;
	int		cond;

	denom = 1.0 / m->dv;
	cond = (m->dv < 0.0);
	h[1] = m->obj->height;
	h[0] = 0.0;
	cap = (h[cond] - m->pv) * denom;
	if (cap <= EPSILON)
	{
		cond = !cond;
		cap = (h[cond] - m->pv) * denom;
	}
	if (cap <= EPSILON)
		return (0);
	m->radial = m->pp + (2.0 * cap * m->dp) + (cap * cap) - (h[cond] * h[cond]);
	hit[1] = (m->radial <= m->obj->radius_sq);
	if(hit[1] && (!hit[0] || cap < m->t[1]))
	{
		*t = cap;
		m->obj->ind = 1 + cond;//ind = 0: side wall, ind = 1: top, ind = 2: bottom
	}
	return (hit[1]);
}

void	cylinder_disc(t_dot_math *m, int *roots)
{
	*roots = 0;
	m->t[1] = -1.0;
	m->disc = (m->b * m->b) - (4.0 * m->a * m->c);
	if (m->disc < 0.0 || m->a <= m->tol_a)
		return ;
	*roots = 1 + (m->disc > 0.0);
	m->root = sqrt(m->disc);
	m->q = -0.5 * (m->b + copysign(m->root, m->b));
	m->t[0] = m->q / m->a;
	if (*roots > 1)
	{
		m->t[1] = m->c / m->q;
		if (m->t[0] > m->t[1])
		{
			m->tmp = m->t[0];
			m->t[0] = m->t[1];
			m->t[1] = m->tmp;
		}
	}
}

int	hit_cylinder(double *t, t_dot_math *m)
{
	int		hit[2];
	int		roots;

	hit[1] = 0;
	m->p = vec_sub(m->E, m->obj->pos);
	m->dv = vec_dot(m->D, m->v);//cosine jumpscare
	m->dp = vec_dot(m->D, m->p);
	m->pv = vec_dot(m->p, m->v);
	m->pp = vec_dot(m->p, m->p);
	m->a = m->dd - (m->dv * m->dv);
	m->b = 2.0 * (m->dp - (m->dv * m->pv));
	m->c = m->pp - (m->pv * m->pv) - (m->obj->radius_sq);
	cylinder_disc(m, &roots);
	hit[0] = (roots > 0 && cylinder_side(t, m));
	if ((!hit[0] || m->t[0] <= EPSILON) && fabs(m->dv) > DIR_TOL)
		cylinder_cap(t, m, hit);
	return (hit[0] || hit[1]);//logic errors might arise if dv wasnt formed from normalised vectors
}

//f#########
int	cone_side(double *t, t_dot_math *m)
{
	double	y_proj;
	int		hit;

	hit = 0;
	if (m->t[0] > EPSILON)
	{
		*t = m->t[0];
		y_proj = m->pv + (m->t[0] * m->dv);
		hit = (y_proj >= 0.0 && y_proj <= m->obj->height);
	}
	if (!hit && m->t[1] > EPSILON)//checks roots > 1 ...bleh
	{
		*t = m->t[1];
		y_proj = m->pv + (m->t[1] * m->dv);
		hit = (y_proj >= 0.0 && y_proj <= m->obj->height);
	}
	if (hit)
		m->obj->y_proj = y_proj;
	return (hit);
}

int	cone_cap(double *t, t_dot_math *m, int *hit)
{
	double	d;
	//double	angle;
	double	cap;
	double	h;

	h = m->obj->height;
	cap = (h - m->pv) / m->dv;
	if (cap <= EPSILON)
		return (0);
	//d = m->pp - (m->pv * m->pv);//gemini flash dumb
	d = m->pp + (2.0 * cap * m->dp) + (cap * cap * m->dd/*is 1*/) - (h * h);
	//angle = tan(/*cache half angle and tan*/);//this is slope
	//return (d <= angle * angle * y_proj);//gemini flash dum2
	hit[1] = (d <= m->obj->cap_check);
	if (hit[1] && (!hit[0] || cap < *t))
	{
		*t = cap;
		m->obj->ind = 1;
	}
	return (hit[1]);
}

//roots starts at -1
void	cone_disc(t_dot_math *m, int *roots)
{
	if (fabs(m->a) <= m->tol_a)
	{
		m->a = 0.0;
		*roots = 1;
		if (fabs(m->b) > m->tol_a * 2.0 * sqrt(m->pp))
			m->t[0] = -m->c / m->b;
		else
			*roots = -(fabs(m->c) > m->tol_a * m->pp);//cap checks side miss first
		return ;
	}
	m->disc = (m->b * m->b) - (4.0 * m->a * m->c);
	*roots = (m->disc >= 0.0) + (m->disc > 0.0);
	if (*roots == 1)
		m->t[0] = -0.5 * m->b / m->a;
	if (*roots < 2)
		return ;
	m->q = -0.5 * (m->b + copysign(sqrt(m->disc), m->b));
	m->t[0] = m->q / m->a;//swap needed ffuuuuuuu
	m->t[1] = m->c / m->q;
	if (m->t[0] > m->t[1])
	{
		m->tmp = m->t[0];
		m->t[0] = m->t[1];
		m->t[1] = m->tmp;
	}
}

//half angle = atan(radius/height);, no need to divide //spits out radian by default
//C is the tip of the cone //oops 
int	hit_cone(double *t, t_dot_math *m)
{
	double	cos_sq;
	int		hit[2];
	int		roots;

	cos_sq = m->obj->cos_sq;
	hit[1] = 0;
	m->t[1] = -1.0;
	roots = -1;
	m->p = vec_sub(m->E, m->obj->pos);
	m->pp = vec_dot(m->p, m->p);
	m->dv = vec_dot(m->D, m->v);
	m->dd = 1.0;
	m->pv = vec_dot(m->p, m->v);
	m->dp = vec_dot(m->D, m->p);
	m->a = (m->dv * m->dv) - (cos_sq * m->dd);
	m->b = 2.0 * ((m->dv * m->pv) - (cos_sq * m->dp));
	m->c = (m->pv * m->pv) - (cos_sq * m->pp);
	cone_disc(m, &roots);
	if (roots < 0)//side wall diagnoses cap misses
		return (0);
	hit[0] = (roots > 0 && cone_side(t, m));
	if ((!hit[0] || (2.0 * m->a * (*t)) + m->b <= 0.0)
		&& fabs(m->dv) > DIR_TOL && (m->obj->height - m->pv) * m->dv > 0.0)
		cone_cap(t, m, hit);//crossing == 0 may be bogus t1/t2
	return (hit[0] || hit[1]);
}

int	hit_plane(double *t, t_dot_math *m)
{
	t_object	*o;
	double		denom;

	//t = vec_dot(vec_sub(m->obj->pos, m->E), m->obj->dir) / vec_dot(m->D, m->obj->dir); //optimised to:
	denom = vec_dot(m->D, m->obj->dir);
	if (fabs(denom) < DIR_TOL)
		return (0);
	o = m->obj;
	*t = -(vec_dot(m->E,o->dir) + o->offset) / vec_dot(m->D, o->dir);
	if (*t <= EPSILON)//scale() might have problems with 0?
		return (0);
	o->p_hit = vec_add(m->E, vec_scale(m->D, *t));//export
	o->p_diff = vec_sub(o->p_hit, o->pos);//local coords: checkerboard and bump maps//export.
	if (o->pl_type == ROUND)
		return (vec_dot(o->p_diff, o->p_diff) <= o->radius_sq);
	else if (o->pl_type == RECTANGLE
			&& fabs(vec_dot(o->p_diff, o->U)) <= o->half_w
			&& fabs(vec_dot(o->p_diff, o->V)) <= o->half_h)
			return (1);
	else
		return (o->pl_type == INFINITE);//mandatory plane IS AN INFINITE PLANE
}
