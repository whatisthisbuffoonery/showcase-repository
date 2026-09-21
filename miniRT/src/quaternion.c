#include "h_minirt.h"

//defines rotation from direction a to direction b
t_quat	build_quat(t_vec3 a, t_vec3 b)
{
	double	scalar;
	double	cond;
	t_vec3	A;
	t_quat	q;

	scalar = vec_dot(a, b);
	if (scalar < -0.99999f)//opp direction
	{
		cond = (fabs(a.x) > 0.9);
		A = vec_norm(vec_cross((t_vec3){!cond, cond, 0}, a));
		return ((t_quat){0.0, A.x, A.y, A.z});
	}
	else if (scalar > 0.99999f)//same direction
		return ((t_quat) {1.0, 0.0, 0.0, 0.0});
	q.w = sqrt(2.0 * (1.0 + scalar));
	A = vec_cross(a, b);
	q.x = A.x / q.w;
	q.y = A.y / q.w;
	q.z = A.z / q.w;
	q.w *= 0.5f;
	return (q);
}

//defines rotation from direction a by amount b
t_quat	mod_quat(t_quat a, t_quat b)
{
	t_quat	q;
	double	mag_sq;
	double	inv_mag;

	q = (t_quat) {
		.w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z,
		.x = a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
		.y = a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
		.z = a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w
	};
	mag_sq = q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z;
	if (mag_sq < EPSILON_SQ)//discards rotations if delta goes apeshit
		return ((t_quat) {1.0, 0.0, 0.0, 0.0});
	inv_mag = 1.0 / sqrt(mag_sq);
	q.w *= inv_mag;
	q.x *= inv_mag;
	q.y *= inv_mag;
	q.z *= inv_mag;
	return (q);
}

void	math_init(t_math *dst, t_quat q)
{
	t_math	m;

	m.x2 = q.x + q.x;
	m.y2 = q.y + q.y;
	m.z2 = q.z + q.z;
	m.wx = m.x2 * q.w;
	m.wy = m.y2 * q.w;
	m.wz = m.z2 * q.w;
	m.xx = m.x2 * q.x;
	m.yy = m.y2 * q.y;
	m.zz = m.z2 * q.z;
	m.xy = q.x * m.y2;
	m.xz = q.x * m.z2;
	m.yz = q.y * m.z2;
	*dst = m;
}

//finds right, up, front vectors from quaternion
//cache camera t_math?
void	quat_RUF(t_vec3 *R, t_vec3 *U, t_vec3 *F, t_quat q)
{
	t_math	m;

	math_init(&m, q);
	*R = (t_vec3){1.0f - (m.yy + m.zz), m.xy + m.wz, m.xz - m.wy};
	*U = (t_vec3){m.xy - m.wz, 1.0f - (m.xx + m.zz), m.yz + m.wx};
	*F = (t_vec3){-(m.xz + m.wy), m.wx - m.yz, (m.xx + m.yy) - 1.0f};//RHS
}
