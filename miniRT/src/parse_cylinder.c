/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achew <achew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 19:23:22 by achew             #+#    #+#             */
/*   Updated: 2026/08/23 19:23:24 by achew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_minirt.h"

static void	set_cylinder_size(t_object *obj, char *diam_tok, char *height_tok,
	t_rt *rt)
{
	if (!is_numeric_token(diam_tok) || !is_numeric_token(height_tok))
		msg_exit("cy: diameter/height: non-numeric value", rt);
	obj->diameter = ft_atof(diam_tok);
	obj->height = ft_atof(height_tok);
	if (obj->diameter <= 0 || obj->height <= 0)
		msg_exit("cy: diameter and height must be positive", rt);
	obj->radius = obj->diameter / 2.0;
	obj->radius_sq = obj->radius * obj->radius;
	obj->inv_radius = 1.0 / obj->radius;
}

int	parse_cylinder(char **tokens, int i, t_rt *rt)
{
	t_object	*obj;

	obj = object_new(OBJ_CYLINDER);
	if (!obj)
		msg_exit("calloc failure", rt);
	object_add_back(&rt->scene.objects, obj);
	obj->pos = parse_vec3(require_token(tokens, i + 1, rt), rt);
	obj->dir = parse_vec3(require_token(tokens, i + 2, rt), rt);
	if (!vec_in_range(obj->dir, VECTOR_L, VECTOR_U))
		msg_exit("cy: axis vector components must be in [-1,1]", rt);
	else if (vec_dot(obj->dir, obj->dir) < EPSILON_SQ)
		msg_exit("cy: nonzero direction needed", rt);
	obj->dir = vec_norm(obj->dir);
	set_cylinder_size(obj, require_token(tokens, i + 3, rt),
		require_token(tokens, i + 4, rt), rt);
	obj->material.color = parse_color(require_token(tokens, i + 5, rt), rt);
	init_cap(obj, obj->height, rt);
	init_cap(obj, 0.0, rt);
	return (i + 6);
}
