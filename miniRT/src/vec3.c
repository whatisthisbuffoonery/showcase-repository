/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 19:24:25 by achew             #+#    #+#             */
/*   Updated: 2026/09/04 12:16:20 by dthoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minirt.h"

t_vec3	vec_add(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vec3	vec_sub(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_vec3	vec_scale(t_vec3 a, double s)
{
	return ((t_vec3){a.x * s, a.y * s, a.z * s});
}

double	vec_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

int	vec_in_range(t_vec3 v, double lo, double hi)
{
	return (v.x >= lo && v.x <= hi
		&& v.y >= lo && v.y <= hi
		&& v.z >= lo && v.z <= hi);
}

t_vec3	vec_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	ret = 
	{
		(a.y * b.z) - (a.z * b.y),
		(a.z * b.x) - (a.x * b.z),
		(a.x * b.y) - (a.y * b.x)
	};
	return (ret);
}

//returns unsquared magnitude
//for squared magnitude, just call vec_dot(a, a)
//vec_dot(a, b) returns cos(angle between the two) in unitless range -1, 1
//^^ only if a and b were normalised
double	vec_magnitude(t_vec3 a)
{
	return (sqrt(pow(a.x, 2.0f) + pow(a.y, 2.0f) + pow(a.z, 2.0f)));
}

t_vec3	vec_norm(t_vec3 a)
{
	return (vec_scale(a, 1.0f / vec_magnitude(a)));
}
